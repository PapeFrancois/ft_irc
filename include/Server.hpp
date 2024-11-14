
#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <map>
# include <vector>

# include <netdb.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <poll.h>
# include <unistd.h>

# include "Client.hpp"

class Server
{
	private:
		std::map<std::string, Client>	clientsList_;
		std::vector<struct pollfd>		pollFds_;
		
		int	server_fd;

	public:
		Server();
		Server(const Server& other);
		~Server();

		Server&	operator = (const Server& other);

		int		launchServer();
		void	addToPollFds(int socketFd);
		void	removeFromPollFds(int socketFd);
		int		createServerSocket();
		void	acceptNewConnection();
		void	readDataFromSocket();
};

#endif