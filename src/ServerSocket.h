/*
 * ServerSocket.h
 *	Note:	Not my work, all credit goes to Rob Tougher
 *	Taken From: http://linuxgazette.net/issue74/tougher.html
 */
#ifndef ServerSocket_class
#define ServerSocket_class

#include "Socket.h"

class ServerSocket: private Socket
{
public:

	ServerSocket(int port);
	ServerSocket() {};
	virtual ~ServerSocket();

	const ServerSocket& operator <<(const std::string&) const;
	const ServerSocket& operator >>(std::string&) const;

	void accept(ServerSocket&);

};

#endif
