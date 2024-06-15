// Copyright (c) 2024 Stefan Schmidt
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::Return;

extern "C"
{
    bool failing_malloc = false;
    void *__real_malloc(size_t size);
    void *__wrap_malloc(size_t size)
    {
        return failing_malloc ? nullptr : __real_malloc(size);
    }
}

TEST(MyMallocTest, original)
{
    void *p;
    p = malloc(10);
    EXPECT_NE(nullptr, p);
    free(p);

    failing_malloc = true;
    p = malloc(10);
    EXPECT_EQ(nullptr, p);
    free(p);

    failing_malloc = false;
    p = malloc(10);
    EXPECT_NE(nullptr, p);
    free(p);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
