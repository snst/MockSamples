// Copyright (c) 2024 Stefan Schmidt
#ifndef MOCK_ADD_H
#define MOCK_ADD_H

#include "gmock/gmock.h"

class MockAdd
{
public:
    static MockAdd *mock;
    MockAdd()
    {
        MockAdd::mock = this;
    }
    ~MockAdd()
    {
        release();
    }
    void release() {
        MockAdd::mock = nullptr;
    }
    MOCK_METHOD(float, add, (float a, float b));
};
MockAdd* MockAdd::mock = nullptr;

extern "C"
{
    float __real_add(float a, float b);
    float __wrap_add(float a, float b)
    {
        if (MockAdd::mock)
            return MockAdd::mock->add(a, b);
        else
            return __real_add(a, b);
    }
}

#endif // MOCK_ADD_H
