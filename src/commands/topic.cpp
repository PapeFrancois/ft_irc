/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:54:11 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/25 15:46:22 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

static std::string extractChannelName(std::string& params)
{
	int	spacePos;

	spacePos = params.find(" ");
	
	if (spacePos == -1)
		return params;
	else
		return params.substr(0, spacePos);
}

static std::string extractNewTopic(std::string& params)
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

void Server::topic(Client& client, std::string& params)
{
	typedef std::vector<int>::iterator	it;

	std::string			channelName;
	std::string			newTopic;
	std::vector<int>	membersFd;
	
	if (params == "")
	{
		this->replies_.push_back(setReply(ERR_NEEDMOREPARAMS(SERVER_NAME, client.getNickname(), "TOPIC"), STATUS_OK, client.getSockFd()));
		return;
	}

	channelName = extractChannelName(params);
	newTopic = extractNewTopic(params);

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
