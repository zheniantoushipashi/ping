#ifndef LIBPING_H
#define LIBPING_H
#include "libping.h"

int  
ping_echo (char *hostname)
{
	return 0;
}


PING *
ping_init(int type, int ident)
{
	int fd;
	struct protoent *proto;
	PING *p;
	proto = getprotobyname("icmp");
	if (!proto) {
		log_error("ping: unknown protocol icmp.\n");
		return NULL;
	}

	fd = socket(AF_INET, SOCK_RAW, proto->p_proto);
	if(fd < 0)
	{
		if (errno == EPERM || errno == EACCES)
		{
			log_error("ping: Lacking privilege for raw socket.\n");
			return NULL;
		}	
	} 

	p = malloc(sizeof(*p));
	if (!p)
	{
		close(fd);
		return p;
	}

	memset(p, 0, sizeof(*p));

	p->ping_fd = fd;
	p->ping_type = type;
  	p->ping_count = 0;

  	p->ping_datalen = sizeof (icmphdr_t);
  	p->ping_ident = ident & 0xFFFF;
  	gettimeofday (&p->ping_start_time, NULL);
  	return p;



}


#endif