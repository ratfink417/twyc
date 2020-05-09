#include "unittest.h"
#include <dlfcn.h>

#define import_check(type, func) type test_func = dlsym(lib_handle, func);

typedef char* (*spanner_tapper)(void);
typedef Network* (*make_network)(char*);
typedef void (*verifier)(char*, void*);
typedef char* (*what_to_do)(Network*);

char *twyc_lib = "/home/emmy/src/TWYC/src/libtwyc.so";
Network *test_net;

void *lib_handle = dlopen(twyc_lib, RTLD_NOW);
check(lib_handle != NULL, "Failed to open library %s: %s", twyc_lib, dlerror());

import_check(spanner_tapper, span);
import_check(spanner_tapper, tap);
import_check(make_network, new_net);
import_check(verifier, span_or_tap_only);
import_check(what_to_do, wut_do);

Network *new_net{return NULL;}
set_network_x(Network *net, int i){return NULL;}
span_or_tap_only(char *arg_val, void *usage()){return NULL;}
char *span(){return NULL;}
char *tap(){return NULL;}
char *wut_do(Network *net){return NULL;}

char *alltests(){
	unittest_suite_start();

	unittest_run_test(new_net);
	unittest_run_test(set_network_x);
	unittest_run_test(span_or_tap_only);
	unittest_run_test(span);
	unittest_run_test(tap);
	unittest_run_test(wut_do);

	return NULL;
}

RUN_TESTS(alltests);
