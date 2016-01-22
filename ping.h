#ifndef PING_H
#define PING_H
#include "core.h"
#include "libping.h"
#include "icmp_address.h"
#include "icmp_cksum.h"
#include "icmp_echo.h"



typedef struct ping_data PING;

# define EXIT_FAILURE 1
#define DEFAULT_PING_COUNT 0

#define OPT_FLOOD       0x001
#define OPT_INTERVAL    0x002
#define OPT_NUMERIC     0x004
#define OPT_QUIET       0x008
#define OPT_RROUTE      0x010
#define OPT_VERBOSE     0x020
#define OPT_IPTIMESTAMP 0x040
#define OPT_FLOWINFO    0x080
#define OPT_TCLASS      0x100

#define SOPT_TSONLY     0x001
#define SOPT_TSADDR     0x002
#define SOPT_TSPRESPEC  0x004

# define EXIT_FAILURE 1




#endif