/*
 ============================================================================
 Name        : ipcsocket.c
 Author      : Przemyslaw Zygmunt p.zygmunt@acsoftware.pl [AC SOFTWARE]
 Version     : 1.0
 Copyright   : GPLv2
 ============================================================================
*/

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

#include "log.h"
#include "tools.h"

typedef struct {

	int sfd;
	struct sockaddr_un saun, fsaun;

}TSuplaIPC_socket;

void *ipcsocket_init(const char *address) {

	int sfd;
	TSuplaIPC_socket *ipc;

	if ( address == 0 || strlen(address) == 0 ) {
		supla_log(LOG_ERR, "IPC unknown address");
	    return 0;
	}

	if ( strlen(address) > 107 ) {
		supla_log(LOG_ERR, "IPC address too long");
	    return 0;
	}

	if ( ( sfd = socket(AF_UNIX, SOCK_STREAM, 0) ) < 0 ) {
		supla_log(LOG_ERR, "Can't create ipc socket");
	    return 0;
	}


	if ( st_file_exists(address) )
		unlink(address);

	ipc = malloc(sizeof(TSuplaIPC_socket));
	memset(ipc, 0, sizeof(TSuplaIPC_socket));
	ipc->sfd = -1;

	ipc->saun.sun_family = AF_UNIX;
	strcpy(ipc->saun.sun_path, address);

	if (bind(sfd, (struct sockaddr *)&ipc->saun, sizeof(ipc->saun)) == -1) {
		free(ipc);
		close(sfd);
		supla_log(LOG_ERR, "Can't bind ipc socket");
		return 0;
	}

	if ( listen(sfd, 5) == -1 ) {
		free(ipc);
		close(sfd);
		supla_log(LOG_ERR, "IPC listen error");
		return 0;
	} else {
		chmod(address, 0777);
	}

	ipc->sfd = sfd;

	return ipc;
}

int ipcsocket_accept(void *_ipc) {
	assert(_ipc != 0);

	socklen_t fromlen = 0;
	TSuplaIPC_socket *ipc = (TSuplaIPC_socket *)_ipc;
	int client_sd = accept(ipc->sfd, (struct sockaddr *)&ipc->fsaun, &fromlen);

	if ( client_sd != -1 )
		fcntl(client_sd, F_SETFL, O_NONBLOCK);

	return client_sd;
}

void ipcsocket_close(void *_ipc) {

	TSuplaIPC_socket *ipc = (TSuplaIPC_socket *)_ipc;

	assert(_ipc != 0);

	if ( ipc->sfd != -1 ) {
		close(ipc->sfd);
		ipc->sfd = -1;

		if ( st_file_exists(ipc->saun.sun_path) )
			unlink(ipc->saun.sun_path);
	}

}

void ipcsocket_free(void *_ipc) {

	assert(_ipc != 0);

	ipcsocket_close(_ipc);
	free(_ipc);

}
