#include "core/result.h" // your header
#include <gtest/gtest.h>

TEST(ResultTest, OkPath) {
  auto r = Result<int, std::string>::ok(42);
  EXPECT_TRUE(r.is_ok());
  EXPECT_FALSE(r.is_err());
  EXPECT_EQ(r.unwrap(), 42);
}

TEST(ResultTest, ErrPath) {
  auto r = Result<int, std::string>::err("boom");
  EXPECT_TRUE(r.is_err());
  EXPECT_FALSE(r.is_ok());
  EXPECT_EQ(r.error(), "boom");
}

TEST(ResultTest, MoveSemantics) {
  auto r1 = Result<std::string, std::string>::ok("hello");
  auto r2 = std::move(r1);
  EXPECT_TRUE(r2.is_ok());
  EXPECT_EQ(r2.unwrap(), "hello");
}
