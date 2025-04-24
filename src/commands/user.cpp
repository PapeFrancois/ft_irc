/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:16:21 by hepompid          #+#    #+#             */
/*   Updated: 2025/04/24 11:04:59 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::string getUsername(std::string& params)
{
	std::string	username;
	int			spacePosition;

	spacePosition = 0;
	for (int i = 0; params[i]; i++)
	{
		if (params[i] == ' ')
		{
			spacePosition = i;
			break;
		}
	}
	username = params.substr(0, spacePosition);
	return username;
}

void Server::user(Client& client, std::string& params)
{
	std::string username;
	
	if (client.getAuth() == 1)
	{
		this->replies_.push_back(ERR_ALREADYREGISTERED(client.getNickname()));
		this->status_.push_back(STATUS_OK);
	}
	else if (params == "")
	{
		this->replies_.push_back(ERR_NEEDMOREPARAMS(client.getNickname(), "USER"));
		this->status_.push_back(STATUS_AUTHFAILED);
	}
	else
	{
		username = getUsername(params);
		client.setUsername(username);
		this->replies_.push_back(RPL_WELCOME(client.getNickname()));
		this->status_.push_back(STATUS_OK);
	}
}
