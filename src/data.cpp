/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:29:26 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/30 14:46:34 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::vector<std::string> parseCommand(std::string& command)
{
	std::vector<std::string>	commandArgs;
	size_t						start;
    
	std::cout << "command = " << command << std::endl;

	for (size_t i = 0; i < command.length(); i++)
	{
		while (i < command.length() && command[i] == ' ')
			i++;

		start = i;
		if (command[start] == ':')
		{
			commandArgs.push_back(command.substr(start, command.length() - start - 1));
			return commandArgs;
		}
		while (i < command.length() && command[i] != ' ' && command[i] != '\r')
			i++;
		if (start < i)
			commandArgs.push_back(command.substr(start, i - start));
	}

    return commandArgs;
}

void Server::manageCommand(Client& client, std::string& command)
{

	std::vector<std::string>	commandArgs;
	std::vector<std::string>	emptyPass; // au cas ou le client lance une commande avant PASS

	emptyPass.push_back("PASS");
	emptyPass.push_back("");
	commandArgs = parseCommand(command);

	for (std::vector<std::string>::iterator it = commandArgs.begin(); it != commandArgs.end(); it++)
		std::cout << YELLOW << *it << RESET << std::endl;
	std::cout << std::endl;

	// commandArgs.at(0) correspond au nom de la commande
	if (commandArgs.at(0) == "PASS")
		pass(client, commandArgs);
	else if (client.getPassOK() == 0 && commandArgs.at(0) != "CAP")
	{
		std::cout << "entree avec emptypass" << std::endl;
		pass(client, emptyPass);
	}
	else if (commandArgs.at(0) == "NICK")
		nick(client, commandArgs);
	else if (commandArgs.at(0) == "USER")
		user(client, commandArgs);
	else if (commandArgs.at(0) == "PING")
		pong(client, commandArgs);
	else if (commandArgs.at(0) == "QUIT")
		quit(client, commandArgs);
	else if (commandArgs.at(0) == "PRIVMSG")
		privmsg(client, commandArgs);
	else if (commandArgs.at(0) == "JOIN")
		join(client, commandArgs);
	else if (commandArgs.at(0) == "PART")
		part(client, commandArgs);
	// else if (commandArgs.at(0) == "MODE")
	// 	mode(client, params);
	else if (commandArgs.at(0) == "KICK")
		kick(client, commandArgs);
	else if (commandArgs.at(0) == "INVITE")
		invite(client, commandArgs);
	else if (commandArgs.at(0) == "TOPIC")
		topic(client, commandArgs);
	else if (commandArgs.at(0) == "OPER")
		oper(client, commandArgs);
	else if (commandArgs.at(0) == "KILL")
		kill(client, commandArgs);
		
	commandArgs.clear();
}

void Server::parseData(int& senderFd)
{
	int	bufferLength;
	
	for (int i = 0; this->bufferRead_[senderFd][i]; i++)
	{
		if (i != 0 && this->bufferRead_[senderFd][i] == '\n' && this->bufferRead_[senderFd][i - 1] == '\r')
		{
			this->commands_.push_back(this->bufferRead_[senderFd].substr(0, i));
			
			
			bufferLength = this->bufferRead_[senderFd].length();
			if (i < bufferLength - 1)
			{
				this->bufferRead_[senderFd] = this->bufferRead_[senderFd].substr(i + 1, bufferLength);
				i = 0;
			}
			else
			{
				this->bufferRead_[senderFd].clear();
				return ;
			}

		}
	}
	
	bufferLength = this->bufferRead_[senderFd].length();
	if (bufferLength == BUFFERSIZE)
	{
		this->bufferRead_[senderFd][bufferLength - 1] = '\n';
		this->bufferRead_[senderFd][bufferLength - 2] = '\r';
		this->commands_.push_back(this->bufferRead_[senderFd]);
		this->bufferRead_[senderFd].clear();
	}
}

void Server::readData(int& senderFd)
{
	int		bytesRead;
	char	buffer[BUFFERSIZE + 1];

	std::memset(buffer, 0, sizeof(buffer));
	bytesRead = recv(senderFd, buffer, BUFFERSIZE, 0);
	this->bufferRead_[senderFd] += buffer;
	if (bytesRead <= 0)
	{
		if (bytesRead == 0)
			std::cout << GREEN << "Client " << senderFd << " disconnected from server" << RESET << std::endl;
		endConnection(senderFd);
		if (bytesRead == -1)
			throw RecvFailed();
		return ;
	}
	
	std::cout << CYAN << this->bufferRead_[senderFd] << RESET;

	for (int i = 0; this->bufferRead_[senderFd][i]; i++)
	{
		if (this->bufferRead_[senderFd][i] == '\r' || this->bufferRead_[senderFd][i] == '\n')
			std::cout << RED << (int)this->bufferRead_[senderFd][i] << RESET << " ";
		else
			std::cout << (int)this->bufferRead_[senderFd][i] << " ";
	}
	std::cout << std::endl;
	
	std::cout << "bytes read = " << bytesRead << std::endl << std::endl;
}

void Server::sendData()
{
	char		buffer[BUFFERSIZE + 1];
	int			bytesSent;
	std::string	bufferStr;

	for (size_t i = 0; i < this->replies_.size(); i++)
	{
		if (this->replies_[i].message.length() >= BUFFERSIZE)
		{
			this->replies_[i].message[BUFFERSIZE - 1] = '\r';
			this->replies_[i].message[BUFFERSIZE] = '\n';
			this->replies_[i].message[BUFFERSIZE + 1] = 0;
		}

		// std::cout << "length reply = " << this->replies_[i].message.length() << std::endl;
		
		std::memset(buffer, 0, sizeof(buffer));
		std::strcpy(buffer, this->replies_[i].message.c_str());
		
		std::cout << YELLOW_BG << "[" << this->replies_[i].targetFd << "] is going to receive the following buffer" << RESET << std::endl << std::endl;
		std::cout << CYAN << buffer << RESET;
		
		bufferStr = buffer;
		bytesSent = send(this->replies_[i].targetFd, buffer, bufferStr.length(), 0);
		
		// // afficher le buffer en raw
		// for (int i = 0; buffer[i]; i++)
		// {
		// 	if (buffer[i] == '\r' || buffer[i] == '\n')
		// 		std::cout << RED << (int)buffer[i] << RESET << " ";
		// 	else
		// 		std::cout << (int)buffer[i] << " ";
		// }
		// std::cout << std::endl;
		
		std::cout << "bytes sent = " << bytesSent << std::endl << std::endl;
		

		if (bytesSent == -1)
		{
			endConnection(this->replies_[i].targetFd);
			std::cout << RED << "Error: Send failed for fd " << this->replies_[i].targetFd << RESET << std::endl;
		}
		if (this->replies_[i].status != STATUS_OK)
		{
			if (this->replies_[i].status == STATUS_AUTHFAILED)
				std::cout << GREEN << "Client " << this->replies_[i].targetFd << " failed auth" << RESET << std::endl;
			else
				std::cout << GREEN << "Client " << this->fdCli_[this->replies_[i].targetFd].getNickname() << " left server" << RESET << std::endl;
			endConnection(this->replies_[i].targetFd);
			break;
		}
	}
}

void Server::processData(int& senderFd)
{
	readData(senderFd);

	parseData(senderFd);

	for (size_t i = 0; i < this->commands_.size(); i++)
		manageCommand(this->fdCli_[senderFd], this->commands_[i]);
	this->commands_.clear();
	
	sendData();
	this->replies_.clear();
}
