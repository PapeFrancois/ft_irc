/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:36:40 by hepompid          #+#    #+#             */
/*   Updated: 2024/11/19 12:54:11 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::addToPollFds(int socketFd)
{
	struct pollfd	newPollFd;

	newPollFd.fd = socketFd;
	
	if (socketFd == this->serverFd_)
		newPollFd.events = POLL_IN;
	else
		newPollFd.events = POLL_IN | POLL_OUT;

	this->pollFds_.push_back(newPollFd);
}

void Server::removeFromPollFds(int socketFd)
{
	typedef std::vector<struct pollfd>::iterator iterator;
	
	for (iterator it = this->pollFds_.begin(); it != this->pollFds_.end(); it++)
	{
		if ((*it).fd == socketFd)
		{
			this->pollFds_.erase(it);
		}
	}
}

void Server::acceptNewConnection()
{
	int	clientFd;

	clientFd = accept(this->serverFd_, NULL, NULL);
	if (clientFd == -1)
		throw AcceptFailed();
		
	addToPollFds(clientFd);
	
	std::cout << GREEN "New connection on fd " << clientFd << RESET << std::endl;
}

void Server::createServerSocket()
{
	struct sockaddr_in	sa;

	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	sa.sin_port = htons(this->port_);

	this->serverFd_ = socket(sa.sin_family, SOCK_STREAM, 0);
	if (this->serverFd_ == -1)
		throw SocketFailed();
	
	if (bind(this->serverFd_, (sockaddr *)&sa, sizeof(sa)) == -1)
		throw BindFailed();

	if (listen(this->serverFd_, BACKLOG) == -1)
		throw ListenFailed();

	addToPollFds(this->serverFd_);

	std::cout << GREEN << "Server is listening on fd " << this->serverFd_ << RESET << std::endl;
}

void Server::launchServer()
{
	try
	{
		createServerSocket();
	}
	catch (const std::exception& e)
	{
		std::cout << RED << "Error: " << e.what() << RESET << std::endl;
	}
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
