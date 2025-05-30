/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:54:11 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/30 12:28:00 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::topic(Client& client, std::vector<std::string>& args)
{
	typedef std::vector<int>::iterator	it;

	std::string			channelName;
	std::string			newTopic;
	std::vector<int>	membersFd;
	
	if (args.size() < 2)
	{
		this->replies_.push_back(setReply(ERR_NEEDMOREPARAMS(SERVER_NAME, client.getNickname(), "TOPIC"), STATUS_OK, client.getSockFd()));
		return;
	}

	channelName = args.at(1);
	if (args.size() >= 3)
		newTopic = args.at(2);
	else
		newTopic = "";

	// le channel n'existe pas
	if (this->channels_.find(channelName) == this->channels_.end())
	{
		this->replies_.push_back(setReply(ERR_NOSUCHCHANNEL(SERVER_NAME, client.getNickname(), channelName), STATUS_OK, client.getSockFd()));
		return;
	}

	// le client ne fait pas partie du channel
	if (!this->channels_[channelName].isMember(&client))
	{
		this->replies_.push_back(setReply(ERR_NOTONCHANNEL(SERVER_NAME, client.getNickname(), channelName), STATUS_OK, client.getSockFd()));
		return;
	}

	// affiche le topic
	if (newTopic == "")
	{
		this->replies_.push_back(setReply(PRINT_TOPIC(client.getNickname(), client.getUsername(), SERVER_HOST, this->channels_[channelName].getTopic()), STATUS_OK, client.getSockFd()));
		return;
	}

	// si le client tente de modif le topic sans etre oper alors que le mode +t est actif
	if (this->channels_[channelName].getTMode() && !this->channels_[channelName].isOper(&client))
	{
		this->replies_.push_back(setReply(ERR_CHANOPRIVSNEEDED(SERVER_NAME, client.getNickname(), channelName), STATUS_OK, client.getSockFd()));
		return;
	}

	// change le topic du channel
	this->channels_[channelName].setTopic(newTopic);
	
	// affiche le nouveau topic aux membres du channel
	membersFd = this->channels_[channelName].getMembersFd();
	for (it it = membersFd.begin(); it != membersFd.end(); it++)
		this->replies_.push_back(setReply(TOPIC_MSG(client.getNickname(), client.getUsername(), SERVER_HOST, channelName, newTopic), STATUS_OK, *it));
}
