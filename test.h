#include <cassert>
#include <cstdio>

void test_suite();

#define SUCC 0
#define FAIL -1

#ifndef case_num
#define case_num case_num
int case_num = 0;

#endif

#define print_case_pass(expr, op, b) printf("[case %.3d] { %s %s %s } pass.\n", ++case_num, #expr, #op, #b);

#define should_equal(expr, b) assert(expr == b); print_case_pass(expr, ==, b);

#define should_not_equal(expr, b) assert(expr != b); print_case_pass(expr, !=, b);

#define should_succ(expr) should_equal(SUCC, expr)

#define should_fail(expr) should_equal(FAIL, expr)