//audio_rtp_session.h
#ifndef __AUDIO_RTP_SESSION_H__
#define __AUDIO_RTP_SESSION_H__

#include <NETEC/NETEC_Export.h>

typedef void (*on_audio_rtp_session_rcvd_rtp_packet_f)(void*user_data,unsigned char*rtp_packet_data,int rtp_packet_len,unsigned char payload_type,int rtp_header_len,unsigned short seq_num,unsigned long timestamp);
typedef void (*on_audio_rtp_session_sending_packet_f)(void*user_data,unsigned char*packet_data,int packet_len,const void*remote_addr,int remote_addr_len);

#ifdef __cplusplus
extern "C" NETEC_API void*audio_rtp_session_create(void*user_data,on_audio_rtp_session_rcvd_rtp_packet_f on_rcvd_rtp_packet,on_audio_rtp_session_sending_packet_f on_sending_packet);
extern "C" NETEC_API void*audio_rtp_session_create_ext(void*user_data,on_audio_rtp_session_rcvd_rtp_packet_f on_rcvd_rtp_packet,on_audio_rtp_session_sending_packet_f on_sending_packet);
extern "C" NETEC_API void audio_rtp_session_destroy(void*handle);

extern "C" NETEC_API int audio_rtp_session_open(void*handle,const char*local_ip,unsigned short local_port,unsigned char payload_type,const char*payload_name);
extern "C" NETEC_API void audio_rtp_session_close(void*handle);
extern "C" NETEC_API void audio_rtp_session_add_remote(void*handle,const char*remote_ip,unsigned short remote_port);
extern "C" NETEC_API void audio_rtp_session_send_rtp_packet(void*handle,unsigned char*rtp_packet_data,int rtp_packet_len);
extern "C" NETEC_API void audio_rtp_session_on_rcvd_packet(void*handle,unsigned char*packet_data,int packet_len,const void*remote_addr,int remote_addr_len);
extern "C" NETEC_API void audio_rtp_session_do_check(void*handle);
#else
NETEC_API void*audio_rtp_session_create(void*user_data,on_audio_rtp_session_rcvd_rtp_packet_f on_rcvd_rtp_packet,on_audio_rtp_session_sending_packet_f on_sending_packet);
NETEC_API void*audio_rtp_session_create_ext(void*user_data,on_audio_rtp_session_rcvd_rtp_packet_f on_rcvd_rtp_packet,on_audio_rtp_session_sending_packet_f on_sending_packet);
NETEC_API void audio_rtp_session_destroy(void*handle);

NETEC_API int audio_rtp_session_open(void*handle,const char*local_ip,unsigned short local_port,unsigned char payload_type,const char*payload_name);
NETEC_API void audio_rtp_session_close(void*handle);
NETEC_API void audio_rtp_session_add_remote(void*handle,const char*remote_ip,unsigned short remote_port);
NETEC_API void audio_rtp_session_send_rtp_packet(void*handle,unsigned char*rtp_packet_data,int rtp_packet_len);
NETEC_API void audio_rtp_session_on_rcvd_packet(void*handle,unsigned char*packet_data,int packet_len,const void*remote_addr,int remote_addr_len);
NETEC_API void audio_rtp_session_do_check(void*handle);
#endif

#endif
