// Copyright (c) 2024 Stefan Schmidt
#ifndef MOCK_FUNC_H
#define MOCK_FUNC_H

#include "gmock/gmock.h"

#define MOCK_FUNC(return_type, func, args, ...)                  \
    class MockFunc_##func                                        \
    {                                                            \
    public:                                                      \
        static MockFunc_##func *mock;                            \
        MockFunc_##func()                                        \
        {                                                        \
            MockFunc_##func::mock = this;                        \
        }                                                        \
        ~MockFunc_##func()                                       \
        {                                                        \
            release();                                           \
        }                                                        \
        void release()                                           \
        {                                                        \
            MockFunc_##func::mock = nullptr;                     \
        }                                                        \
        MOCK_METHOD(return_type, func, args);                    \
    };                                                           \
    MockFunc_##func *MockFunc_##func::mock = nullptr;            \
    extern "C"                                                   \
    {                                                            \
        return_type __real_##func args;                          \
        return_type __wrap_##func args;                          \
        return_type __wrap_##func args                           \
        {                                                        \
            if (MockFunc_##func::mock)                           \
                return MockFunc_##func::mock->func(__VA_ARGS__); \
            else                                                 \
                return __real_##func(__VA_ARGS__);               \
        }                                                        \
    }

#endif // MOCK_FUNC_H
