/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:07:48 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/30 14:04:24 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::kill(Client& client, std::vector<std::string>& args)
{
	std::string					target;
	std::string					reason;
	std::vector<std::string>	quitArgs;
	
	// pas assez de params, on attend une target
	if (args.size() < 2)
	{
		this->replies_.push_back(setReply(ERR_NEEDMOREPARAMS(SERVER_NAME, client.getNickname(), "KILL"), STATUS_OK, client.getSockFd()));
		return;
	}
	
	target = args.at(1);

	if (!getClientFromNick(target))
	{
		this->replies_.push_back(setReply(ERR_NOSUCHNICK(SERVER_NAME, client.getNickname(), target), STATUS_OK, client.getSockFd()));
		return;
	}

	// le client n'est pas operator
	if (!client.getIsOper())
	{
		this->replies_.push_back(setReply(ERR_NOPRIVILEGES(SERVER_NAME, client.getNickname()), STATUS_OK, client.getSockFd()));
		return;
	}
	
	if (args.size() >= 3)
	reason = args.at(2);
	else
		reason = "killed";
	
	quitArgs.push_back("QUIT");
	quitArgs.push_back(reason);
	quit(*getClientFromNick(target), quitArgs);
}
