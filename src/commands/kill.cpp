/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:07:48 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/26 15:03:10 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

static std::string extractTarget(std::string& params)
{
	int	spacePos;

	spacePos = params.find(" ");
	
	if (spacePos == -1)
		return params;
	else
		return params.substr(0, spacePos);
}

static std::string extractReason(std::string& params)
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

void Server::kill(Client& client, std::string& params)
{
	std::string	target;
	std::string	reason;

	target = extractTarget(params);

	// pas assez de params
	if (target == "")
	{
		this->replies_.push_back(setReply(ERR_NEEDMOREPARAMS(SERVER_NAME, client.getNickname(), "KILL"), STATUS_OK, client.getSockFd()));
		return;
	}

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
	
	reason = extractReason(params);
	if (reason == "")
		reason = "killed";
	
	quit(*getClientFromNick(target), reason);
}
