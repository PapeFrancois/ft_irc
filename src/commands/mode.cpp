/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:46:08 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/30 17:03:58 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

size_t tokenPos(std::string& mode, char option)
{
	int	tokenPos;

	// debut des token en pos 3 (command name, channel name, mode options)
	tokenPos = 3;

	for (int i = 0; mode[i]; i++)
	{
		if (mode[i] == option)
			return tokenPos;
		if (mode[i] == 'k' || mode[i] == 'l' || mode[i] == 'o')
			tokenPos++;
	}
	return tokenPos;
}

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

bool lModeManager(Channel& channel, char& sign, std::string& limitOfMembersStr)
{
	int	limitOfMembersInt;

	if (sign == '-')
	{
		channel.setLimitOfMembers(0);
		return 1;
	}
	
	std::stringstream	ss(limitOfMembersStr);

	ss >> limitOfMembersInt;

	if (ss.fail())
		return 0;
	
	channel.setLimitOfMembers(limitOfMembersInt);
	return 1;
}

void Server::mode(Client& client, std::vector<std::string>& args)
{
	std::string					channelName;
	std::string					mode;
	std::string					reply;
	std::string					replySuffix;
	std::vector<int>			membersFd;
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

			std::stringstream ss;

			ss << this->channels_[channelName].getLimitOfMembers();
			reply += ss.str();
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
	if (mode.find('k') != std::string::npos)
	{
		if (args.size() > tokenPos(mode, 'k') && sign == '+')
			key = args.at(tokenPos(mode, 'k'));
		kModeManager(this->channels_[channelName], mode[0], key);
		reply += 'k';
		if (sign == '+')
		{
			replySuffix += ' ';
			replySuffix += key;
		}
	}
	if (mode.find('l') != std::string::npos)
	{
		if (args.size() > tokenPos(mode, 'l') && sign == '+')
			limitOfUsers = args.at(tokenPos(mode, 'l'));
			
		
		bool status = lModeManager(this->channels_[channelName], mode[0], limitOfUsers);
		if (status)
			reply += 'l';
		if (sign == '+' && status)
		{
			replySuffix += ' ';
			replySuffix += limitOfUsers;
		}
	}
	// if (mode.find('o') != std::string::npos && args.size() >= tokenUsed + 3)
	// {
	// 	chanOpTarget = args.at(tokenUsed + 3);
	// 	oModeManager;
	// 	tokenUsed++;
	// }

	if (replySuffix != "")
		reply += replySuffix;

	if (reply == "")
		return;
	
	membersFd = this->channels_[channelName].getMembersFd();
	
	for (std::vector<int>::iterator it = membersFd.begin(); it != membersFd.end(); it++)
	{
		this->replies_.push_back(setReply(MODE_MSG(client.getNickname(), client.getUsername(), SERVER_HOST, channelName, reply), STATUS_OK, *it));
		
	}	
}
