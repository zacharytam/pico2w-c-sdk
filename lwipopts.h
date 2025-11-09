#ifndef _LWIPOPTS_H
#define _LWIPOPTS_H

#include "lwipopts_examples_common.h"

#define LWIP_HTTPD_CGI 1
#define LWIP_HTTPD_SSI 1
#define LWIP_HTTPD_SSI_MULTIPART 1
#define LWIP_HTTPD_SUPPORT_POST 1
#define LWIP_MDNS_RESPONDER 1
#define LWIP_IGMP 1

#define MEMP_NUM_SYS_TIMEOUT (LWIP_NUM_SYS_TIMEOUT_INTERNAL + 3)
#define MEMP_NUM_TCP_PCB 12

#define HTTPD_FSDATA_FILE "pico_fsdata.inc"

#endif
