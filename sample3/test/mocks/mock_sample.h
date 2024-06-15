#ifndef MOCK_SAMPLE1_H
#define MOCK_SAMPLE1_H

#include "mock_func.h"
#include <stdint.h>

MOCK_FUNC(void *, malloc, (size_t size), (size))
MOCK_FUNC(int, gethostname, (char *name, size_t len), (name, len))

#endif // MOCK_SAMPLE1_H