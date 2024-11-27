/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:39:45 by hepompid          #+#    #+#             */
/*   Updated: 2024/11/27 23:28:45 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() : port_(6667), password_("1234"), passOK_(0) {}

Server::Server(const int& port, const std::string& password) : port_(port), password_(password), passOK_(0) {}

Server::Server(const Server& other) : port_(other.port_), password_(other.password_)
{
	*this = other;
}

Server::~Server() {}

Server& Server::operator = (const Server& other)
{
	this->clients_ = other.clients_;
	this->pollFds_ = other.pollFds_;
	this->serverFd_ = other.serverFd_;

	return *this;
}

const std::string& Server::getPassword() const
{
	return this->password_;
}

const int& Server::getPort() const
{
	return this->port_;
}

const char* Server::RecvFailed::what() const throw()
{
	return ("Recv system call failed");
}

const char* Server::SocketFailed::what() const throw()
{
	return ("Socket system call failed");
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