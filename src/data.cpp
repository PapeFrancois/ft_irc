/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:29:26 by hepompid          #+#    #+#             */
/*   Updated: 2024/11/19 18:30:47 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::readData(int senderFd)
{
	char	buffer[BUFFERSIZE];
	int		bytesRead;

	bytesRead = recv(senderFd, buffer, BUFFERSIZE, 0);
	if (bytesRead <= 0)
	{
		endConnection(senderFd);
		if (bytesRead == -1)
			throw RecvFailed();
		else if (bytesRead == 0)
			std::cout << GREEN << "Client " << senderFd << " disconnected from server" << RESET << std::endl;
	}
	
}

const char* Server::RecvFailed::what() const throw()
{
	return ("Recv system call failed");
}
