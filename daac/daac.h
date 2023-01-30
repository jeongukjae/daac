#ifndef __DAAC_DAAC_H__
#define __DAAC_DAAC_H__

#include <cstdint>

#include "absl/status/statusor.h"
#include "daac/darts_clone_wrapper.h"

namespace daac {

class DAAC {
 public:
  // Constructs an instance by passing in the pointer to the trie array data,
  // and the pointer to the fail path array data.
  static absl::StatusOr<DAAC> Create(const uint32_t* trie_array,
                                     const uint32_t* fail_path) {
    auto darts_clone_trie_wrapper_or =
        trie::DartsCloneTrieWrapper::Create(trie_array);
    if (!darts_clone_trie_wrapper_or.ok()) {
      return darts_clone_trie_wrapper_or.status();
    }

    if (fail_path == nullptr) {
      return absl::InvalidArgumentError("fail_path array is nullptr.");
    }

    return DAAC(darts_clone_trie_wrapper_or.value(), fail_path);
  }

  bool TryGetData(const trie::DartsCloneTrieWrapper::TraversalCursor& cursor,
                  std::vector<int>& out_vec) const {
    int out;
    if (trie_wrapper_.TryGetData(cursor, out)) {
      out_vec.push_back(out);

      auto current =
          trie_wrapper_.CreateTraversalCursor(fail_path_[cursor.node_id]);
      while (trie_wrapper_.TryGetData(current, out)) {
        out_vec.push_back(out);
        current =
            trie_wrapper_.CreateTraversalCursor(fail_path_[current.node_id]);
      }
    }

    return false;
  }

  // Print all matching words for the given sentence.
  std::vector<int> FindAllMatchingWords(absl::string_view sentence) {
    std::vector<int> out;
    auto cursor = trie_wrapper_.CreateTraversalCursorPointToRoot();

    for (int i = 0; i < sentence.size(); ++i) {
      if (!trie_wrapper_.TryTraverseOneStep(cursor, sentence[i])) {
        cursor =
            trie_wrapper_.CreateTraversalCursor(fail_path_[cursor.node_id]);
        trie_wrapper_.TryTraverseOneStep(cursor, sentence[i]);
      }

      TryGetData(cursor, out);
    }

    return out;
  }

 private:
  explicit DAAC(const trie::DartsCloneTrieWrapper trie_wrapper,
                const uint32_t* fail_path)
      : trie_wrapper_(trie_wrapper), fail_path_(fail_path) {}

  // darts_clone trie wrapper.
  const trie::DartsCloneTrieWrapper trie_wrapper_;
  // The pointer to the fail path array.
  const uint32_t* fail_path_;
};

}  // namespace daac

#endif  // __DAAC_DAAC_H__
