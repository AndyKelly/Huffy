/*
 * HuffyServer.cpp
 *
 *  Created on: Jan 10, 2013
 *      Author: Andy Kelly
 */

#include "HuffyServer.h"
#include "CommunicationCodes.h"
#include <string>
#include <iostream>

HuffyServer::HuffyServer() {
}

HuffyServer::~HuffyServer() {
}

bool HuffyServer::Initalise()
{
	bool SetupResult = false;

	try
	{
		// Create the socket
		m_ServerSocket = new ServerSocket(30000);

		while (!SetupResult)
		{
			m_ServerSocket->accept(new_sock);
			m_ConectionSocket = &new_sock;
			try
			{
				while (!SetupResult)
				{
					std::string data;
					*m_ConectionSocket >> data;
					if (data == CLIENT_REQUEST)
					{
						SetupResult = true;
					}
					SendUpdate(SERVER_RESPONSE);
				}
			}
			catch (SocketException&) {}

		}
	}
	catch (SocketException& e)
	{
		std::cout << "Socket exception was caught:" << e.description();
	}

	return SetupResult;
}

void HuffyServer::ServerWaitForClientToRequestUpdate()
{
	//Todo, should be multi-threaded to avoid hanging while waiting for client.
	std::string Request = "";
	while (Request != UPDATE_REQUEST)
	{
		try
		{
			*m_ConectionSocket >> Request;
		}
		catch (SocketException& e)
		{
			std::cout << "Socket exception was caught:" << e.description();
			;
			Request = UPDATE_REQUEST;
		}
		std::cout << "\nFrom client:" + Request;
	}
	SendUpdate(UPDATE_RESPONSE + m_Update);
}

void HuffyServer::SendUpdate(std::string Update)
{
	try
	{
		*m_ConectionSocket << Update;
	}
	catch (SocketException&) {
	}
}

void HuffyServer::AssignUpdate(std::string NewUpdate)
{
	m_Update = NewUpdate;
}
