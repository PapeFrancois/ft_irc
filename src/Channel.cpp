/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 09:58:38 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/07 11:06:37 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel() : name_("@yoo"), limitOfUsers_(0), iMode_(0), tMode_(0) {}

Channel::Channel(const std::string& name) : name_(name), limitOfUsers_(0), iMode_(0), tMode_(0) {}

Channel::Channel(const Channel& other) : name_(other.name_)
{
	*this = other;
}

Channel::~Channel() {}

Channel& Channel::operator = (const Channel& other)
{
	this->topic_ = other.topic_;
	this->key_ = other.key_;
	this->limitOfUsers_ = other.limitOfUsers_;
	this->members_ = other.members_;
	this->operators_ = other.operators_;
	this->invitedUsers_ = other.invitedUsers_;
	this->iMode_ = other.iMode_;
	this->tMode_ = other.tMode_;
	return *this;
}

const std::string& Channel::getName() const
{
	return this->name_;
}

const std::string& Channel::getTopic() const
{
	return this->topic_;
}

const std::string& Channel::getKey() const
{
	return this->key_;
}

const int& Channel::getLimitOfUsers() const
{
	return this->limitOfUsers_;
}

const bool& Channel::getIMode() const
{
	return this->iMode_;
}

const bool& Channel::getTMode() const
{
	return this->tMode_;
}

void Channel::setTopic(const std::string& newTopic)
{
	this->topic_ = newTopic;
}

void Channel::setKey(const std::string& newKey)
{
	this->key_ = newKey;
}

void Channel::setLimitOfUsers(const int& newLimitOfUsers)
{
	this->limitOfUsers_ = newLimitOfUsers;
}

void Channel::setIMode(const bool& newIMode)
{
	this->iMode_ = newIMode;
}

void Channel::setTMode(const bool& newTMode)
{
	this->tMode_ = newTMode;
}

void Channel::printMembers() const
{
	typedef	std::vector<std::string>::const_iterator it;
	
	if (this->members_.empty())
		std::cout << "no members in channel " << this->name_ << std::endl;
	for (it it = this->members_.begin(); it != this->members_.end(); it++)
		std::cout << *it << std::endl;
}

void Channel::printOperators() const
{
	typedef	std::vector<std::string>::const_iterator it;
	
	if (this->operators_.empty())
		std::cout << "no operators in channel " << this->name_ << std::endl;
	for (it it = this->operators_.begin(); it != this->operators_.end(); it++)
		std::cout << *it << std::endl;
}

void Channel::printInvitedUsers() const
{
	typedef	std::vector<std::string>::const_iterator it;
	
	if (this->invitedUsers_.empty())
		std::cout << "no invited users in channel " << this->name_ << std::endl;
	for (it it = this->invitedUsers_.begin(); it != this->invitedUsers_.end(); it++)
		std::cout << *it << std::endl;
}

void Channel::addMember(const std::string& userNickname)
{
	this->members_.push_back(userNickname);
}

void Channel::removeMember(const std::string& userNickname)
{
	typedef	std::vector<std::string>::iterator it;
	
	for (it it = this->members_.begin(); it != this->members_.end(); it++)
	{
		if (*it == userNickname)
			this->members_.erase(it);
	}
}

void Channel::addOperator(const std::string& userNickname)
{
	this->operators_.push_back(userNickname);
}

void Channel::removeOperator(const std::string& userNickname)
{
	typedef	std::vector<std::string>::iterator it;
	
	for (it it = this->operators_.begin(); it != this->operators_.end(); it++)
	{
		if (*it == userNickname)
			this->operators_.erase(it);
	}
}

void Channel::addInvitedUser(const std::string& userNickname)
{
	this->invitedUsers_.push_back(userNickname);
}

void Channel::removeInvitedUser(const std::string& userNickname)
{
	typedef	std::vector<std::string>::iterator it;
	
	for (it it = this->invitedUsers_.begin(); it != this->invitedUsers_.end(); it++)
	{
		if (*it == userNickname)
			this->invitedUsers_.erase(it);
	}
}