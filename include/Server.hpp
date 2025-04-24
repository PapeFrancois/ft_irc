/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:08:53 by hepompid          #+#    #+#             */
/*   Updated: 2025/04/24 11:34:02 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <string>
# include <map>
# include <vector>
# include <cstring>
# include <cstdlib>

# include <netdb.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <poll.h>
# include <unistd.h>

# include "Client.hpp"
# include "reply.hpp"
# include "ansiCodes.hpp"

# ifndef INFOSERV
#  define INFOSERV
#  define BACKLOG 10
#  define TIMEOUT 2000
#  define BUFFERSIZE 512
#  define SERVER_NAME "britney-spears"
#  define SERVER_VERSION "1.0"
#  define CREATION_DAY "a hundred years ago"
# endif

# ifndef SERVER_STATUS
#  define SERVER_STATUS
#  define STATUS_OK 0
#  define STATUS_AUTHFAILED 1
#  define STATUS_QUIT 2
# endif

class Server
{
	private:
		const int					port_;
		const std::string			password_;
		
		std::vector<struct pollfd>	pollFds_;
		int							serverFd_;
		char						bufferRead_[BUFFERSIZE + 1];
		std::vector<std::string>	commands_;
		char						bufferWrite_[BUFFERSIZE + 1];
		std::vector<std::string>	replies_;
		std::vector<int>			status_;
		
		std::map<int, Client>		clients_;


		void		acceptNewConnection();
		void		addToPollFds(int& socketFd);
		void		createServerSocket();
		void		endConnection(int& socketFd);
		void		pollEvent();
		void		removeFromPollFds(int& socketFd);
		
		std::string	extractCommandName(std::string& command);
		std::string	extractParams(std::string& command);
		void		manageCommand(Client& client, std::string& command);
		void		parseData();
		void		processData(int& senderFd);
		void		readData(int& senderFd);
		void		sendData(int& senderFd);

		void		cap(std::string& params);
		void		pass(Client& client, std::string params);
		void		nick(Client& client, std::string& nickname);
		void		user(Client& client, std::string& params);
		void		pong(Client& client, std::string& params);
		void		quit();
				
		
	public:
		Server();
		Server(const int& port, const std::string& password);
		Server(const Server& other);
		~Server();
		
		Server&	operator = (const Server& other);

		const std::string&	getPassword() const;
		const int&			getPort() const;
		const Client&		getClientFromFd(int& fd) const;

		void	launchServer();

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
		
		class SendFailed : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
};

#endif
