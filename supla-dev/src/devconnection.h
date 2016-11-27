/*
 ============================================================================
 Name        : dev-connection.h
 Author      : Przemyslaw Zygmunt p.zygmunt@acsoftware.pl [AC SOFTWARE]
 Version     : 1.0
 Copyright   : GPLv2
 ============================================================================
 */

#ifndef DEV_CONNECTION_H_
#define DEV_CONNECTION_H_

#ifdef __cplusplus
extern "C" {
#endif

void* devconnection_start(void);
void devconnection_stop(void *dconn_thread);

#ifdef __cplusplus
}
#endif

#endif /* DEV_CONNECTION_H_ */
