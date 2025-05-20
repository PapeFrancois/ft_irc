/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:29:26 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/20 15:05:05 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::string Server::extractCommandName(std::string& command)
{
	int	start;
	int	end;
	
	start = 0;
	while (command[start] == ' ')
		start++;
	
	end = start;
	while (command[end] != ' ' && command[end] != '\r')
		end++;

	return command.substr(start, end - start);
}

std::string Server::extractParams(std::string& command)
{
	int			start;
	int			end;
	
	start = 0;
	while (command[start] == ' ')
		start++;
	while (command[start] != ' ' && command[start] != '\r')
		start++;
	if (command[start] == '\r')
		return "";
	while (command[start] == ' ')
		start++;
		
	end = start;
	while (command[end] != '\r')
		end++;

	return command.substr(start, end - start);
}

void Server::manageCommand(Client& client, std::string& command)
{
	std::string	commandName;
	std::string	params;

	std::cout << YELLOW << "Command parsed : " << command << RESET << std::endl;
	commandName = extractCommandName(command);
	std::cout << YELLOW << "Command name : " << commandName << RESET << std::endl;
	params = extractParams(command);
	std::cout << YELLOW << "Params : " << params << RESET << std::endl;
	std::cout << RED << "auth = " << client.getAuth() << RESET << std::endl;

	if (commandName == "PASS")
		pass(client, params);
	else if (client.getPassOK() == 0 && commandName != "CAP")
		pass(client, "");
	else if (commandName == "NICK")
		nick(client, params);
	else if (commandName == "USER")
		user(client, params);
	else if (commandName == "PING")
		pong(client, params);
	else if (commandName == "QUIT")
		quit(client);
	else if (commandName == "PRIVMSG")
		privmsg(client, params);
	else if (commandName == "JOIN")
		join(client, params);
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
	
	std::cout << CYAN << "Buffer received" << std::endl << this->bufferRead_[senderFd] << RESET;

	for (int i = 0; this->bufferRead_[senderFd][i]; i++)
	{
		if (this->bufferRead_[senderFd][i] == '\r' || this->bufferRead_[senderFd][i] == '\n')
			std::cout << RED << (int)this->bufferRead_[senderFd][i] << RESET << " ";
		else
			std::cout << (int)this->bufferRead_[senderFd][i] << " ";
	}
	std::cout << std::endl;
	
	std::cout << "bytes read = " << bytesRead << std::endl;
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

		std::cout << "length reply = " << this->replies_[i].message.length() << std::endl;
		
		std::memset(buffer, 0, sizeof(buffer));
		std::strcpy(buffer, this->replies_[i].message.c_str());
		
		std::cout << CYAN << "Buffer to send" << std::endl << buffer << RESET;
		
		bufferStr = buffer;
		bytesSent = send(this->replies_[i].targetFd, buffer, bufferStr.length(), 0);
		
		for (int i = 0; buffer[i]; i++)
		{
			if (buffer[i] == '\r' || buffer[i] == '\n')
				std::cout << RED << (int)buffer[i] << RESET << " ";
			else
				std::cout << (int)buffer[i] << " ";
		}
		std::cout << std::endl;
		
		std::cout << "bytes sent = " << bytesSent << std::endl;
		

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
	// this->status_.clear();
}
