#include "unittest.h"
#include "libtwyc.h"
#include <dlfcn.h>

#define import_check(type,func) type type ## _test_func = dlsym(lib_handle, #func );\
				check(type ## _test_func != NULL, "failed import: " #func );\
				printf("loaded: %s\n", " " #func);

char *code_relocation_check(){
	typedef char* (*spanner_tapper)(void);
	typedef Network* (*make_network)(char*);
	typedef void (*verifier)(char*, void*);
	typedef char* (*what_to_do)(Network*);


	int rc = 0;
	char *twyc_lib = "libtwyc.so";
	void *lib_handle = dlopen(twyc_lib, RTLD_NOW);
	check(lib_handle != NULL, "Failed to open library %s: %s", twyc_lib, dlerror());

// place any new function from twyc lib that will be used in your program here
	import_check(spanner_tapper, tap);
    	import_check(make_network, new_net);
    	import_check(verifier, span_or_tap_only);
    	import_check(what_to_do, wut_do);

	rc = dlclose(lib_handle);

	return NULL;

error:
	return "Failed the code relocation test check the spelling or type signature of the\n\
function or library you are trying to import\n";
}

char *test_new_net(){
	return NULL;
}
char *test_span_or_tap_only(){
	return NULL;
}
char *test_span_and_tap(){
	return NULL;
}
char *test_wut_do(){
	return NULL;
}

char *alltests(){
        unittest_suite_start();
        unittest_run_test(code_relocation_check);
  	unittest_run_test(test_new_net);
        unittest_run_test(test_span_or_tap_only);
        unittest_run_test(test_span_and_tap);
        unittest_run_test(test_wut_do);

	return NULL;

error:
	return "ERROR";
}

RUN_TESTS(alltests);
