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
		//Todo, this value should be configurable, in HuffyConstants.h?
		//Fix in next iteraltion
		m_ServerSocket = new ServerSocket(30000);
		std::cout << "\nSetting up Server, waiting on client\n";
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
	std::cout << "\nClient has connected\n";
	return SetupResult;
}

void HuffyServer::ServerWaitForClientToRequestUpdate()
{
	//Todo, should be multi-threaded to avoid hanging while waiting for client.
	std::string Request = "";
	std::cout <<"\nWaiting for client to request update\n";
	while (Request != UPDATE_REQUEST)
	{

		try
		{
			*m_ConectionSocket >> Request;
		}
		catch (SocketException& e)
		{
			std::cout << "Socket exception was caught:" << e.description();

			Request = UPDATE_REQUEST;
		}

	}
	std::cout << "\nMessage recieved from client:" + Request;
	std::cout << "\nnote: U is the value for UPDATE_REQUEST defined in the Comunication codes header";
		std::cout <<"\nClient requested update\n";
	std::cout <<"\nUpdate is:" << (UPDATE_RESPONSE + m_Update) << ".\n";
	SendUpdate(UPDATE_RESPONSE + m_Update);
}

void HuffyServer::SendUpdate(std::string Update)
{
	std::cout <<"\nTrying to send update\n";
	try
	{
		*m_ConectionSocket << Update;
	}
	catch (SocketException& e)
	{
		std::cout << "Socket exception was caught:" << e.description();
	}
}

void HuffyServer::AssignUpdate(std::string NewUpdate)
{
	std::cout <<"\nAssigning update\n";
	m_Update = NewUpdate;
}
