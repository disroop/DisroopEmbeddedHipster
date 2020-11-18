extern "C"
{
#include "toggle.h"
}
#include <gtest/gtest.h>

TEST(ToggleTest, Test1)
{
  EXPECT_EQ(1,1);
  EXPECT_NO_THROW(toggleLed());
}
