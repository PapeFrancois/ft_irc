/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:39:45 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/20 15:20:39 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// ######### CONSTR DESTR OPER #########

Server::Server() : port_(6667), password_("1234") {}

Server::Server(const int& port, const std::string& password) : port_(port), password_(password) {}

Server::Server(const Server& other) : port_(other.port_), password_(other.password_)
{
	*this = other;
}

Server::~Server() {}

Server& Server::operator = (const Server& other)
{
	this->fdCli_ = other.fdCli_;
	this->pollFds_ = other.pollFds_;
	this->serverFd_ = other.serverFd_;

	return *this;
}


// ######### GETTERS & PRINTERS #########

const std::string& Server::getPassword() const
{
	return this->password_;
}

const int& Server::getPort() const
{
	return this->port_;
}

void Server::printClients() const
{
	typedef	std::map<int, Client>::const_iterator it;
	
	if (this->fdCli_.empty())
		std::cout << "no client registered" << std::endl;
	for (it it = this->fdCli_.begin(); it != this->fdCli_.end(); it++)
		std::cout << it->second.getNickname() << std::endl;
}


// ######### METHODS #########

void Server::validateAuth(Client& client)
{
	client.setAuth(1);
	this->replies_.push_back(setReply(RPL_WELCOME(SERVER_NAME, client.getNickname()) + RPL_YOURHOST(SERVER_NAME, client.getNickname(), SERVER_VERSION) + RPL_CREATED(SERVER_NAME, client.getNickname(), CREATION_DAY) + RPL_MYINFO(SERVER_NAME, client.getNickname(), SERVER_VERSION), STATUS_OK, client.getSockFd()));
	this->replies_.push_back(setReply(RPL_MOTDSTART(SERVER_NAME, client.getNickname()) + RPL_MOTD1(SERVER_NAME, client.getNickname()), STATUS_OK, client.getSockFd()));
	this->replies_.push_back(setReply(RPL_MOTD2 + RPL_ENDOFMOTD(SERVER_NAME, client.getNickname()), STATUS_OK, client.getSockFd()));
	
}

Client* Server::getClientFromNick(const std::string& nickname)
{
	typedef std::map<int, Client>::iterator	it;
	
	for (it it = this->fdCli_.begin(); it != this->fdCli_.end(); it++)
	{
		if (it->second.getNickname() == nickname)
			return &(it->second);
	}
	return NULL;
}

replies Server::setReply(const std::string& message, const int& status, const int& targetFd)
{
	replies	reply;

	reply.message = message;
	reply.status = status;
	reply.targetFd = targetFd;

	return reply;
}


// ######### EXCEPTIONS #########

const char* Server::RecvFailed::what() const throw()
{
	return ("Recv system call failed");
}

const char* Server::SocketFailed::what() const throw()
{
	return ("Socket system call failed");
}

const char* Server::SocketOptionFailed::what() const throw()
{
	return ("Setsockopt system call failed");
}

const char* Server::BindFailed::what() const throw()
{
	return ("Bind system call failed");
}

const char* Server::ListenFailed::what() const throw()
{
	return ("Listen system call failed");
}

const char* Server::AcceptFailed::what() const throw()
{
	return ("Accept system call failed");
}

const char* Server::PollFailed::what() const throw()
{
	return ("Poll system call failed");
}

const char* Server::SendFailed::what() const throw()
{
	return ("Send system call failed");
}