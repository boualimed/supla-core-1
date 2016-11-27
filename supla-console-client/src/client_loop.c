/*
 ============================================================================
 Name        : client_loop.c
 Author      : Przemyslaw Zygmunt p.zygmunt@acsoftware.pl [AC SOFTWARE]
 Version     : 1.0
 Copyright   : GPLv2
 ============================================================================
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "supla-client-lib/supla-client.h"
#include "supla-client-lib/sthread.h"
#include "supla-client-lib/tools.h"
#include "supla-client-lib/log.h"
#include "client_loop.h"
#include "clientcfg.h"

void client_loop_on_registererror(void *_suplaclient, void *sthread, int code) {

	if ( code == SUPLA_RESULTCODE_BAD_CREDENTIALS ) {

		st_app_terminate = 1;
		sthread_terminate(sthread);

	} else {
		usleep(5000000);
	}

}

void client_loop_location_update(void *_suplaclient, void *sthread, TSC_SuplaLocation *location) {

	supla_log(LOG_DEBUG, "Location #%i: %s EOL=%i", location->Id, location->Caption, location->EOL);

}

void client_loop_channel_update(void *_suplaclient, void *sthread, TSC_SuplaChannel *channel) {

	double temp;
	if ( channel->Func == 40 ) {
		memcpy(&temp, channel->value.value, sizeof(double));
		supla_log(LOG_DEBUG, "-> Channel #%i: %f st. EOL=%i", channel->Id, temp, channel->EOL);
	} else {
		supla_log(LOG_DEBUG, "Channel #%i: %s LocationID=%i, Function=%i, online=%i, value[0]: %i sub_value[0]: %i, EOL=%i", channel->Id,
				channel->Caption,
				channel->LocationID,
				channel->Func,
				channel->online,
				channel->value.value[0],
				channel->value.sub_value[0],
				channel->EOL);
	}


}

void client_loop_on_event(void *_suplaclient, void *user_data, TSC_SuplaEvent *event) {

	supla_log(LOG_DEBUG, "Event: %i, SenderID: %i, SenderName: %s", event->Event, event->SenderID, event->SenderName);

}

void client_loop_channel_value_update(void *_suplaclient, void *sthread, TSC_SuplaChannelValue *channel_value) {

	double temp;
	if ( channel_value->Id == 82 || channel_value->Id == 83 ||  channel_value->Id == 97 ||  channel_value->Id == 127 ) {
		memcpy(&temp, channel_value->value.value, sizeof(double));
		supla_log(LOG_DEBUG, "Channel #%i: %f st.", channel_value->Id, temp);
	} else {
	supla_log(LOG_DEBUG, "Channel #%i: Value: online %i, value[0]: %i, sub_value[0]: %i, EOL: %i", channel_value->Id,
			channel_value->online,
			channel_value->value.value[0],
			channel_value->value.sub_value[0],
			channel_value->EOL);
	}

}

void *client_loop_init(void *sthread) {

	TSuplaClientCfg scc;
	supla_client_cfginit(&scc);

	snprintf(scc.Name, SUPLA_CLIENT_NAME_MAXSIZE, "Console client");
	snprintf(scc.SoftVer, SUPLA_SOFTVER_MAXSIZE, "1.0-Linux");

	if ( cfg_pwd != NULL )
		snprintf(scc.AccessIDpwd, SUPLA_ACCESSID_PWD_MAXSIZE, "%s", cfg_pwd);

	scc.AccessID = cfg_aid;
	memcpy(scc.clientGUID, cfg_client_GUID, SUPLA_GUID_SIZE);

	scc.host = cfg_host;
	if ( cfg_ssl_enabled ) {
		scc.ssl_port = cfg_port;
	} else {
		scc.tcp_port = cfg_port;
	}
	scc.ssl_enabled = cfg_ssl_enabled;
	scc.user_data = sthread;
	scc.cb_on_registererror = &client_loop_on_registererror;
	scc.cb_location_update = &client_loop_location_update;
	scc.cb_channel_update = &client_loop_channel_update;
	scc.cb_channel_value_update = &client_loop_channel_value_update;
	scc.cb_on_event = &client_loop_on_event;

	return supla_client_init(&scc);
}


void client_loop(void *user_data, void *sthread) {

	void *sclient = client_loop_init(sthread);

	if ( sclient == NULL ) {
		st_app_terminate = 1;
		return;
	}

	if ( user_data )
		*(void**)user_data = sclient;

	while(sthread_isterminated(sthread) == 0) {

		supla_log(LOG_INFO, "Connecting...");

		if ( 0 == supla_client_connect(sclient) ) {
			usleep(2000000);
		} else {

			while( sthread_isterminated(sthread) == 0
				   && supla_client_iterate(sclient, 10000000) == 1 ) {
			}

		}
	}

	if ( user_data )
		*(void**)user_data =NULL;


	supla_client_free(sclient);


}
