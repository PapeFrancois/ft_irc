/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:25:27 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/07 10:42:52 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client() : nickname_("*"), sockFd_(-1), passOK_(0), auth_(0)
{
	// std::cout << GREEN_BG << "Client created at " << this << RESET << std::endl;
}

Client::Client(const int& sockFd) : nickname_("*"), sockFd_(sockFd), passOK_(0), auth_(0)
{
	// std::cout << GREEN_BG << "Client created at " << this << RESET << std::endl;
}

Client::Client(const Client& other) : sockFd_(-1), passOK_(0)
{
	// std::cout << GREEN_BG << "Client created by copy at " << this << RESET << std::endl;
	*this = other;
}

Client::~Client()
{
	// std::cout << RED_BG << "Client destroyed at " << this << RESET << std::endl;
}

Client& Client::operator = (const Client& other)
{
	this->nickname_ = other.nickname_;
	this->username_ = other.username_;
	this->auth_ = other.auth_;
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

void Client::setNickname(const std::string& newNickname)
{
	this->nickname_ = newNickname;
}

void Client::setUsername(const std::string& newUsername)
{
	this->username_ = newUsername;
}

void Client::setAuth(const int& status)
{
	this->auth_ = status;
}