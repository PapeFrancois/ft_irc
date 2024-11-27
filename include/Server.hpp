/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:08:53 by hepompid          #+#    #+#             */
/*   Updated: 2024/11/27 23:28:33 by hepompid         ###   ########.fr       */
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
# include "reply.hpp"

# ifndef ANSI_CODES
#  define ANSI_CODES

#  define RESET "\033[0m"
#  define BOLD "\033[1m"
#  define UNDERLINE "\033[4m"

#  define BLACK "\033[30m"
#  define RED "\033[31m"
#  define GREEN "\033[32m"
#  define YELLOW "\033[33m"
#  define BLUE "\033[34m"
#  define PURPLE "\033[35m"
#  define CYAN "\033[36m"
#  define WHITE "\033[37m"

#  define BLACK_BG "\033[40m"
#  define RED_BG "\033[41m"
#  define GREEN_BG "\033[42m"
#  define YELLOW_BG "\033[43m"
#  define BLUE_BG "\033[44m"
#  define PURPLE_BG "\033[45m"
#  define CYAN_BG "\033[46m"
#  define WHITE_BG "\033[47m"
# endif

# ifndef INFOSERV
#  define INFOSERV
#  define BACKLOG 10
#  define TIMEOUT 2000
#  define BUFFERSIZE 512
#  define SERVER_NAME ":britney-spears "
# endif

class Server
{
	private:
		const int					port_;
		const std::string			password_;
		int							passOK_;
		
		std::vector<struct pollfd>	pollFds_;
		int							serverFd_;
		char						bufferRead_[BUFFERSIZE + 1];
		std::vector<std::string>	commands_;
		char						bufferWrite_[BUFFERSIZE + 1];
		std::vector<std::string>	replies_;
		
		std::map<int, Client>		clients_;


		void		acceptNewConnection();
		void		addToPollFds(int& socketFd);
		void		createServerSocket();
		void		endConnection(int& socketFd);
		void		pollEvent();
		void		removeFromPollFds(int& socketFd);
		
		std::string	extractCommandName(std::string& command);
		std::string	extractParams(std::string& command);
		void		manageCommand(std::string& command);
		void		parseData();
		void		processData(int& senderFd);
		void		readData(int& senderFd);
		void		sendData(int& senderFd);

		void		cap();
		void		pass(std::string params);
		void		error();
				
		
	public:
		Server();
		Server(const int& port, const std::string& password);
		Server(const Server& other);
		~Server();
		
		Server&	operator = (const Server& other);

		const std::string&	getPassword() const;
		const int&			getPort() const;

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
