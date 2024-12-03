/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:25:27 by hepompid          #+#    #+#             */
/*   Updated: 2024/12/03 19:19:26 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client() : nickname_("*"), sockFd_(-1), passOK_(0), auth_(0) {}

Client::Client(const int& sockFd) : nickname_("*"), sockFd_(sockFd), passOK_(0), auth_(0) {}

Client::Client(const Client& other) : sockFd_(-1)
{
	*this = other;
}

Client::~Client() {}

Client& Client::operator = (const Client& other)
{
	this->nickname_ = other.nickname_;
	this->username_ = other.username_;
	return *this;
}

const std::string& Client::getNickname() const
{
	return this->nickname_;
}

const std::string& Client::getUsername() const
{
	return this->username_;
}

const int& Client::getSockFd() const
{
	return this->sockFd_;
}

const int& Client::getPassOK() const
{
	return this->passOK_;
}

const int& Client::getAuth() const
{
	return this->auth_;
}

void Client::setPassOK(const int& status)
{
	this->passOK_ = status;
}

void Client::setNickname(const std::string& nickname)
{
	this->nickname_ = nickname;
}

void Client::setUsername(const std::string& username)
{
	this->username_ = username;
}

void Client::setAuth(const int& status)
{
	this->auth_ = status;
}