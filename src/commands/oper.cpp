/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:13:00 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/26 15:09:31 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

static std::string extractName(std::string& params)
{
	int	spacePos;

	spacePos = params.find(" ");
	
	if (spacePos == -1)
		return params;
	else
		return params.substr(0, spacePos);
}

static std::string extractPassword(std::string& params)
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

void Server::oper(Client& client, std::string& params)
{
	std::string	name;
	std::string	password;
	
		// le client est deja operator
		if (client.getIsOper())
			return;

	name = extractName(params);
	password = extractPassword(params);

	// pas de params
	if (password == "" || name == "")
	{
		this->replies_.push_back(setReply(ERR_NEEDMOREPARAMS(SERVER_NAME, client.getNickname(), "OPER"), STATUS_OK, client.getSockFd()));
		return;
	}

	// pas d'entree associe a ce name, ou mauvais host
	if (!hostMatchesUsername(name, client.getIpAddress()))
	{
		this->replies_.push_back(setReply(ERR_NOOPERHOST(SERVER_NAME, client.getNickname()), STATUS_OK, client.getSockFd()));
		return;
	}

	// mauvais mdp
	if (!passwordMatchesUsername(name, password))
	{
		this->replies_.push_back(setReply(ERR_PASSWDMISMATCH(SERVER_NAME, client.getNickname()), STATUS_OK, client.getSockFd()));
		return;
	}

	// le client devient oper
	client.setIsOper(1);
	this->replies_.push_back(setReply(RPL_YOUREOPER(SERVER_NAME, client.getNickname()), STATUS_OK, client.getSockFd()));
}
