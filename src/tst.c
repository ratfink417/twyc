#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "dbg.h"
#include "libtwyc.h"

void usage(){
	printf("there are only 2 kinds of time:\n\
		\"you can\"\n\
		\"you must\"\n");
	exit(1);
}

// span and function signature
typedef char* (*spanner_tapper)(void);
// new_net function signature
typedef Network* (*make_network)(char*);
// span_or_tap_only function signature
typedef void (*verifier)(char*, void*);
// wut_do function signature
typedef char* (*what_to_do)(Network*);

int main(int argc, char *argv[]){
	int rc = 0;
	char *twyc_lib = "/home/emmy/src/TWYC/src/libtwyc.so";
	Network *my_net;
	char *span_it,*tap_it,*my_choice;

	if(argc != 3)
		usage();

	void *lib_handle = dlopen(twyc_lib, RTLD_NOW);
	check(lib_handle != NULL, "Failed to open library %s: %s", twyc_lib, dlerror());

	spanner_tapper make_spanner = dlsym(lib_handle, "span");
	check(make_spanner != NULL, "didn't find span in %s: %s", twyc_lib, dlerror());
	spanner_tapper make_tapper  = dlsym(lib_handle, "tap");
	check(make_tapper != NULL, "didn't find tap in %s: %s", twyc_lib, dlerror());
	make_network networker = dlsym(lib_handle, "new_net");
	check(networker != NULL, "didn't find new_net in %s: %s", twyc_lib, dlerror());
	verifier check_net = dlsym(lib_handle, "span_or_tap_only");
	check(check_net != NULL, "didn't find span_or_tap_only in %s: %s", twyc_lib, dlerror());
	what_to_do advice_func = dlsym(lib_handle, "wut_do");
	check(advice_func != NULL, "didn't find wut_do in %s: %s", twyc_lib, dlerror());

	check_net(argv[2], &usage);

	my_net    = networker(argv[2]);
	span_it   = make_spanner();
	tap_it    = make_tapper();
	my_choice = advice_func(my_net);

	printf("%s", my_choice);


	free(my_net);

	rc = dlclose(lib_handle);
	check(rc == 0, "Failed to close %s", twyc_lib);
	return 0;
error:
	printf("You've somehow found yourself in an error state, make sure to fix ^^ this shit\n");
	return -1;
}
