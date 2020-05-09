#include "libtwyc.h"
#include "dbg.h"
#include <stdio.h>
#include <stdlib.h>

Network *new_net(const char *can_or_must){
    Network *net = malloc(sizeof(Network));
    net->when = can_or_must;
    return net;
}

void set_network_x(Network *net, int i){
    net->x = i;
    return;
}

void span_or_tap_only(char *arg_val, void *usage()){
	if(strcmp(arg_val,"can") == 0 || strcmp(arg_val,"must") == 0)
		{return;}
	else
	{
		usage();
	}
}

char *span(){
	return "SPAN!\n";
}

char *tap(){
	return "TAP!\n";
}

char *wut_do(Network *net){
	if(strcmp(net->when,"can") == 0)
		return tap();
	if(strcmp(net->when,"must") == 0)
		return span();
return "error, dunno how you got here";
}
