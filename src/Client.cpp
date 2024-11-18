/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:25:27 by hepompid          #+#    #+#             */
/*   Updated: 2024/11/18 18:00:41 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client() : nick_("noNick"), user_("noUser"), sockFd_(-1) {}

Client::Client(const Client& other) : sockFd_(-1)
{
	*this = other;
}

Client::~Client() {}

Client& Client::operator = (const Client& other)
{
	this->nick_ = other.nick_;
	this->user_ = other.user_;
	
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
