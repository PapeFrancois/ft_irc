/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:14:13 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/22 18:55:29 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::string extractChannelName(std::string& params)
{
	int	spacePos;

	spacePos = params.find(" ");
	
	if (spacePos == -1)
		return params;
	else
		return params.substr(0, spacePos);
}

std::string extractKey(std::string& params)
{
	int	spacePos;

	spacePos = params.find(" ");
	
	if (spacePos == -1)
		return "";
		
	for (int i = spacePos; params[i]; i++)
	{
		if (params[i] != ' ')
			return params.substr(i, params.length() - i);
	}
	return "";
}

bool validName(const std::string& name)
{
	if (name[0] != '#')
		return false;
	if (name.length() == 1)
		return false;
	
	for (size_t i = 1; i < name.length(); i++)
	{
		if (name[i] < '0')
			return false;
		else if (name[i] > '9' && name[i] < 'A')
			return false;
		else if (name[i] > 'Z' && name[i] < 'a')
			return false;
		else if (name[i] > 'z')
			return false;
	}	
	return true;
}

void Server::join(Client& client, std::string& params)
{
	std::string			channelName;
	std::string			key;
	std::vector<int>	membersFd;

	channelName = extractChannelName(params);
	key = extractKey(params);

	std::cout << PURPLE << "Channel name : " << channelName << std::endl << "Key : " << key << RESET << std::endl;

	// nom de channel invalide
	if (!validName(channelName))
	{
		this->replies_.push_back(setReply(ERR_BADCHANMASK(SERVER_NAME, channelName), STATUS_OK, client.getSockFd()));
		return ;
	}
	
		// le channel n'existe pas
	if (this->channels_.find(channelName) == this->channels_.end())
	{
		createChannel(channelName, &client);
		this->replies_.push_back(setReply(JOIN_MSG(client.getNickname(), channelName), STATUS_OK, client.getSockFd()));
		this->replies_.push_back(setReply(RPL_NAMREPLY(SERVER_NAME, client.getNickname(), channelName, this->channels_[channelName].getMembersNickList()), STATUS_OK, client.getSockFd()));
		this->replies_.push_back(setReply(RPL_ENDOFNAMES(SERVER_NAME, client.getNickname(), channelName), STATUS_OK, client.getSockFd()));
	}
	
	// le channel existe
	else
	{
		// si mauvais password
		if (this->channels_[channelName].getKey() != key)
		{
			this->replies_.push_back(setReply(ERR_BADCHANNELKEY(SERVER_NAME, client.getNickname(), channelName), STATUS_OK, client.getSockFd()));
			return ;	
		}

		// si la limite de membres est atteinte
		if (this->channels_[channelName].getLimitOfMembers() == this->channels_[channelName].getNumberOfMembers())
		{
			this->replies_.push_back(setReply(ERR_CHANNELISFULL(SERVER_NAME, client.getNickname(), channelName), STATUS_OK, client.getSockFd()));
			return ;
		}

		// si l'user n'est pas invite
		if (this->channels_[channelName].getIMode() && !this->channels_[channelName].userIsInvited(&client))
		{
			this->replies_.push_back(setReply(ERR_INVITEONLYCHAN(SERVER_NAME, client.getNickname(), channelName), STATUS_OK, client.getSockFd()));
			return ;
		}

		// l'user rejoint le channel
		this->channels_[channelName].addMember(&client);
	
		membersFd = this->channels_[channelName].getMembersFd();
		for (int i = 0; membersFd[i]; i++)
		this->replies_.push_back(setReply(JOIN_MSG(client.getNickname(), channelName), STATUS_OK, membersFd[i]));
		this->replies_.push_back(setReply(RPL_NAMREPLY(SERVER_NAME, client.getNickname(), channelName, this->channels_[channelName].getMembersNickList()), STATUS_OK, client.getSockFd()));
		this->replies_.push_back(setReply(RPL_ENDOFNAMES(SERVER_NAME, client.getNickname(), channelName), STATUS_OK, client.getSockFd()));

	}
}
