// Copyright (c) 2024 Stefan Schmidt
#include "gtest/gtest.h"
#include "mocks/mock_sample.h"

using ::testing::_;
using ::testing::Return;

TEST(Test2, mockGethostname)
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
