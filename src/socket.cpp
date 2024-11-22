/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:36:40 by hepompid          #+#    #+#             */
/*   Updated: 2024/11/23 00:15:08 by hepompid         ###   ########.fr       */
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
			return ;
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

void Server::endConnection(int socketFd)
{
	close(socketFd);
	
	removeFromPollFds(socketFd);
}

void Server::pollEvent()
{
	size_t	size = this->pollFds_.size();
	
	for (size_t i = 0; i < size; i++)
	{
		if ((this->pollFds_[i].revents & POLL_IN) != 1)
			continue;
		
		std::cout << BLUE_BG << "[" << this->pollFds_[i].fd << "] ready for lecture" << RESET << std::endl;
		
		try
		{
			if (this->pollFds_[i].fd == this->serverFd_)
				acceptNewConnection();
			else
				readData(this->pollFds_[i].fd);
		}
		catch (const std::exception& e)
		{
			throw;
		}
	}
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
	int	status;
	
	try
	{
		createServerSocket();
	}
	catch (const std::exception& e)
	{
		throw;
	}

	while (1)
	{
		status = poll(&(this->pollFds_[0]), this->pollFds_.size(), TIMEOUT);
		if (status == -1)
			throw PollFailed();
		else if (status == 0)
			std::cout << "Waiting..." << std::endl;
		else
		{
			try
			{
				pollEvent();
			}
			catch(const std::exception& e)
			{
				throw;
			}
			
		}
	}
}
