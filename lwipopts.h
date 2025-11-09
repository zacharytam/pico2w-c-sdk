#ifndef _LWIPOPTS_H
#define _LWIPOPTS_H

// Include the common minimal settings
#include "lwipopts_examples_common.h"

// Enable mDNS
#define LWIP_MDNS_RESPONDER 1
#define LWIP_IGMP 1
#define LWIP_NUM_NETIF_CLIENT_DATA 1
#define MDNS_RESP_USENETIF_EXTCALLBACK 1

// HTTPD features
#define LWIP_HTTPD_CGI 1
#define LWIP_HTTPD_SSI 1
#define LWIP_HTTPD_SSI_MULTIPART 1
#define LWIP_HTTPD_SUPPORT_POST 1
#define LWIP_HTTPD_SSI_INCLUDE_TAG 0

// Generated file containing HTML data
#define HTTPD_FSDATA_FILE "pico_fsdata.inc"

#endif
