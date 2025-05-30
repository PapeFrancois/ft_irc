/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:14:13 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/30 12:18:53 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

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

void Server::join(Client& client, std::vector<std::string>& args)
{
	typedef std::vector<int>::iterator	it;
	
	std::string			channelName;
	std::string			key;
	std::vector<int>	membersFd;

	// pas de params donnes
	if (args.size() == 1)
	{
		this->replies_.push_back(setReply(ERR_NEEDMOREPARAMS(SERVER_NAME, client.getNickname(), "JOIN"), STATUS_OK, client.getSockFd()));
		return;
	}

	channelName = args.at(1);

	if (args.size() > 2)
		key = args.at(2);
	else
		key = "";

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
		this->replies_.push_back(setReply(JOIN_MSG(client.getNickname(), client.getUsername(), SERVER_HOST, channelName), STATUS_OK, client.getSockFd()));
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
		std::cout << RED_BG << "segfault 1" << RESET << std::endl;
		if (this->channels_[channelName].getIMode() && !this->channels_[channelName].userIsInvited(&client))
		{
			this->replies_.push_back(setReply(ERR_INVITEONLYCHAN(SERVER_NAME, client.getNickname(), channelName), STATUS_OK, client.getSockFd()));
			return ;
		}

		// si l'user est invite, le retirer de la liste d'invites
		if (this->channels_[channelName].getIMode() && this->channels_[channelName].userIsInvited(&client))
			this->channels_[channelName].removeInvitedUser(&client);

		// l'user rejoint le channel
		this->channels_[channelName].addMember(&client);
	
		// envoie JOIN_MSG a tous les membres du channel
		membersFd = this->channels_[channelName].getMembersFd();
		for (it it = membersFd.begin(); it != membersFd.end(); it++)
			this->replies_.push_back(setReply(JOIN_MSG(client.getNickname(), client.getUsername(), SERVER_HOST, channelName), STATUS_OK, *it));
		
		// envoie les messages relatifs a l'arrivee dans un channel a l'user qui vient de JOIN
		if (this->channels_[channelName].getTopic() != "")
			this->replies_.push_back(setReply(RPL_TOPIC(SERVER_NAME, client.getNickname(), channelName, this->channels_[channelName].getTopic()), STATUS_OK, client.getSockFd()));
		this->replies_.push_back(setReply(RPL_NAMREPLY(SERVER_NAME, client.getNickname(), channelName, this->channels_[channelName].getMembersNickList()), STATUS_OK, client.getSockFd()));
		this->replies_.push_back(setReply(RPL_ENDOFNAMES(SERVER_NAME, client.getNickname(), channelName), STATUS_OK, client.getSockFd()));
	}
}
