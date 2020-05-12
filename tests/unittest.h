#undef NDEBUG
#ifndef _unittest_h
#define _unittest_h

#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"

#define unittest_suite_start() char *message = NULL

#define unittest_assert(test,message) if(!(test)){\
	log_err(message); return message;}

#define unittest_run_test(test) debug("\t\t%s", " " #test);\
	message = test();\
	tests_run++;\
	printf("\n____________________________________________________________________________\n");\
	if(message) return message;

#define RUN_TESTS(name) int main(int argc, char *argv[]){\
	argc = 1;\
	printf("############################################################################\n");\
	printf("\t\t\t----- RUNNING TESTS -----\n");\
	printf("############################################################################\n");\
	char *result = name();\
	printf("RESULTS\n");\
	printf("----------------------------------------------------------------------------\n\n");\
	if(result != 0){printf("FAILED: %s\n", result);}\
	else\
	{\
		printf("ALL TESTS PASSED\n");\
		exit(result != 0);\
	}}

int tests_run;
#endif
