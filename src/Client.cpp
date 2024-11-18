/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:25:27 by hepompid          #+#    #+#             */
/*   Updated: 2024/11/18 16:57:57 by hepompid         ###   ########.fr       */
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

std::string& Client::getNick()
{
	return this->nick_;
}

std::string& Client::getUser()
{
	return this->user_;
}

const int& Client::getSockFd()
{
	return this->sockFd_;
}
