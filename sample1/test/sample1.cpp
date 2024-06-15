// Copyright (c) 2024 Stefan Schmidt
#include "gtest/gtest.h"
#include "mocks/mock_add.h"
#include "mocks/mock_powf.h"
#include "mocks/mock_func.h"
#include "my_calculator.h"

using ::testing::_;
using ::testing::Return;

MOCK_FUNC(void *, malloc, (size_t size), (size))
MOCK_FUNC(int, gethostname, (char *name, size_t len), (name, len))
MOCK_FUNC(float, sub, (float a, float b), (a, b))

TEST(MyMathTest, mockMalloc)
{
    MockFunc_malloc mock;
    EXPECT_CALL(mock, malloc(99))
        .Times(1)
        .WillOnce(Return(nullptr));

    void *p = malloc(99);
    EXPECT_EQ(nullptr, p);

    mock.release();
    p = malloc(99);
    EXPECT_NE(nullptr, p);
    free(p);
}

TEST(MyMathTest, mockGethostname)
{
    int ret;
    char name[255] = {0};
    ret = gethostname(name, sizeof(name));
    printf("%d: %s\n", ret, name);
    EXPECT_EQ(0, ret);

    MockFunc_gethostname mock;
    EXPECT_CALL(mock, gethostname(_, _))
        .Times(1)
        .WillOnce(Return(11));

    ret = gethostname(name, sizeof(name));
    printf("%d: %s\n", ret, name);
    EXPECT_EQ(11, ret);
}

TEST(MyMathTest, mockSub)
{
    MockFunc_sub mock;
    EXPECT_CALL(mock, sub(4, 8))
        .Times(1)
        .WillOnce(Return(22));

    EXPECT_EQ(calculate("4 - 8"), 22);

    mock.release();
    EXPECT_EQ(-4, calculate("4 - 8"));
}

TEST(MyMathTest, original)
{
    EXPECT_EQ(12, calculate("4 + 8"));
    EXPECT_EQ(32, calculate("4 * 8"));
    EXPECT_EQ(0.5, calculate("4 / 8"));
    EXPECT_EQ(-4, calculate("4 - 8"));
    EXPECT_EQ(65536, calculate("4 ^ 8"));
}

TEST(MyMathTest, mockAdd)
{
    MockAdd mock;
    EXPECT_CALL(mock, add(4, 8))
        .Times(1)
        .WillOnce(Return(22));

    EXPECT_EQ(calculate("4 + 8"), 22);

    mock.release();
    EXPECT_EQ(12, calculate("4 + 8"));
}

TEST(MyMathTest, mockPowf)
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
