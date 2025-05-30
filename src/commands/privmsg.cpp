/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:01:29 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/30 12:31:39 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::privmsg(Client& client, std::vector<std::string>& args)
{
	typedef std::vector<int>::iterator	it;

    std::string 		target;
	int					targetFd;
    std::string 		message;
	std::vector<int>	membersFd;


	if (args.size() < 2)
	{
		this->replies_.push_back(setReply(ERR_NEEDMOREPARAMS(SERVER_NAME, client.getNickname(), "PRIVMSG"), STATUS_OK, client.getSockFd()));
		return;
	}
	
    target = args.at(1);
	if (args.size() >= 3)
    	message = args.at(2);
	else
		message = "";
	
	// target mais pas de message
	if (message.empty())
	{
		this->replies_.push_back(setReply(ERR_NOTEXTTOSEND(SERVER_NAME, client.getNickname()), STATUS_OK, client.getSockFd()));
		return;
	}

	// target est un user
	if (target[0] != '#')
	{
		// l'user n'existe pas
		if (!getClientFromNick(target))
		{
			this->replies_.push_back(setReply(ERR_NOSUCHNICK(SERVER_NAME, client.getNickname(), target), STATUS_OK, client.getSockFd()));
			return;
		}
		
		// envoi du message a l'user
		targetFd = getClientFromNick(target)->getSockFd();
		this->replies_.push_back(setReply(PRIVMSG(client.getNickname(), client.getUsername(), SERVER_HOST, target, message), STATUS_OK, targetFd));
		return;
	}

	// target est un channel
	
	// le channel n'existe pas
	if (this->channels_.find(target) == this->channels_.end())
	{
		this->replies_.push_back(setReply(ERR_NOSUCHCHANNEL(SERVER_NAME, client.getNickname(), target), STATUS_OK, client.getSockFd()));
		return;
	}
	
	// envoi du message aux membres du channel sauf a soi meme
	membersFd = this->channels_[target].getMembersFd();
	for (it it =  membersFd.begin(); it != membersFd.end(); it++)
	{
		if (*it != client.getSockFd())
			this->replies_.push_back(setReply(PRIVMSG(client.getNickname(), client.getUsername(), SERVER_HOST, target, message), STATUS_OK, *it));
	}
}

