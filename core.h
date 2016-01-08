#ifndef CORE_H
#define CORE_H




#include "log.h"
#include "icmp.h"

#include <netinet/in_systm.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/time.h>



#include <stdbool.h>

union ping_address {
  struct sockaddr_in ping_sockaddr;
};



struct ping_data
{
	int ping_fd;
	int ping_type;
	size_t ping_count;
	struct timeval ping_start_time;
	union ping_address ping_dest;
	union ping_address ping_from;
	size_t ping_num_xmit;
	size_t ping_num_recv;
	size_t ping_num_rept;
	size_t ping_datalen;
	char *ping_hostname;

};

typedef struct ping_data PING;




#endif