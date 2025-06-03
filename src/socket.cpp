/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:36:40 by hepompid          #+#    #+#             */
/*   Updated: 2025/06/03 14:52:44 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool running = 1;

void Server::addToPollFds(const int& socketFd)
{
	struct pollfd	newPollFd;

	newPollFd.fd = socketFd;
	
	if (socketFd == this->serverFd_)
		newPollFd.events = POLLIN;
	else
	{
		newPollFd.events = POLLIN;
		// newPollFd.events = POLLIN | POLLOUT;
	}

	this->pollFds_.push_back(newPollFd);
}

void Server::removeFromPollFds(const int& socketFd)
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
	struct sockaddr_in	clientAddr;
	socklen_t			clientLen;
	int					clientFd;
	std::string			clientIp;

	clientLen = sizeof(clientAddr);
	clientFd = accept(this->serverFd_, (struct sockaddr *)&clientAddr, &clientLen);

	clientIp = inet_ntoa(clientAddr.sin_addr);

	if (clientFd == -1)
		throw AcceptFailed();
		
	addToPollFds(clientFd);
	
	Client	client(clientFd, clientIp);
	this->fdCli_[clientFd] = client;
	
	std::cout << GREEN "New connection on fd " << clientFd << RESET << std::endl;
}

void Server::endConnection(const int& socketFd)
{
	this->fdCli_.erase(socketFd);
	
	close(socketFd);
	removeFromPollFds(socketFd);
}

void Server::pollEvent()
{
	size_t	size = this->pollFds_.size();
	
	for (size_t i = 0; i < size; i++)
	{
		if ((this->pollFds_[i].revents & POLLIN) != POLLIN)
			continue;
		
		std::cout << BLUE_BG << "[" << this->pollFds_[i].fd << "] ready for lecture" << RESET << std::endl << std::endl;
		
		try
		{
			if (this->pollFds_[i].fd == this->serverFd_)
				acceptNewConnection();
			else
				processData(this->pollFds_[i].fd);
		}
		catch (const std::exception& e)
		{
			throw;
		}
	}

	for (size_t i = 0; i < size; i++)
	{
		if ((this->pollFds_[i].revents & POLLOUT) != POLLOUT)
			continue ;

		// std::cout << BLUE_BG << "[" << this->pollFds_[i].fd << "] expects a reply ASAP" << RESET << std::endl;
	}
}

void Server::createServerSocket()
{
	struct sockaddr_in	sa;
	int					opt;

	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	sa.sin_port = htons(this->port_);

	this->serverFd_ = socket(sa.sin_family, SOCK_STREAM, 0);
	if (this->serverFd_ == -1)
		throw SocketFailed();
	
	opt = 1;
	if (setsockopt(this->serverFd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		throw SocketOptionFailed();
		
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
		if (this->serverFd_ != -1)
			close(this->serverFd_);
		throw;
	}

	while (running)
	{
		status = poll(&(this->pollFds_[0]), this->pollFds_.size(), TIMEOUT);
		if (status == -1 && running)
			throw PollFailed();
		// else if (status == 0)
		// 	std::cout << "Waiting..." << std::endl;
		else if (running)
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

	std::cout << std::endl;
	std::cout << GREEN << "Server closed connection" << RESET << std::endl;
}

void stopServer(int signal)
{
	(void)signal;
	running = 0;
}
