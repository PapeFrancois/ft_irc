/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:25:27 by hepompid          #+#    #+#             */
/*   Updated: 2024/11/28 00:11:14 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client() : sockFd_(-1), auth_(0) {}

Client::Client(const int& sockFd) : sockFd_(sockFd), auth_(0) {}

Client::Client(const Client& other) : user_("noUser"), sockFd_(-1)
{
	*this = other;
}

Client::~Client() {}

Client& Client::operator = (const Client& other)
{
	this->nick_ = other.nick_;
	return *this;
}

const std::string& Client::getNick() const
{
	return this->nick_;
}

const std::string& Client::getUser() const
{
	return this->user_;
}

const int& Client::getSockFd() const
{
	return this->sockFd_;
}

const int& Client::getAuth() const
{
	return this->auth_;
}

void Client::setAuth(const int& status)
{
	this->auth_ = status;
}
