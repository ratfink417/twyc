#include "unittest.h"
#include "libtwyc.h"
#include <dlfcn.h>

#define import_check(TYPE,FUNC) TYPE TYPE ## _test_func = dlsym(lib_handle, #FUNC );\
    check(TYPE ## _test_func != NULL, "failed import: " #FUNC );\
    printf("loaded: %s\n", " " #FUNC);

#define make_network_test(NUM, INPUT)Network *test_net ## NUM = make_network_test_func(" "#INPUT);\
    net_val_set_test_func(test_net ## NUM,NUM);\
    printf("\n%s\n", "test_net" #NUM);\
    printf("\tCan or must: %s\n",test_net ## NUM->when);\
    printf("\tNetwork Integer: %d\n",test_net ## NUM->x);\
    free(test_net ## NUM);

void usage_stub(){printf("\nusage functions will work\n"); return;}
void *lib_handle = NULL;
typedef char* (*spanner_tapper)(void);
typedef Network* (*make_network)(char*);
typedef void (*verifier)(char*, void*);
typedef char* (*what_to_do)(Network*);
typedef void* (*net_val_set)(Network*, int);

char *code_relocation_check(){
    char *twyc_lib = "libtwyc.so";
    lib_handle = dlopen(twyc_lib, RTLD_NOW);
    check(lib_handle != NULL, "Failed to open library %s: %s", twyc_lib, dlerror());

// place any new function from twyc lib that will be used in your program here
    import_check(spanner_tapper, tap);
    import_check(make_network, new_net);
    import_check(verifier, span_or_tap_only);
    import_check(what_to_do, wut_do);

    printf("SUCCESS! all functions used in twyc loaded properly\n");
    return NULL;

error:
    return "Failed the code relocation test check the spelling or type signature of the\n\
function or library you are trying to import\n";
}

char *test_new_net(){
    import_check(make_network, new_net);
    import_check(net_val_set, set_network_x);

    make_network_test(1,can);
    make_network_test(2,must);
    make_network_test(3,atypical);

    return NULL;
error:
    return "unable to test network object creation.\n";
}
char *test_span_or_tap_only(){
    import_check(verifier, span_or_tap_only);
    verifier_test_func("can", &usage_stub);
    verifier_test_func("must", &usage_stub);
    verifier_test_func("atypical", &usage_stub);

    return NULL;

error:
    return "FAIL: unable to import the span_or_tap_only function\n";
}
char *test_span_and_tap(){
    import_check(spanner_tapper, tap);
    spanner_tapper_test_func();
    spanner_tapper span_test_func = dlsym(lib_handle, "span");
    check(span_test_func != NULL, "failed import: span" );
    printf("loaded: span\n");

    return NULL;

error:
    return "FAIL: unable to load spanner or tapper type functions\n";
}
char *test_wut_do(){
    import_check(what_to_do, wut_do);
    import_check(make_network, new_net);

    Network *test_net1 = make_network_test_func("can");
    Network *test_net2 = make_network_test_func("must");
    Network *test_net3 = make_network_test_func("atypical");

    char *t_can = what_to_do_test_func(test_net1);
    char *t_must = what_to_do_test_func(test_net2);
    char *t_atypical = what_to_do_test_func(test_net3);

    printf("\ncan: %s"\
           "must: %s"\
           "atypical: %s",t_can, t_must, t_atypical); // will display "dunno how you got here" because the value would normally be checked by the span_or_tap_only function but this is good and shows that even this code path works

    free(test_net1);
    free(test_net2);
    free(test_net3);

    return NULL;

error:
    return "FAIL: unable to load the wut_do function\n";
}

char *alltests(){
        unittest_suite_start();
        unittest_run_test(code_relocation_check);
        unittest_run_test(test_new_net);
        unittest_run_test(test_span_or_tap_only);
        unittest_run_test(test_span_and_tap);
        unittest_run_test(test_wut_do);

        int rc = dlclose(lib_handle);
        check(rc == 0, "Failed to close shared library");

        return NULL;

error:
        return "ERROR";
}

RUN_TESTS(alltests);
