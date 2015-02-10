//AUDEC_config.h
#ifndef __AUDEC_CONFIG_H__
#define __AUDEC_CONFIG_H__


#define _USED_STATIC_DTMF

#define _USED_G711
#define _USED_GSM
//#define _USED_G7231
#define _USED_G729A
#define _USED_G722
#define _USED_ADPCM

#ifndef _WIN32_WCE

#define _USED_ILBC


#endif

#define _USED_G7222
#define _USED_EVRC
//#define _USED_MP3
#define _USED_SPEEX

#define _USED_G7221
#define _USED_G719
#define _USED_OPUS

//#define _DEMO
#ifndef _DEMO

#ifdef WIN32
#ifndef WINCE
#define _USED_HiKG726
#endif
#endif
#define _USED_AAC
//


#endif

#endif
