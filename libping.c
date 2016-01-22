#ifndef LIBPING_H
#define LIBPING_H
#include "libping.h"


void
ping_reset (PING * p)
{
  p->ping_num_xmit = 0;
  p->ping_num_recv = 0;
  p->ping_num_rept = 0;
}


void
ping_set_event_handler (PING * ping, ping_efp pf, void *closure)
{
  ping->ping_event.handler = pf;
  ping->ping_closure = closure;
}





int
ping_recv (PING * p)
{
  socklen_t fromlen = sizeof (p->ping_from.ping_sockaddr);
  int n, rc;
  icmphdr_t *icmp;
  struct ip *ip;
  int dupflag;

  n = recvfrom (p->ping_fd,
    (char *) p->ping_buffer, _PING_BUFLEN (p, USE_IPV6), 0,
    (struct sockaddr *) &p->ping_from.ping_sockaddr, &fromlen);
  if (n < 0)
    return -1;

  rc = icmp_generic_decode (p->ping_buffer, n, &ip, &icmp);
  if (rc < 0)
    {
      /*FIXME: conditional */
      fprintf (stderr, "packet too short (%d bytes) from %s\n", n,
         inet_ntoa (p->ping_from.ping_sockaddr.sin_addr));
      return -1;
    }

  switch (icmp->icmp_type)
    {
    case ICMP_ECHOREPLY:
    case ICMP_TIMESTAMPREPLY:
    case ICMP_ADDRESSREPLY:
      /*    case ICMP_ROUTERADV: */

      if (ntohs (icmp->icmp_id) != p->ping_ident)
  return -1;

      if (rc)
  fprintf (stderr, "checksum mismatch from %s\n",
     inet_ntoa (p->ping_from.ping_sockaddr.sin_addr));

      p->ping_num_recv++;
      if (_PING_TST (p, ntohs (icmp->icmp_seq)))
  {
    p->ping_num_rept++;
    p->ping_num_recv--;
    dupflag = 1;
  }
      else
  {
    _PING_SET (p, ntohs (icmp->icmp_seq));
    dupflag = 0;
  }

      if (p->ping_event.handler)
  (*p->ping_event.handler) (dupflag ? PEV_DUPLICATE : PEV_RESPONSE,
          p->ping_closure,
          &p->ping_dest.ping_sockaddr,
          &p->ping_from.ping_sockaddr, ip, icmp, n);
      break;

    case ICMP_ECHO:
    case ICMP_TIMESTAMP:
    case ICMP_ADDRESS:
      return -1;

    default:
      if (!my_echo_reply (p, icmp))
  return -1;

      if (p->ping_event.handler)
  (*p->ping_event.handler) (PEV_NOECHO,
          p->ping_closure,
          &p->ping_dest.ping_sockaddr,
          &p->ping_from.ping_sockaddr, ip, icmp, n);
    }
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