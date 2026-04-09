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
    print_begin("find_exponent");

    // long double: positive exponents

    GCEM_TEST_EXPECTED_VAL(gcem::internal::find_exponent,  0.0L,  1.0L,    0LL);
    GCEM_TEST_EXPECTED_VAL(gcem::internal::find_exponent,  0.0L,  5.0L,    0LL);
    GCEM_TEST_EXPECTED_VAL(gcem::internal::find_exponent,  1.0L,  10.0L,   0LL);
    GCEM_TEST_EXPECTED_VAL(gcem::internal::find_exponent,  1.0L,  11.0L,   0LL);
    GCEM_TEST_EXPECTED_VAL(gcem::internal::find_exponent,  1.0L,  99.9L,   0LL);
    GCEM_TEST_EXPECTED_VAL(gcem::internal::find_exponent,  2.0L,  100.0L,  0LL);
    GCEM_TEST_EXPECTED_VAL(gcem::internal::find_exponent,  2.0L,  200.0L,  0LL);
    GCEM_TEST_EXPECTED_VAL(gcem::internal::find_exponent,  2.0L,  123.45L, 0LL);

    // long double: negative exponents, including the boundary cases (0.1L and
    // 0.001L round toward zero in 80-bit, placing them just below their nominal
    // decade boundary)

    GCEM_TEST_EXPECTED_VAL(gcem::internal::find_exponent, -1.0L,  0.5L,    0LL);
    GCEM_TEST_EXPECTED_VAL(gcem::internal::find_exponent, -1.0L,  0.1L,    0LL);
    GCEM_TEST_EXPECTED_VAL(gcem::internal::find_exponent, -2.0L,  0.01L,   0LL);
    GCEM_TEST_EXPECTED_VAL(gcem::internal::find_exponent, -3.0L,  0.001L,  0LL);
    GCEM_TEST_EXPECTED_VAL(gcem::internal::find_exponent, -4.0L,  2.0e-4L, 0LL);

    // double: verify the same boundary values work for double

    GCEM_TEST_EXPECTED_VAL(gcem::internal::find_exponent, -1.0L,  0.1,     0LL);
    GCEM_TEST_EXPECTED_VAL(gcem::internal::find_exponent, -3.0L,  0.001,   0LL);

    print_final("find_exponent");

    return 0;
}
