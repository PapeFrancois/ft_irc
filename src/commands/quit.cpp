/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:46:57 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/26 14:43:00 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::quit(Client& client, std::string& params)
{
	typedef	std::map<std::string, Channel>::iterator	iter;
	
	iter	it;
	iter	jt;
	
	it = this->channels_.begin();
	
	while (it != this->channels_.end())
	{
		if (it->second.isMember(&client))
		{
			jt = it++;
			part(client, (std::string&)jt->first);
		}
		else
			it++;
	}
	
	for (std::map<int, Client>::iterator it = this->fdCli_.begin(); it != this->fdCli_.end(); it++)
	{
		if (it->first != client.getSockFd())
			this->replies_.push_back(setReply(QUIT_MSG(client.getNickname(), client.getUsername(), SERVER_HOST, params), STATUS_OK, it->first));
	}
	
	this->replies_.push_back(setReply(QUIT_MSG(client.getNickname(), client.getUsername(), SERVER_HOST, params), STATUS_QUIT, client.getSockFd()));
}
