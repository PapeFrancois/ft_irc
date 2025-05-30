/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:46:57 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/30 14:02:14 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::quit(Client& client, std::vector<std::string>& args)
{
	typedef	std::map<std::string, Channel>::iterator	iter;
	
	iter						it;
	iter						jt;
	std::string					reason;
	std::vector<std::string>	partArgs;
	
	if (args.size() >= 2)
		reason = args.at(1);
	else
		reason = ":thank you britney";

	it = this->channels_.begin();
	
	while (it != this->channels_.end())
	{
		if (it->second.isMember(&client))
		{
			jt = it++;
			partArgs.push_back("PART");
			partArgs.push_back(jt->first);
			partArgs.push_back(reason);
			part(client, partArgs);
		}
		else
			it++;
	}
	

	for (std::map<int, Client>::iterator it = this->fdCli_.begin(); it != this->fdCli_.end(); it++)
	{
		if (it->first != client.getSockFd())
			this->replies_.push_back(setReply(QUIT_MSG(client.getNickname(), client.getUsername(), SERVER_HOST, reason), STATUS_OK, it->first));
	}
	
	this->replies_.push_back(setReply(QUIT_MSG(client.getNickname(), client.getUsername(), SERVER_HOST, reason), STATUS_QUIT, client.getSockFd()));
}
