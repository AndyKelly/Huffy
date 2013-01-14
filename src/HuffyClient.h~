/*
 * HuffyClient.h
 *
 *  Created on: Jan 10, 2013
 *      Author: hal
 */

#ifndef HUFFYCLIENT_H_
#define HUFFYCLIENT_H_
#include <string>
#include "ClientSocket.h"
#include "Socket.h"
#include "SocketException.h"

class HuffyClient {
public:
	HuffyClient();
	virtual ~HuffyClient();
	bool Initalise(std::string);
	std::string RequestUpdate();
private:
	ClientSocket *m_ClientSocket;
	bool m_Initalised;
};

#endif /* HUFFYClient_H_ */
