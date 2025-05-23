/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:46:08 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/23 14:12:25 by hepompid         ###   ########.fr       */
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

std::string extractMode(std::string& params)
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

void Server::mode(Client& client, std::string& params)
{
	std::string	channelName;
	std::string	mode;
	std::string	modeList;

	if (params == "")
	{
		this->replies_.push_back(setReply(ERR_NEEDMOREPARAMS(SERVER_NAME, client.getNickname(), "MODE"), STATUS_OK, client.getSockFd()));
		return;
	}

	channelName = extractChannelName(params);
	mode = extractMode(params);

	// soit si le channel n'existe pas, soit si c'est un mode user
	if (this->channels_.find(channelName) == this->channels_.end())
		return;

	// donne les modes du channel
	if (mode == "")
	{
		modeList = "+";
		if (this->channels_[channelName].getIMode())
			modeList += "i";
		if (this->channels_[channelName].getTMode())
			modeList += "t";
		if (this->channels_[channelName].getKey() != "")
			modeList += "k";
		if (this->channels_[channelName].getLimitOfMembers() != 0)
			modeList += "l";
		modeList += " ";
		if (this->channels_[channelName].getKey() != "")
			modeList += this->channels_[channelName].getKey();
		if (this->channels_[channelName].getLimitOfMembers() != 0)
		{
			modeList += " ";
			modeList += this->channels_[channelName].getLimitOfMembers();
		}
		this->replies_.push_back(setReply(RPL_CHANNELMODEIS(SERVER_NAME, client.getNickname(), channelName, modeList), STATUS_OK, client.getSockFd()));
		return;
	}
	
	
}
