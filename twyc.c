#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Network
{
	char *when;
	int x;
};

char *span(){
	return "SPAN!\n";
}

char *tap(){
	return "TAP!\n";
}

void usage(){
	printf("there are only 2 kinds of time:\n\
		\"you can\"\n\
		\"you must\"\n");
	exit(1);
}

void check_input(char *arg_val){

	if(strcmp(arg_val,"can") == 0 || strcmp(arg_val,"must") == 0)
		{return;}
	else
	{
		usage();
	}
}

char *wut_do(struct Network *net){
	if(strcmp(net->when,"can") == 0)
		return tap();
	if(strcmp(net->when,"must") == 0)
		return span();
return "error, dunno how you got here";
}

int main(int argc, char *argv[]){
	struct Network *myNet = malloc(sizeof(struct Network));

	if(argc != 3)
		usage();

	myNet->x = 1;
	myNet->when = argv[2];

	check_input(myNet->when);

	printf("%s\n", wut_do(myNet));

	free(myNet);

	return 0;
}
