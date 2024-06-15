#ifndef MOCK_POW_H
#define MOCK_POW_H

#include "gmock/gmock.h"

class MockPowf
{
public:
    MockPowf()
    {
        MockPowf::mock = this;
    }
    ~MockPowf()
    {
        release();
    }
    void release() {
        MockPowf::mock = nullptr;
    }
    MOCK_METHOD(float, powf, (float a, float b));
    static MockPowf *mock;
};
MockPowf* MockPowf::mock = nullptr;

extern "C"
{
    float __real_powf(float a, float b);
    float __wrap_powf(float a, float b)
    {
        if (MockPowf::mock)
            return MockPowf::mock->powf(a, b);
        else
            return __real_powf(a, b);
    }
}

#endif // MOCK_POW_H
