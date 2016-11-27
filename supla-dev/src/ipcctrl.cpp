/*
 ============================================================================
 Name        : ipcctrl.cpp
 Author      : Przemyslaw Zygmunt p.zygmunt@acsoftware.pl [AC SOFTWARE]
 Version     : 1.0
 Copyright   : GPLv2
 ============================================================================
 */


#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <string.h>

#include "ipcctrl.h"
#include "sthread.h"
#include "log.h"
#include "channel-io.h"

const char hello[] = "SUPLA DEVICE CTRL\n";
const char cmd_channel_get_hivalue[] = "CHANNEL-GET-HIVALUE:";
const char cmd_channel_set_hivalue[] = "CHANNEL-SET-HIVALUE:";
const char cmd_channel_get_type[] = "CHANNEL-GET-TYPE:";


svr_ipcctrl::svr_ipcctrl(int sfd) {
	this->sfd = sfd;

	this->eh = eh_init();
	eh_add_fd(eh, sfd);
}

bool svr_ipcctrl::match_command(const char *cmd, int len) {

	if ( len > (int)strlen(cmd)
						 && memcmp(buffer, cmd, strlen(cmd)) == 0
						 && buffer[len-1] == '\n' ) {

		buffer[len-1] = 0;
		return true;
	}

	return false;
}

void svr_ipcctrl::send_result(const char *result) {

	snprintf(buffer, 255, "%s\n", result);
	send(sfd, buffer, strlen(buffer), 0);

}

void svr_ipcctrl::send_result(const char *result, int i) {

	snprintf(buffer, 255, "%s%i\n", result, i);
	send(sfd, buffer, strlen(buffer), 0);

}

void svr_ipcctrl::send_result(const char *result, double i) {

	snprintf(buffer, 255, "%s%f\n", result, i);
	send(sfd, buffer, strlen(buffer), 0);

}

void svr_ipcctrl::execute(void *sthread) {

	if ( sfd == -1 )
		return;

	int len;

	struct timeval last_action;
	gettimeofday(&last_action, NULL);

	send(sfd, hello, sizeof(hello), 0);

	while(sthread_isterminated(sthread) == 0) {
		eh_wait(eh, 1000000);

		if ( (len = recv(sfd, buffer, sizeof(buffer), 0)) != 0 ) {

			if ( len > 0 ) {

				buffer[255] = 0;

				if ( match_command(cmd_channel_get_hivalue, len) ) {

					char hi;
					int number = 255;
					sscanf (&buffer[strlen(cmd_channel_get_hivalue)], "%i", &number);

					if (  channelio_get_hi_value(number, &hi) == 1 ) {
						send_result("HIVALUE:", hi == 1 ? 1 : 0);
					} else {
						send_result("ERR", number);
					}

				} else if ( match_command(cmd_channel_get_type, len) ) {

					int number = 255;
					sscanf (&buffer[strlen(cmd_channel_get_type)], "%i", &number);
					send_result("TYPE:", channelio_get_type(number));

				} else if ( match_command(cmd_channel_set_hivalue, len) ) {

					int hi = 0;
					int number = 255;
					unsigned int timems = 0;

					sscanf (&buffer[strlen(cmd_channel_set_hivalue)], "%i,%i,%i", &number, &hi, &timems);

					if (  channelio_set_hi_value(number, hi == 1 ? 1 : 0, timems) == 1 ) {
						send_result("OK");
					} else {
						send_result("ERR", number);
					}
				}


			}

		} else {
			sthread_terminate(sthread);
		}


		struct timeval now;
		gettimeofday(&now, NULL);

		if ( now.tv_sec-last_action.tv_sec >= 5 ) {
			sthread_terminate(sthread);
			break;
		}
	};

}

svr_ipcctrl::~svr_ipcctrl() {
	if ( sfd != -1 )
		close(sfd);

	eh_free(eh);
}

