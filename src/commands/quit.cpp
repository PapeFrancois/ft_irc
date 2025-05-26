/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:46:57 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/26 14:13:54 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::quit(Client& client)
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
	
	this->replies_.push_back(setReply(QUIT_MSG(client.getNickname()), STATUS_QUIT, client.getSockFd()));
}
