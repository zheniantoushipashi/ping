#include "ping.h"


extern int ping_echo (char *hostname);

extern char *optarg;

int ping_set_dest(PING *ping, char *host);


char buf[BUF_SIZE] = {0};

// ICMP报文数据结构
struct icmp{
    UCHAR           type;      // 类型
    UCHAR           code;      // 代码
    USHORT          checksum;  // 校验和
    USHORT          id;        // 标识符
    USHORT          sequence;  // 序号 
    struct timeval  timestamp; // 时间戳
};


// IP首部数据结构
struct ip{
    // 主机字节序判断
    #if __BYTE_ORDER == __LITTLE_ENDIAN
    UCHAR   hlen:4;        // 首部长度
    UCHAR   version:4;     // 版本      
    #endif
    #if __BYTE_ORDER == __BIG_ENDIAN
    UCHAR   version:4;       
    UCHAR   hlen:4;    
    #endif    
    UCHAR   tos;             // 服务类型
    USHORT  len;             // 总长度
    USHORT  id;                // 标识符
    USHORT  offset;            // 标志和片偏移
    UCHAR   ttl;            // 生存时间
    UCHAR   protocol;       // 协议
    USHORT  checksum;       // 校验和
    struct in_addr ipsrc;    // 32位源ip地址
    struct in_addr ipdst;   // 32位目的ip地址
};




int (*decode_type (const char *arg)) (char *hostname);
void ping_set_sockope(PING *ping, int opt, void *val, int valsize);

size_t data_length = PING_DATALEN;

enum {
  ARG_ECHO = 256,
  ARG_ADDRESS,
  ARG_TIMESTAMP,
  ARG_ROUTERDISCOVERY,
  ARG_TTL,
  ARG_IPTIMESTAMP,
};

size_t count = DEFAULT_PING_COUNT;
unsigned options;
PING *ping;
int ttl = 0;

size_t  ping_cvt_number (const char *optarg, size_t maxval, int allow_zero);
static errno_t  parse_opt(int argc, char **argv);



int 
main (int argc, char **argv)
{
  int status = 0;
  parse_opt(argc, argv);
  int one = 1;

  ping = ping_init(ICMP_ECHO, getpid())

  if (ping == NULL)
    /* ping_init() prints our error message.  */
    exit (EXIT_FAILURE);


  ping_set_sockopt (ping, SO_BROADCAST, (char *) &one, sizeof (one));

  setuid (getuid ());

  --argc;
  ++argv;

  if (count != 0)
  {
    ping->ping_count = count;
  }

  if (socket_type != 0)
  {
    ping_set_sockopt(ping, socket_type, &one, sizeof(one));
  }  

  if (options & OPT_INTERVAL)
  {
    ping->ping_interval = interval;
  }  


  while (argc --)
  {
    ping_echo(*argv ++);
    ping_reset(ping);
  }

  
  free (ping);
  free (data_buffer);

  return status;

}




static size_t _ping_packetsize (PING * p);

size_t
_ping_packetsize (PING * p)
{
  if (p->ping_type == ICMP_TIMESTAMP || p->ping_type == ICMP_TIMESTAMPREPLY)
    return ICMP_TSLEN;

  if (p->ping_type == ICMP_ADDRESS || p->ping_type == ICMP_ADDRESSREPLY)
    return ICMP_MASKLEN;

  return PING_HEADER_LEN + p->ping_datalen;
}







int
icmp_generic_decode (unsigned char * buffer, size_t bufsize,
         struct ip **ipp, icmphdr_t ** icmpp)
{
  size_t hlen;
  unsigned short cksum;
  struct ip *ip;
  icmphdr_t *icmp;

  /* IP header */
  ip = (struct ip *) buffer;
  hlen = ip->ip_hl << 2;
  if (bufsize < hlen + ICMP_MINLEN)
    return -1;

  /* ICMP header */
  icmp = (icmphdr_t *) (buffer + hlen);

  /* Prepare return values */
  *ipp = ip;
  *icmpp = icmp;

  /* Recompute checksum */
  cksum = icmp->icmp_cksum;
  icmp->icmp_cksum = 0;
  icmp->icmp_cksum = icmp_cksum ((unsigned char *) icmp, bufsize - hlen);
  if (icmp->icmp_cksum != cksum)
    return 1;
  return 0;
}

int
icmp_echo_encode (unsigned char * buffer, size_t bufsize, int ident, int seqno)
{
  return icmp_generic_encode (buffer, bufsize, ICMP_ECHO, ident, seqno);
}


int
icmp_echo_decode (unsigned char * buffer, size_t bufsize,
      struct ip **ipp, icmphdr_t ** icmpp)
{
  return icmp_generic_decode (buffer, bufsize, ipp, icmpp);
}


int 
ping_run(PING *ping, int (*finish)())
{   
    struct icmp sendicmp;

    for (i = 0; i < NUM; i ++)
     {
        nsend ++;
        memset(&sendicmp, 0, ICMP_SIZE);


     } 
    for (i = 0; i < NUM; i++) {
      nsend ++;
      memset()
    }
   //循环发送报文、接收报文 
    for(i = 0; i < NUM; i++){
        nsend++;  // 发送次数加1
        memset(&sendicmp, 0, ICMP_SIZE);
        pack(&sendicmp, nsend);

        if(sendto(p->ping_fd, &sendicmp, ICMP_SIZE, 0, (struct sockaddr)* ) &p->ping_dest.ping_sockaddr, sizeof(struct sockaddr_in)){
            log_error("send to error \n")
            continue
        }

        if (n = ping_recv(p)) {
            log_error("recvfrom error \n")
        }

    }

  ping_unset_data (ping);

  if (finish)
    return (*finish) ();
  return 0;

}


int
send_echo (PING * ping)
{
  size_t off = 0;
  int rc;

  if (PING_TIMING (data_length))
    {
      struct timeval tv;
      gettimeofday (&tv, NULL);
      ping_set_data (ping, &tv, 0, sizeof (tv), USE_IPV6);
      off += sizeof (tv);
    }
  if (data_buffer)
    ping_set_data (ping, data_buffer, off,
       data_length > off ? data_length - off : data_length,
       USE_IPV6);

  rc = ping_xmit (ping);
  if (rc < 0)
    error (EXIT_FAILURE, errno, "sending packet");

  return rc;
}



void pack(struct icmp * icmp, int sequence){
    icmp->type = ICMP_ECHO;
    icmp->code = 0;
    icmp->checksum = 0;
    icmp->id = getpid();
    icmp->sequence = sequence;
    gettimeofday(&icmp->timestamp, 0);
    icmp->checksum = checkSum((USHORT *)icmp, ICMP_SIZE);
}



void
sig_int (int signal _GL_UNUSED_PARAMETER)
{
  stop = 1;
}





void
ping_set_sockope(PING *ping, int opt, void *val, int valsize)
{
  setsockopt(ping->ping_fd, SOL_SOCKET, opt, (char *)&val, valsize);
}

int (*decode_type(const char *arg))(char *hostname)
{
	int (*ping_type)(char *hostname);
	if (strcasecmp(arg, "echo") ==0)
		ping_type = ping_echo;;
	return ping_type;
}



size_t
ping_cvt_number (const char *optarg, size_t maxval, int allow_zero)
{
  char *p;
  unsigned long int n;

  n = strtoul (optarg, &p, 0);
  if (*p)
    log_error("invalid value (`%s' near `%s')", optarg, p); 

  if (n == 0 && !allow_zero)
    log_error("option value too small: %s", optarg);

  if (maxval && n > maxval)
    log_error("option value too big: %s", optarg); 



  return n;
}



static errno_t 
parse_opt(int argc, char **argv)
{
    int oc;                     /*选项字符 */
    char *b_opt_arg;            /*选项参数字串 */
    while((oc = getopt(argc, argv, "c:nv")) != -1)
    {
        switch(oc)
        {
            case 'c':
            b_opt_arg = optarg;
             log_info("the ping  count is %s", b_opt_arg);
            count = ping_cvt_number (b_opt_arg, 0, 1);
            log_info("the ping  count is %zd", count);
            break;

            case 'n': 
            options |= OPT_NUMERIC;
            break;

   

            case 'v':
            options |= OPT_VERBOSE;
            break;

            case ARG_ECHO:
            ping_type = decode_type("echo");

            case ARG_TIMESTAMP:
            ping_type = decode_type ("timestamp");
            break;

            case ARG_ADDRESS:
            ping_type = decode_type ("address");
            break;

            case ARG_ROUTERDISCOVERY:
            ping_type = decode_type ("router");
            break;

            case ARG_TTL:
            b_opt_arg = optarg;
            ttl = ping_cvt_number (b_opt_arg, 255, 0);
            break;
        }
    }    
    return 0;
}


int 
ping_set_dest(PING *ping, char *host)
{
  int rc;
  struct addrinfo *hints, *res;
  memset (&hints, 0, sizeof (hints));

  hints.ai_family = AF_INET;
  hints.ai_flags = AI_CANONNAME;

  rc = getaddrinfo(hostname, NULL, &hints, &res);

  if （rc）
    return 1;  

  memcpy (&ping->ping_dest.ping_sockaddr, res->ai_addr, res->ai_addrlen);
  return 0;
  

  struct hostent *hp;

  hp = gethostbyname (p);

  return 0;

}




