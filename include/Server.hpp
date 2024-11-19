/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:08:53 by hepompid          #+#    #+#             */
/*   Updated: 2024/11/19 21:11:51 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <string>
# include <map>

# include <netdb.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <poll.h>
# include <unistd.h>

# include "Client.hpp"

# ifndef ANSI_CODES
#  define ANSI_CODES
#  define RESET "\033[0m"
#  define RED "\033[31m"
#  define GREEN "\033[32m"
#  define YELLOW "\033[33m"
#  define UNDERLINE "\033[4m"
# endif

# ifndef INFOSERV
#  define INFOSERV
#  define BACKLOG 10
#  define TIMEOUT 2000
#  define BUFFERSIZE 512
# endif

class Server
{
	private:
		std::map<int, Client>		clients_;
		std::vector<struct pollfd>	pollFds_;
		const int					port_;
		const std::string			password_;
		int							serverFd_;
		char						buffer_[BUFFERSIZE + 1];

		void	acceptNewConnection();
		void	addToPollFds(int socketFd);
		void	createServerSocket();
		void	endConnection(int socketFd);
		void	pollEvent();
		void	readData(int senderFd);
		void	removeFromPollFds(int socketFd);
		void	parseData();
		
	public:

		// ################
		// # constructors #
		// ################
		
		Server();
		Server(const int& port, const std::string& password);
		Server(const Server& other);
		~Server();


		// #############
		// # operators #
		// #############
		
		Server&	operator = (const Server& other);


		// ###########
		// # getters #
		// ###########

		const std::string&	getPassword() const;
		const int&			getPort() const;


		// ###########
		// # methods #
		// ###########

		void	launchServer();


		// ##############
		// # exceptions #
		// ##############

		class SocketFailed : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class BindFailed : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class ListenFailed : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class AcceptFailed : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class PollFailed : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class RecvFailed : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
};

#endif
