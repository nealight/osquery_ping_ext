#include <gtest/gtest.h>
#include "helpers.hpp"

namespace osquery {
namespace example {

class PingTests : public testing::Test {};

TEST_F(PingTests, test_plugin) {
  EXPECT_TRUE(isValidHost("8.8.8.8"));
  EXPECT_TRUE(isValidHost("google.com"));
  EXPECT_FALSE(isValidHost("8.8.888.8"));
  EXPECT_FALSE(isValidHost("eval(\"rm .\")"));

}

}
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
