/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:29:26 by hepompid          #+#    #+#             */
/*   Updated: 2024/11/23 00:13:59 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::manageCommand(char command[])
{
	std::cout << YELLOW << "Command parsed : " << command << RESET;
}

void Server::parseData()
{
	char	tempBuffer[BUFFERSIZE + 1];
	int		j;
	
	std::memset(tempBuffer, 0, sizeof(tempBuffer));
	j = 0;
	for (int i = 0; this->buffer_[i]; i++)
	{
		// std::cout << (int)this->buffer_[i] << std::endl;
		tempBuffer[j] = this->buffer_[i];
		if (this->buffer_[i] == '\n' && this->buffer_[i - 1] == '\r')
		{
			manageCommand(tempBuffer);
			std::memset(tempBuffer, 0, sizeof(tempBuffer));
			j = -1;
		}
		j++;
	}
	if (j >= 2 && (tempBuffer[j - 1] != '\n' || tempBuffer[j - 2] != '\r'))
	{
		tempBuffer[j - 1] = '\n';
		tempBuffer[j - 2] = '\r';
		manageCommand(tempBuffer);
	}
}

void Server::readData(int senderFd)
{
	int		bytesRead;

	std::memset(this->buffer_, 0, sizeof(this->buffer_));
	bytesRead = recv(senderFd, this->buffer_, BUFFERSIZE, 0);
	if (bytesRead <= 0)
	{
		endConnection(senderFd);
		if (bytesRead == -1)
			throw RecvFailed();
		else if (bytesRead == 0)
			std::cout << GREEN << "Client " << senderFd << " disconnected from server" << RESET << std::endl;
		return ;
	}
	
	// std::cout << YELLOW << "Buffer received with recv : " << this->buffer_ << RESET;
	parseData();
	// std::cout << "bytes read = " << bytesRead << std::endl;
}

const char* Server::RecvFailed::what() const throw()
{
	return ("Recv system call failed");
}
