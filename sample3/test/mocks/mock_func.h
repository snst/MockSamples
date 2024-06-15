// Copyright (c) 2024 Stefan Schmidt
#ifndef MOCK_FUNC_H
#define MOCK_FUNC_H

#include "gmock/gmock.h"

#define MOCK_FUNC(return_type, func, params, args)       \
    extern "C"                                           \
    {                                                    \
        return_type __real_##func params;                \
        return_type __wrap_##func params;                \
    }                                                    \
    class MockFunc_##func                                \
    {                                                    \
    public:                                              \
        static MockFunc_##func *mock;                    \
        MockFunc_##func()                                \
        {                                                \
            enable();                                    \
        }                                                \
        ~MockFunc_##func()                               \
        {                                                \
            disable();                                   \
        }                                                \
        void enable()                                    \
        {                                                \
            MockFunc_##func::mock = this;                \
        }                                                \
        void disable()                                   \
        {                                                \
            MockFunc_##func::mock = nullptr;             \
        }                                                \
        static return_type real_func params              \
        {                                                \
            return __real_##func args;                   \
        }                                                \
        static return_type call params                   \
        {                                                \
            if (MockFunc_##func::mock)                   \
                return MockFunc_##func::mock->func args; \
            else                                         \
                return __real_##func args;               \
        }                                                \
        MOCK_METHOD(return_type, func, params);          \
    };

#define MOCK_FUNC_IMPL(return_type, func, params, args) \
    MockFunc_##func *MockFunc_##func::mock = nullptr;   \
    extern "C"                                          \
    {                                                   \
        return_type __wrap_##func params                \
        {                                               \
            return MockFunc_##func::call args;          \
        }                                               \
    }

#endif // MOCK_FUNC_H
