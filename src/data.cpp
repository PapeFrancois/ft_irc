/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:29:26 by hepompid          #+#    #+#             */
/*   Updated: 2024/11/26 12:42:21 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::string Server::extractCommandName(std::string command)
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

// ATTENTION : PLUS TARD, CHECKER CORRECTEMENT L'INPUT (CLIENT ET NC POUR TOUT BIEN PARSER)

void Server::manageCommand(std::string& command)
{
	std::string	commandName;

	std::cout << YELLOW << "Command parsed : " << command << RESET;
	commandName = extractCommandName(command);
	std::cout << YELLOW << "Command name : " << commandName << RESET << std::endl;

	if (command == "CAP LS 302\r\n")
		cap();
	// if (commandName == "PASS")
	// {}
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

void Server::readData(int senderFd)
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

void Server::sendData(int senderFd)
{
	// std::cout << "replies size = " << this->replies_.size() << std::endl;
	for (size_t i = 0; i < this->replies_.size(); i++)
	{
		std::memset(this->bufferWrite_, 0, sizeof(this->bufferWrite_));
		std::strcpy(this->bufferWrite_, this->replies_[i].c_str());
		
		if (send(senderFd, bufferWrite_, BUFFERSIZE, 0) == -1)
		{
			endConnection(senderFd);
			throw SendFailed();
		}
	}
}

void Server::processData(int senderFd)
{
	readData(senderFd);

	for (size_t i = 0; i < this->commands_.size(); i++)
		manageCommand(this->commands_[i]);
	this->commands_.clear();
	
	sendData(senderFd);
	this->replies_.clear();
}
