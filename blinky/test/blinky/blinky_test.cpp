extern "C" {
#include "blinky.h"
}

#include "gtest/gtest.h"

class UT_Blinky : public testing::Test {
   public:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(UT_Blinky, test1) {
    EXPECT_EQ(1, 1);
}
