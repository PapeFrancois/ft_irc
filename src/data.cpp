/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:29:26 by hepompid          #+#    #+#             */
/*   Updated: 2024/11/20 00:42:36 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::formatData()
{
	bool	end;
	
	end = false;
	for (int i = 0; i < BUFFERSIZE; i++)
	{
		std::cout << (int)this->buffer_[i] << std::endl;
		if (end == true)
			this->buffer_[i] = 0;
		else if (this->buffer_[i] == '\n' && this->buffer_[i - 1] == '\r')
			end = true;
	}
	// std::cout << "end = " << end << std::endl;
	if (end == false)
	{
		this->buffer_[BUFFERSIZE - 2] = '\r';
		this->buffer_[BUFFERSIZE - 1] = '\n';
		this->buffer_[BUFFERSIZE] = 0;
	}
}

void Server::parseData()
{
	
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
	
	std::cout << YELLOW << "Message reveived : " << this->buffer_ << RESET;
	formatData();
	std::cout << "bytes read = " << bytesRead << std::endl;
	std::cout << YELLOW << "Message reveived : " << this->buffer_ << RESET;
}

const char* Server::RecvFailed::what() const throw()
{
	return ("Recv system call failed");
}
