#include "func_check.h"


int main(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = unit_tests_suite();
   
    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);

    no_failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    if (no_failed == 0)
    {
        return EXIT_SUCCESS;
    }
    else
    {
        return EXIT_FAILURE;
    }
}
