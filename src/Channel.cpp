/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 09:58:38 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/30 16:05:12 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel() : name_("@yoo"), numberOfMembers_(0), limitOfMembers_(0), iMode_(0), tMode_(0) {}

Channel::Channel(const std::string& name, Client* creator) : 
	name_(name), numberOfMembers_(1), limitOfMembers_(0), iMode_(0), tMode_(0)
{
	this->operators_.push_back(creator);
	this->members_.push_back(creator);
}

Channel::Channel(const Channel& other) : name_(other.name_)
{
	*this = other;
}

Channel::~Channel() {}

Channel& Channel::operator = (const Channel& other)
{
	this->topic_ = other.topic_;
	this->key_ = other.key_;
	this->numberOfMembers_ = other.numberOfMembers_;
	this->limitOfMembers_ = other.limitOfMembers_;
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

const int& Channel::getNumberOfMembers() const
{
	return this->numberOfMembers_;
}

const int& Channel::getLimitOfMembers() const
{
	return this->limitOfMembers_;
}

const std::string& Channel::getKey() const
{
	return this->key_;
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

void Channel::setLimitOfMembers(const int& newLimitOfUsers)
{
	this->limitOfMembers_ = newLimitOfUsers;
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
	typedef	std::vector<Client*>::const_iterator it;
	
	if (this->members_.empty())
		std::cout << "no members in channel " << this->name_ << std::endl;
	for (it it = this->members_.begin(); it != this->members_.end(); it++)
		std::cout << (*it)->getNickname() << std::endl;
}

void Channel::printOperators() const
{
	typedef	std::vector<Client*>::const_iterator it;
	
	if (this->operators_.empty())
		std::cout << "no operators in channel " << this->name_ << std::endl;
	for (it it = this->operators_.begin(); it != this->operators_.end(); it++)
		std::cout << (*it)->getNickname() << std::endl;
}

void Channel::printInvitedUsers() const
{
	typedef	std::vector<Client*>::const_iterator it;
	
	if (this->invitedUsers_.empty())
		std::cout << "no invited users in channel " << this->name_ << std::endl;
	for (it it = this->invitedUsers_.begin(); it != this->invitedUsers_.end(); it++)
		std::cout << (*it)->getNickname() << std::endl;
}

void Channel::addMember(Client* user)
{
	this->members_.push_back(user);
	this->numberOfMembers_++;
}

void Channel::removeMember(Client* user)
{
	typedef	std::vector<Client*>::iterator ite;
	
	ite	it;
	
	it = this->members_.begin();
	while (it != this->members_.end())
	{
		if ((*it)->getNickname() == user->getNickname())
			this->members_.erase(it);
		else
			it++;
	}
	this->numberOfMembers_--;
	
	if (isOper(user))
		removeOperator(user);
}

void Channel::addOperator(Client* user)
{
	this->operators_.push_back(user);
}

void Channel::removeOperator(Client* user)
{
	typedef	std::vector<Client*>::iterator ite;
	
	ite	it;

	it = this->operators_.begin();
	while (it != this->operators_.end())
	{
		if ((*it)->getNickname() == user->getNickname())
			this->operators_.erase(it);
		else
			it++;
	}
}

void Channel::addInvitedUser(Client* user)
{
	this->invitedUsers_.push_back(user);
}

void Channel::removeInvitedUser(Client* user)
{
	typedef	std::vector<Client*>::iterator ite;

	ite	it;
	
	it = this->invitedUsers_.begin();
	while (it != this->invitedUsers_.end())
	{
		if ((*it)->getNickname() == user->getNickname())
			this->invitedUsers_.erase(it);
		else
			it++;
	}
}

void Channel::clearInvitedUsers()
{
	this->invitedUsers_.clear();
}

bool Channel::userIsInvited(Client* user) const
{
	typedef std::vector<Client*>::const_iterator	it;
	
	for (it it = this->invitedUsers_.begin(); it != this->invitedUsers_.end(); it++)
	{
		if (*it == user)
			return true;
	}
	return false;
}

std::vector<int> Channel::getMembersFd() const
{
	std::vector<int>	membersFd;
	typedef std::vector<Client*>::const_iterator it;

	for (it it = this->members_.begin(); it != this->members_.end(); it++)
		membersFd.push_back((*it)->getSockFd());
	return membersFd;
}

std::string Channel::getMembersNickList() const
{
	std::string	nickList;
	typedef std::vector<Client*>::const_iterator it;
	
	for (it it = this->members_.begin(); it != this->members_.end(); it++)
	{
		if (isOper(*it))
			nickList += "@";
		nickList += (*it)->getNickname();
		if (it + 1 != this->members_.end())
			nickList += " ";
	}
	return nickList;
}

bool Channel::isOper(Client* client) const
{
	typedef std::vector<Client*>::const_iterator it;

	for (it it = this->operators_.begin(); it != this->operators_.end(); it++)
		if (*it == client)
			return true;
	return false;
}

bool Channel::isMember(Client* client) const
{
	typedef std::vector<Client*>::const_iterator it;

	for (it it = this->members_.begin(); it != this->members_.end(); it++)
		if (*it == client)
			return true;
	return false;
}
