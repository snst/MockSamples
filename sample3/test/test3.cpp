// Copyright (c) 2024 Stefan Schmidt
#include "gtest/gtest.h"

TEST(Test3, mockGethostname)
{
    int ret;
    char name[255] = {0};
    ret = gethostname(name, sizeof(name));
    printf("%d: %s\n", ret, name);
    EXPECT_EQ(0, ret);
}
