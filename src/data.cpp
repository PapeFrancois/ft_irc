/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:29:26 by hepompid          #+#    #+#             */
/*   Updated: 2024/11/28 11:59:39 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::string Server::extractCommandName(std::string& command)
{
	std::string	commandName;
	char		tempBuffer[BUFFERSIZE + 1];

	std::memset(tempBuffer, 0, sizeof(tempBuffer));
	for (int i = 0; command[i] != '\r'; i++)
	{
		if (command[i] == ' ')
			break;
		tempBuffer[i] = command[i];
	}
	commandName = tempBuffer;
	return commandName;
}

std::string Server::extractParams(std::string& command)
{
	std::string	params;
	char		tempBuffer[BUFFERSIZE + 1];
	int			j;
	
	std::memset(tempBuffer, 0, sizeof(tempBuffer));
	j = 0;
	for (int i = command.find(' ') + 1; command[i] != '\r'; i++)
	{
		tempBuffer[j] = command[i];
		j++;
	}
	params = tempBuffer;
	return params;
}

// ATTENTION : PLUS TARD, CHECKER CORRECTEMENT L'INPUT (CLIENT ET NC POUR TOUT BIEN PARSER)

void Server::manageCommand(Client& client, std::string& command)
{
	std::string	commandName;
	std::string	params;

	std::cout << YELLOW << "Command parsed : " << command << RESET;
	commandName = extractCommandName(command);
	std::cout << YELLOW << "Command name : " << commandName << RESET << std::endl;
	params = extractParams(command);
	std::cout << YELLOW << "Params : " << params << RESET << std::endl;
	// std::cout << "auth = " << client.getAuth() << std::endl;

	if (commandName == "CAP")
		cap(params);
	else if (commandName == "PASS")
		pass(client, params);
	else if (client.getAuth() == 0 && commandName != "JOIN")
		pass(client, "");
}

void Server::parseData()
{
	char	tempBuffer[BUFFERSIZE + 1];
	int		j;
	
	std::memset(tempBuffer, 0, sizeof(tempBuffer));
	j = 0;
	for (int i = 0; this->bufferRead_[i]; i++)
	{
		// std::cout << (int)this->bufferRead_[i] << std::endl;
		tempBuffer[j] = this->bufferRead_[i];
		if (this->bufferRead_[i] == '\n' && this->bufferRead_[i - 1] == '\r')
		{
			this->commands_.push_back(tempBuffer);
			std::memset(tempBuffer, 0, sizeof(tempBuffer));
			j = -1;
		}
		j++;
	}
	if (j >= 2 && (tempBuffer[j - 1] != '\n' || tempBuffer[j - 2] != '\r'))
	{
		tempBuffer[j - 1] = '\n';
		tempBuffer[j - 2] = '\r';
		this->commands_.push_back(tempBuffer);
	}
}

void Server::readData(int& senderFd)
{
	int		bytesRead;

	std::memset(this->bufferRead_, 0, sizeof(this->bufferRead_));
	bytesRead = recv(senderFd, this->bufferRead_, BUFFERSIZE, 0);
	if (bytesRead <= 0)
	{
		endConnection(senderFd);
		if (bytesRead == -1)
			throw RecvFailed();
		else if (bytesRead == 0)
			std::cout << GREEN << "Client " << senderFd << " disconnected from server" << RESET << std::endl;
		return ;
	}
	
	std::cout << YELLOW << "Buffer received with recv : " << this->bufferRead_ << RESET;
	parseData();
	std::cout << "bytes read = " << bytesRead << std::endl;
}

void Server::sendData(int& senderFd)
{
	// std::cout << "replies size = " << this->replies_.size() << std::endl;
	for (size_t i = 0; i < this->replies_.size(); i++)
	{
		std::memset(this->bufferWrite_, 0, sizeof(this->bufferWrite_));
		std::strcpy(this->bufferWrite_, this->replies_[i].c_str());
		
		std::cout << YELLOW << "Message to send : " << this->bufferWrite_ << RESET;
		
		if (send(senderFd, bufferWrite_, BUFFERSIZE, 0) == -1)
		{
			endConnection(senderFd);
			throw SendFailed();
		}
		if (this->replies_[i] == ERR_PASSWDMISMATCH)
		{
			endConnection(senderFd);
			std::cout << GREEN << "Client " << senderFd << " failed auth" << RESET << std::endl;
			break;
		}
	}
}

void Server::processData(int& senderFd)
{
	readData(senderFd);

	for (size_t i = 0; i < this->commands_.size(); i++)
		manageCommand(this->clients_[senderFd], this->commands_[i]);
	this->commands_.clear();
	
	sendData(senderFd);
	this->replies_.clear();
}
