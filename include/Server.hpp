/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:08:53 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/30 14:01:13 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <string>
# include <sstream>
# include <fstream>
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
# include "Channel.hpp"

# include "reply.hpp"
# include "ansiCodes.hpp"

# ifndef INFOSERV
#  define INFOSERV
#  define BACKLOG 10
#  define TIMEOUT 2000
#  define BUFFERSIZE 512
#  define SERVER_NAME "britney-spears"
#  define SERVER_VERSION "1.0"
#  define CREATION_DAY "25/12/JESUSBD"
#  define SERVER_HOST "127.0.0.1"
# endif

# ifndef SERVER_STATUS
#  define SERVER_STATUS
#  define STATUS_OK 0
#  define STATUS_AUTHFAILED 1
#  define STATUS_QUIT 2
# endif

typedef struct replies {
	std::string	message;
	int			status;
	int			targetFd;	
}	replies;

typedef struct serverOperators {
	std::string	name;
	std::string	password;
	std::string	host;
}	serverOperators;

class Server
{
	private:
		const int							port_;
		const std::string					password_;
		
		std::vector<struct pollfd>			pollFds_;
		int									serverFd_;
		

		std::map<int, std::string>			bufferRead_;
		std::vector<std::string>			commands_;
		std::vector<replies>				replies_;
		
		std::map<int, Client>				fdCli_;
		std::map<std::string, Channel>		channels_;
		std::vector<serverOperators>		serverOperators_;


		void			acceptNewConnection();
		void			addToPollFds(int& socketFd);
		void			createServerSocket();
		void			endConnection(int& socketFd);
		void			pollEvent();
		void			removeFromPollFds(int& socketFd);
		
		std::string		extractCommandName(std::string& command);
		std::string		extractParams(std::string& command);
		void			manageCommand(Client& client, std::string& command);
		void			parseData(int& senderFd);
		void			processData(int& senderFd);
		void			readData(int& senderFd);
		void			sendData();
		replies			setReply(const std::string& message, const int& status, const int& targetFd);
		
		serverOperators	setServerOperator(const std::string& name, const std::string& password, const std::string& host);
		bool			hostMatchesUsername(const std::string& username, const std::string& host);
		bool			passwordMatchesUsername(const std::string& username, const std::string& password);

		void			pass(Client& client, std::vector<std::string>& args);
		void			nick(Client& client, std::vector<std::string>& args);
		void			user(Client& client, std::vector<std::string>& args);
		void			pong(Client& client, std::vector<std::string>& args);
		void			quit(Client& client, std::vector<std::string>& args);
		void			join(Client& client, std::vector<std::string>& args);
		void			part(Client& client, std::vector<std::string>& args);
		void			mode(Client& client, std::vector<std::string>& args);
		void			kick(Client& client, std::vector<std::string>& args);
		void			invite(Client& client, std::vector<std::string>& args);
		void			topic(Client& client, std::vector<std::string>& args);
		void			privmsg(Client& client, std::vector<std::string>& args);
		void			oper(Client& client, std::vector<std::string>& args);
		void			kill(Client& client, std::vector<std::string>& args);
		
		void			validateAuth(Client& client);
		Client*			getClientFromNick(const std::string& nickname);
		
		void			createChannel(const std::string& name, Client* creator);
		void			deleteChannel(const std::string& name);
				
		
	public:
		Server();
		Server(const int& port, const std::string& password);
		Server(const Server& other);
		~Server();
		
		Server&	operator = (const Server& other);

		const std::string&	getPassword() const;
		const int&			getPort() const;
		
		void				printClients() const;

		void				initOperList();
		void				launchServer();

		
		class OpenFailed : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		
		class SocketFailed : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class SocketOptionFailed : public std::exception
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
