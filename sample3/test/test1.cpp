// Copyright (c) 2024 Stefan Schmidt
#include "gtest/gtest.h"
#include "mocks/mock_sample.h"

using ::testing::_;
using ::testing::Return;

TEST(Test1, mockMalloc)
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

TEST(Test1, mockGethostname)
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
