/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:30:53 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/30 12:26:03 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::invite(Client& client, std::vector<std::string>& args)
{
	std::string channelName;
	std::string	target;

	// pas assez de params, on attend le name d'un channel et une target
	if (args.size() < 3)
	{
		this->replies_.push_back(setReply(ERR_NEEDMOREPARAMS(SERVER_NAME, client.getNickname(), "JOIN"), STATUS_OK, client.getSockFd()));
		return;
	}
	
	channelName = args.at(1);
	target = args.at(2);

	// la target n'existe pas
	if (this->getClientFromNick(target) == NULL)
	{
		this->replies_.push_back(setReply(ERR_NOSUCHNICK(SERVER_NAME, client.getNickname(), target), STATUS_OK, client.getSockFd()));
		return;
	}

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

	// le client n'est pas channel operator
	if (!this->channels_[channelName].isOper(&client))
	{
		this->replies_.push_back(setReply(ERR_CHANOPRIVSNEEDED(SERVER_NAME, client.getNickname(), channelName), STATUS_OK, client.getSockFd()));
		return;
	}

	// la target fait deja partie du channel
	if (this->channels_[channelName].isMember(getClientFromNick(target)))
	{
		this->replies_.push_back(setReply(ERR_USERONCHANNEL(SERVER_NAME, client.getNickname(), target, channelName), STATUS_OK, client.getSockFd()));
		return;
	}

	// ajout de la target a la liste des invited users
	this->channels_[channelName].addInvitedUser(getClientFromNick(target));
	
	// confirmation d'envoi d'invitation, send au client qui invite
	this->replies_.push_back(setReply(RPL_INVITING(SERVER_NAME, client.getNickname(), target, channelName), STATUS_OK, client.getSockFd()));
	
	// message d'invitation, send au client invited
	this->replies_.push_back(setReply(INVITE_MSG(client.getNickname(), client.getUsername(), SERVER_HOST, target, channelName), STATUS_OK, getClientFromNick(target)->getSockFd()));
}
