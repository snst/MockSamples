#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <math.h>
#include <unistd.h>

using ::testing::_;
using ::testing::Return;

#define SET_MOCK(func, val) \
    val_mock_##func = val;  \
    enable_mock_##func = true;
#define CLEAR_MOCK(func) \
    enable_mock_##func = false;

#define WRAP_FUNCTION(return_type, func, args) \
    static bool enable_mock_##func = false;    \
    static return_type val_mock_##func;        \
    return_type __real_##func args;            \
    return_type __wrap_##func args;            \
    return_type __wrap_##func args

#define WRAP_FUNCTION_IMPL(func, ...)                                             \
    {                                                                             \
        return enable_mock_##func ? val_mock_##func : __real_##func(__VA_ARGS__); \
    }

extern "C"
{
    WRAP_FUNCTION(void *, malloc, (size_t size))
    WRAP_FUNCTION_IMPL(malloc, size)

#if 0
    WRAP_FUNCTION(int, gethostname, (char *name, size_t len))
    WRAP_FUNCTION_IMPL(gethostname, name, len)
#else
    WRAP_FUNCTION(int, gethostname, (char *name, size_t len))
    {
        if (enable_mock_gethostname)
        {
            strcpy(name, "mockedhostname");
            return val_mock_gethostname;
        }
        else
            return __real_gethostname(name, len);
    }
#endif
}

TEST(Mock, malloc)
{
    void *p;
    p = malloc(10);
    EXPECT_NE(nullptr, p);
    free(p);

    SET_MOCK(malloc, nullptr)
    p = malloc(10);
    EXPECT_EQ(nullptr, p);

    SET_MOCK(malloc, (void *)33)
    p = malloc(10);
    EXPECT_EQ((void *)33, p);

    CLEAR_MOCK(malloc);
    p = malloc(10);
    EXPECT_NE(nullptr, p);
    free(p);
}

TEST(Mock, gethostbyname)
{
    int ret;
    char name[255] = {0};
    ret = gethostname(name, sizeof(name));
    printf("%d: %s\n", ret, name);
    EXPECT_EQ(0, ret);

    SET_MOCK(gethostname, 11)
    ret = gethostname(name, sizeof(name));
    printf("%d: %s\n", ret, name);
    EXPECT_EQ(11, ret);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
