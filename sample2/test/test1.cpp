// Copyright (c) 2024 Stefan Schmidt
#include "gtest/gtest.h"
#include "mocks/mock_add.h"
#include "mocks/mock_powf.h"
#include "my_calculator.h"

using ::testing::_;
using ::testing::Return;

TEST(Sample1, original)
{
    EXPECT_EQ(12, calculate("4 + 8"));
    EXPECT_EQ(32, calculate("4 * 8"));
    EXPECT_EQ(0.5, calculate("4 / 8"));
    EXPECT_EQ(-4, calculate("4 - 8"));
    EXPECT_EQ(65536, calculate("4 ^ 8"));
}

TEST(Sample1, mockAdd)
{
    MockAdd mock;
    EXPECT_CALL(mock, add(4, 8))
        .Times(1)
        .WillOnce(Return(22));

    EXPECT_EQ(calculate("4 + 8"), 22);

    mock.release();
    EXPECT_EQ(12, calculate("4 + 8"));
}

TEST(Sample1, mockPowf)
{
    MockPowf mock;
    EXPECT_CALL(mock, powf(4, 8))
        .Times(1)
        .WillOnce(Return(22));

    EXPECT_EQ(calculate("4 ^ 8"), 22);

    mock.release();
    EXPECT_EQ(65536, calculate("4 ^ 8"));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
