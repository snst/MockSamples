#include "mock_sample.h"

MOCK_FUNC_IMPL(void *, malloc, (size_t size), (size))
MOCK_FUNC_IMPL(int, gethostname, (char *name, size_t len), (name, len))
