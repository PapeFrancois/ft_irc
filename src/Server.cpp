/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:39:45 by hepompid          #+#    #+#             */
/*   Updated: 2024/11/18 16:58:00 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() : port_(6667), password_("1234") {}

Server::Server(const Server& other) : port_(other.port_), password_(other.password_)
{
	*this = other;
}

Server::~Server() {}

Server& Server::operator = (const Server& other)
{
	this->clients_ = other.clients_;
	this->pollFds_ = other.pollFds_;

	return *this;
}

const std::string& Server::getPassword()
{
	return this->password_;
}

const int& Server::getPort()
{
	return this->port_;
}
