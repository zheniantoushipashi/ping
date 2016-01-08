#include "ping.h"


extern int ping_echo (char *hostname);

extern char *optarg;

int (*ping_type) (char *hostname) = ping_echo;

int (*decode_type (const char *arg)) (char *hostname);



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
	log_info("hello world  dsfssfsf sdffsdsdsd");
  parse_opt(argc, argv);

  ping = ping_init(ICMP_ECHO, getpid())

  if (ping == NULL)
    /* ping_init() prints our error message.  */
    exit (EXIT_FAILURE);

  
	return 1;
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



