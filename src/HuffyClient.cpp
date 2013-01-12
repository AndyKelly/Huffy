/*
 * HuffyClient.cpp
 *
 *  Created on: Jan 10, 2013
 *      Author: hal
 */

#include "HuffyClient.h"
#include "CommunicationCodes.h"
#include "ClientSocket.h"
#include <string>
#include <iostream>

HuffyClient::HuffyClient(){
	m_Initalised = false;

}

HuffyClient::~HuffyClient() {
	delete m_ClientSocket;
}

bool HuffyClient::Initalise(std::string Address)
{
	try {
		m_ClientSocket = new ClientSocket(Address, 30000);

		std::string reply;

		try
		{
			*m_ClientSocket << CLIENT_REQUEST;
			*m_ClientSocket >> reply;
			if (reply == SERVER_RESPONSE)
			{
				std::cout << "\nConnected to server successfully\n";
				m_Initalised = true;
			}
			else
			{
				std::cout << "\nFailed to connect to the server\n";
			}
		}
		catch (SocketException& e)
		{
			std::cout << "\nSocket exception thrown: " + e.description();
		}
	}

	catch (SocketException& e) {
		std::cout << "Exception was caught:" << e.description() << "\n";
	}
return false;
}

std::string HuffyClient::RequestUpdate()
{

	if(m_Initalised)
	{
		std::string reply;

			try
			{
				*m_ClientSocket << UPDATE_REQUEST;
				*m_ClientSocket >> reply;
				if (reply[0] == UPDATE_RESPONSE[0])
				{
					return reply;
				}
				else
				{
					std::cout << "\nFailed to get update from server\n";
					return ERROR;
				}
			}
			catch (SocketException& e)
			{
				std::cout << "\nSocket exception thrown: " + e.description();
			}
	}
}
