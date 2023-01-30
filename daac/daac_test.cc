#include "daac/daac.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "daac/darts_clone_builder.h"
#include "daac/darts_clone_wrapper.h"

using namespace daac;

TEST(TestDAAC, test) {
  std::vector<std::string> keys = {"a", "ab", "bc", "abc", "bcd", "efg"};
  auto status = trie::BuildDartsCloneTrie(keys);

  ASSERT_TRUE(status.ok());
  auto trie_array = status.value();

  status = trie::BuildFailPath(trie_array);
  ASSERT_TRUE(status.ok());
  auto fail_path = status.value();

  auto daac_or = DAAC::Create(trie_array.data(), fail_path.data());
  ASSERT_TRUE(daac_or.ok());

  auto output = daac_or.value().FindAllMatchingWords("abcdef");
  ASSERT_THAT(output, testing::UnorderedElementsAre(0, 1, 2, 3, 4));
}
