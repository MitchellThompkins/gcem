/*################################################################################
  ##
  ##   Copyright (C) 2016-2026 Keith O'Hara
  ##
  ##   This file is part of the GCE-Math C++ library.
  ##
  ##   Licensed under the Apache License, Version 2.0 (the "License");
  ##   you may not use this file except in compliance with the License.
  ##   You may obtain a copy of the License at
  ##
  ##       http://www.apache.org/licenses/LICENSE-2.0
  ##
  ##   Unless required by applicable law or agreed to in writing, software
  ##   distributed under the License is distributed on an "AS IS" BASIS,
  ##   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  ##   See the License for the specific language governing permissions and
  ##   limitations under the License.
  ##
  ################################################################################*/

#define TEST_PRINT_PRECISION_1 6
#define TEST_PRINT_PRECISION_2 18

#include "gcem_tests.hpp"

int main()
{
    print_begin("mantissa");

    // long double: values whose mantissa is unambiguous

    GCEM_TEST_EXPECTED_VAL(gcem::internal::mantissa,  1.0L,  1.0L);
    GCEM_TEST_EXPECTED_VAL(gcem::internal::mantissa,  5.0L,  5.0L);
    GCEM_TEST_EXPECTED_VAL(gcem::internal::mantissa,  9.99L, 9.99L);
    GCEM_TEST_EXPECTED_VAL(gcem::internal::mantissa,  2.0L,  20.0L);
    GCEM_TEST_EXPECTED_VAL(gcem::internal::mantissa,  1.2345L, 123.45L);
    GCEM_TEST_EXPECTED_VAL(gcem::internal::mantissa,  5.0L,  0.5L);
    GCEM_TEST_EXPECTED_VAL(gcem::internal::mantissa,  2.0L,  0.02L);

    // long double: boundary cases withing the ULP-tolerant snap.  0.1L and
    // 0.001L round toward zero in 80-bit, so repeated scaling by 10 lands just
    // below 1.0 rather than exactly on it.  mantissa() must snap these to 1.0
    // to stay consistent with find_exponent().

    GCEM_TEST_EXPECTED_VAL(gcem::internal::mantissa,  1.0L,  0.1L);
    GCEM_TEST_EXPECTED_VAL(gcem::internal::mantissa,  1.0L,  0.001L);

    // double: verify the same boundary values work for double

    GCEM_TEST_EXPECTED_VAL(gcem::internal::mantissa,  1.0,   0.1);
    GCEM_TEST_EXPECTED_VAL(gcem::internal::mantissa,  1.0,   0.001);

    print_final("mantissa");

    return 0;
}
