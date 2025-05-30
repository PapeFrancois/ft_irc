/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:15:10 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/30 14:51:56 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::part(Client& client, std::vector<std::string>& args)
{
	typedef std::vector<int>::iterator	it;

	std::vector<int>	membersFd;
	std::string			channelName;
	std::string			reason;

	
	// pas de channel name donne
	if (args.size() < 2)
	{
		this->replies_.push_back(setReply(ERR_NEEDMOREPARAMS(SERVER_NAME, client.getNickname(), "PART"), STATUS_OK, client.getSockFd()));
		return;
	}

	channelName = args.at(1);
	if (args.size() >= 3)
		reason = args.at(2);
	else
		reason = ":bye britney";

	// le channel n'existe pas
	if (this->channels_.find(channelName) == channels_.end())
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

	membersFd = this->channels_[channelName].getMembersFd();
	for (it it = membersFd.begin(); it != membersFd.end(); it++)
		this->replies_.push_back(setReply(PART_MSG(client.getNickname(), client.getUsername(), SERVER_HOST, channelName, reason), STATUS_OK, *it));

	// si le client est le dernier membre du channel
	if (this->channels_[channelName].getNumberOfMembers() == 1)
		deleteChannel(channelName);

	
	// s'il y a d'autres membres dans le channel
	else
		this->channels_[channelName].removeMember(&client);
}
