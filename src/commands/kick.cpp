/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:09:15 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/30 12:22:33 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::kick(Client& client, std::vector<std::string>& args)
{
	typedef std::vector<int>::iterator	it;

	std::vector<std::string>	kickParams;
	std::string					channelName;
	std::string					target;
	std::string					message;
	std::vector<int>			membersFd;

	// pas de parametres donnes
	if (args.size() == 1)
	{
		this->replies_.push_back(setReply(ERR_NEEDMOREPARAMS(SERVER_NAME, client.getNickname(), "KICK"), STATUS_OK, client.getSockFd()));
		return;
	}

	// pas assez de parametres donnes, il faut le nom d'un channel et une target
	if (args.size() <  3)
	{
		this->replies_.push_back(setReply(ERR_NEEDMOREPARAMS(SERVER_NAME, client.getNickname(), "KICK"), STATUS_OK, client.getSockFd()));
		return;
	}

	channelName = args.at(1);
	target = args.at(2);
	if (args.size() >= 4)
		message = args.at(3);
	else
		message = ":" + client.getNickname();

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
	
	// la target ne fait pas partie du channel
	if (!this->channels_[channelName].isMember(getClientFromNick(target)))
	{
		this->replies_.push_back(setReply(ERR_USERNOTINCHANNEL(SERVER_NAME, client.getNickname(), channelName, target), STATUS_OK, client.getSockFd()));
		return;
	}

	// le client n'a pas les perm operateur
	if (!this->channels_[channelName].isOper(&client))
	{
		this->replies_.push_back(setReply(ERR_CHANOPRIVSNEEDED(SERVER_NAME, client.getNickname(), channelName), STATUS_OK, client.getSockFd()));
		return;
	}

	// affiche KICK_MSG a tous les membres du channel
	membersFd = this->channels_[channelName].getMembersFd();
	for (it it = membersFd.begin(); it != membersFd.end(); it++)
		this->replies_.push_back(setReply(KICK_MSG(client.getNickname(), client.getUsername(), SERVER_HOST, channelName, target, message), STATUS_OK, *it));

	// remove les perm oper a l'user kick
	if (this->channels_[channelName].isOper(getClientFromNick(target)))
		this->channels_[channelName].removeOperator(getClientFromNick(target));
	
	// remove l'user du channel
	this->channels_[channelName].removeMember(getClientFromNick(target));
}
