#ifndef LIBPING_H
#define LIBPING_H
#include "core.h"

int ping_reset (PING * p);
void ping_set_event_handler (PING * ping, ping_efp pf, void *closure);
int ping_recv (PING * p);
PING *ping_init(int type, int ident);

#endif