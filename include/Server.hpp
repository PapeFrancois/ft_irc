/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:08:53 by hepompid          #+#    #+#             */
/*   Updated: 2024/11/18 17:55:37 by hepompid         ###   ########.fr       */
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

# ifndef INFOSERV
#  define INFOSERV
#  define BACKLOG 10
#  define TIMEOUT 2000
#  define BUFFERSIZE 512
# endif

class Server
{
	private:
		std::map<int, Client>	clients_;
		struct pollfd			*pollFds_;
		const int				port_;
		const std::string		password_;
		
	public:
		Server();
		Server(const int& port, const std::string& password);
		Server(const Server& other);
		~Server();
		
		Server&	operator = (const Server& other);

		const std::string&	getPassword() const;
		const int&			getPort() const;

		void	launchServer();
};

#endif
