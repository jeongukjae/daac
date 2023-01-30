#ifndef __DAAC_DARTS_CLONE_BUILDER_H__
#define __DAAC_DARTS_CLONE_BUILDER_H__

#include "absl/status/statusor.h"

namespace daac {
namespace trie {

// Builds the trie given keys and values, and returns the darts_clone trie
// array data. `keys` and `values` should have the same size; `values[i]` is the
// value for `keys[i]`. `keys` should not contain duplicated elements. In
// addition, the empty string "" should not be in `keys`, because darts_clone
// does not support that. Furthermore, all `values` should be non-negative.
//
// Copied from
// https://github.com/tensorflow/text/blob/master/tensorflow_text/core/kernels/darts_clone_trie_builder.h
absl::StatusOr<std::vector<uint32_t>> BuildDartsCloneTrie(
    const std::vector<std::string>& keys, const std::vector<int>& values);

// A variant where the values are indexes in the keys: i.e., the value for
// `keys[i]` is the index `i`.
//
// Copied from
// https://github.com/tensorflow/text/blob/master/tensorflow_text/core/kernels/darts_clone_trie_builder.h
absl::StatusOr<std::vector<uint32_t>> BuildDartsCloneTrie(
    const std::vector<std::string>& keys);

// Build fail path for the trie.
absl::StatusOr<std::vector<uint32_t>> BuildFailPath(
    const std::vector<uint32_t>& trie_array);

}  // namespace trie
}  // namespace daac

#endif  // __DAAC_DARTS_CLONE_BUILDER_H__
