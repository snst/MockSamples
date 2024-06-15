#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::Return;

extern "C"
{
    void *__real_malloc(size_t size);
    void *__wrap_malloc(size_t size)
    {
        return __real_malloc(size);
    }
}

TEST(Malloc, test)
{
    void *p;
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
