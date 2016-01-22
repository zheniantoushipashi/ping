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


typedef int (*ping_efp) (int code,
			 void *closure,
			 struct sockaddr_in * dest,
			 struct sockaddr_in * from,
			 struct ip * ip, icmphdr_t * icmp, int datalen);

union event {
  ping_efp handler;
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
	union event ping_event

	unsigned char *ping_buffer;

};

typedef struct ping_data PING;


struct ping_stat
{
  double tmin;                  /* minimum round trip time */
  double tmax;                  /* maximum round trip time */
  double tsum;                  /* sum of all times, for doing average */
  double tsumsq;                /* sum of all times squared, for std. dev. */
};


#define PING_HEADER_LNE ICMP_MINLEN
#define PING_DATALEN    (64 - PING_HEADER_LEN)  /* default data length */


#endif