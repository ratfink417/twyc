#ifndef _ex22_h
#define _ex22_h
#include <stdlib.h>

typedef struct network
{
	const char *when;
	int x;
} Network;

// constructor method of the Network object
Network *new_net(const char *can_or_must);

// verifies user input against the twyc block chain before allowing
// the AI to perform analysis
void span_or_tap_only(char *arg_val, void *usage());

// reaches deep in the twyc neural net to return a final decision
char *span();
char *tap();
char *wut_do(Network *net);

#endif
