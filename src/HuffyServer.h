/*
 * HuffyServer.h
 *
 *  Created on: Jan 10, 2013
 *      Author: hal
 */

#ifndef HUFFYSERVER_H_
#define HUFFYSERVER_H_
#include <string>
#include "ServerSocket.h"
#include "Socket.h"
#include "SocketException.h"

class HuffyServer {
public:
	HuffyServer();
	virtual ~HuffyServer();
	bool Initalise();
	void ServerWaitForClientToRequestUpdate();
	void AssignUpdate(std::string);
private:
	void SendUpdate(std::string);
	ServerSocket *m_ServerSocket;
	ServerSocket *m_ConectionSocket;
	ServerSocket new_sock;
	std::string m_Update;
};

#endif /* HUFFYSERVER_H_ */
