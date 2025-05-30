/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:46:08 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/30 16:06:01 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


void iModeManager(Channel& channel, char& sign)
{
	if (sign == '+')
		channel.setIMode(1);
	else
	{
		channel.clearInvitedUsers();
		channel.setIMode(0);
	}
}

void tModeManager(Channel& channel, char& sign)
{
	if (sign == '+')
		channel.setTMode(1);
	else
		channel.setTMode(0);
}

void kModeManager(Channel& channel, char& sign, std::string& key)
{
	if (sign == '+')
		channel.setKey(key);
	else
		channel.setKey("");
}

void lModeManager(Channel& channel, char& sign, std::string& limitOfMembersStr)
{
	int	limitOfMembersInt;

	std::istringstream	iss(limitOfMembersStr);

	iss >> limitOfMembersInt;

	if (iss.fail())
		return;
	
	if (sign == '+')
		channel.setLimitOfMembers(limitOfMembersInt);
	else
		channel.setLimitOfMembers(0);
}

void Server::mode(Client& client, std::vector<std::string>& args)
{
	std::string					channelName;
	std::string					mode;
	std::string					reply;
	std::string					replySuffix;
	std::vector<int>			membersFd;
	size_t						tokenUsed;
	std::string					key;
	std::string					limitOfUsers;
	std::string					chanOpTarget;
	char						sign;

	if (args.size() < 2)
	{
		this->replies_.push_back(setReply(ERR_NEEDMOREPARAMS(SERVER_NAME, client.getNickname(), "MODE"), STATUS_OK, client.getSockFd()));
		return;
	}

	channelName = args.at(1);
	if (args.size() >= 3)
		mode = args.at(2);
	else
		mode = "";

	std::cout << PURPLE_BG << "channel name = " << channelName << RESET << std::endl;
	std::cout << PURPLE_BG << "mode = " << mode << RESET << std::endl;	
	
	// soit si le channel n'existe pas, soit si c'est un mode user
	if (this->channels_.find(channelName) == this->channels_.end())
		return;


	// donne les modes du channel
	if (mode == "")
	{
		reply = "+";
		if (this->channels_[channelName].getIMode())
			reply += "i";
		if (this->channels_[channelName].getTMode())
			reply += "t";
		if (this->channels_[channelName].getKey() != "")
			reply += "k";
		if (this->channels_[channelName].getLimitOfMembers() != 0)
			reply += "l";
		if (this->channels_[channelName].getKey() != "")
		{			
			reply += " ";
			reply += this->channels_[channelName].getKey();
		}
		if (this->channels_[channelName].getLimitOfMembers() != 0)
		{
			reply += " ";
			reply += this->channels_[channelName].getLimitOfMembers();
		}
		this->replies_.push_back(setReply(RPL_CHANNELMODEIS(SERVER_NAME, client.getNickname(), channelName, reply), STATUS_OK, client.getSockFd()));
		return;
	}


	
	// dans le cas ou les modes sont modifies
	
	if (!this->channels_[channelName].isOper(&client))
	{
		this->replies_.push_back(setReply(ERR_CHANOPRIVSNEEDED(SERVER_NAME, client.getNickname(), channelName), STATUS_OK, client.getSockFd()));
		return;
	}

	if (mode[0] == '+')
	{
		sign = '+';
		reply = '+';
	}
	else if (mode[0] == '-')
	{
		sign = '-';
		reply = '-';
	}
		
	else
		return;
	

	tokenUsed = 0;
	
	if (mode.find('i') != std::string::npos)
	{
		iModeManager(this->channels_[channelName], mode[0]);
		reply += 'i';
	}
	if (mode.find('t') != std::string::npos)
	{
		tModeManager(this->channels_[channelName], mode[0]);
		reply += 't';
	}
	if (mode.find('k') != std::string::npos && args.size() >= tokenUsed + 2)
	{
		key = args.at(tokenUsed + 2);
		kModeManager(this->channels_[channelName], mode[0], key);
		reply += 'k';
		replySuffix += key;
		tokenUsed++;
	}
	if (mode.find('l') != std::string::npos && args.size() >= tokenUsed + 2)
	{
		limitOfUsers = args.at(tokenUsed + 2);
		lModeManager(this->channels_[channelName], mode[0], limitOfUsers);
		reply += 'l';
		replySuffix += limitOfUsers;
		tokenUsed++;
	}
	// if (mode.find('o') != std::string::npos && args.size() >= tokenUsed + 2)
	// {
	// 	chanOpTarget = args.at(tokenUsed + 2);
	// 	oModeManager;
	// 	tokenUsed++;
	// }

	if (replySuffix != "")
	{
		reply += " ";
		reply += replySuffix;
	}

	if (reply == "")
		return;
	
	membersFd = this->channels_[channelName].getMembersFd();
	
	for (std::vector<int>::iterator it = membersFd.begin(); it != membersFd.end(); it++)
	{
		this->replies_.push_back(setReply(MODE_MSG(client.getNickname(), client.getUsername(), SERVER_HOST, channelName, reply), STATUS_OK, *it));
		
	}	
}
