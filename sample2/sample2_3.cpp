#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::Return;

#define WRAP_FUNCTION(return_type, func, args) \
    bool failing_##func = false;               \
    return_type __real_##func args;            \
    return_type __wrap_##func args;            \
    return_type __wrap_##func args

extern "C"
{
    WRAP_FUNCTION(void *, malloc, (size_t size))
    {
        return failing_malloc ? nullptr : __real_malloc(size);
    }
}

TEST(Malloc, test)
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
