// Copyright (c) 2024 Stefan Schmidt
#ifndef MOCK_FUNC_H
#define MOCK_FUNC_H

#include "gmock/gmock.h"

#define MOCK_FUNC(return_type, func, params, args) \
    class MockFunc_##func                          \
    {                                              \
    public:                                        \
        static MockFunc_##func *mock;              \
        MockFunc_##func()                          \
        {                                          \
            MockFunc_##func::mock = this;          \
        }                                          \
        ~MockFunc_##func()                         \
        {                                          \
            release();                             \
        }                                          \
        void release()                             \
        {                                          \
            MockFunc_##func::mock = nullptr;       \
        }                                          \
        MOCK_METHOD(return_type, func, params);    \
    };                                             \
    extern "C"                                     \
    {                                              \
        return_type __real_##func params;          \
        return_type __wrap_##func params;          \
    }

#define MOCK_FUNC_IMPL(return_type, func, params, args)  \
    MockFunc_##func *MockFunc_##func::mock = nullptr;    \
    extern "C"                                           \
    {                                                    \
        return_type __wrap_##func params                 \
        {                                                \
            if (MockFunc_##func::mock)                   \
                return MockFunc_##func::mock->func args; \
            else                                         \
                return __real_##func args;               \
        }                                                \
    }

#endif // MOCK_FUNC_H
