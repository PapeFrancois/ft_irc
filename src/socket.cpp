/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:36:40 by hepompid          #+#    #+#             */
/*   Updated: 2024/11/18 20:43:09 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

static int createServerSocket(int port, int backlog)
{
	struct sockaddr_in	sa;
	int					serverFd;

	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	sa.sin_port = htons(port);

	serverFd = socket(sa.sin_family, SOCK_STREAM, 0);
	if (serverFd == -1)
		throw Server::SocketFailed();
	
	if (bind(serverFd, (sockaddr *)&sa, sizeof(sa)) == -1)
		throw Server::BindFailed();

	if (listen(serverFd, backlog) == -1)
		throw Server::ListenFailed();

	std::cout << GREEN << "Server is listening on fd " << serverFd << RESET << std::endl;
	
	return serverFd;
}

void addToPollFds(int serverFd, int socketFd, std::vector<struct pollfd>* pollFds)
{
	struct pollfd newPollFd;

	newPollFd.fd = socketFd;
	
	if (socketFd == serverFd)
		newPollFd.events = POLL_IN;
	else
		newPollFd.events = POLL_IN | POLL_OUT;

	(*pollFds).push_back(newPollFd);
}

void Server::launchServer()
{
	try
	{
		this->serverFd_ = createServerSocket(this->port_, BACKLOG);
	}
	catch (const std::exception& e)
	{
		std::cout << RED << "Error: " << e.what() << RESET << std::endl;
	}

	addToPollFds(this->serverFd_, this->serverFd_, &this->pollFds_);
}

class SocketFailed : public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return ("Socket system call failed");
		}
};

class BindFailed : public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return ("Bind system call failed");
		}
};

class ListenFailed : public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return ("Listen system call failed");
		}
};
