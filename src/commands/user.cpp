/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:16:21 by hepompid          #+#    #+#             */
/*   Updated: 2025/04/29 16:13:46 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::string getUsername(std::string& params)
{
	std::string	username;
	int			spacePosition;

	spacePosition = params.find(' ');
	username = params.substr(0, spacePosition);
	return username;
}

void Server::user(Client& client, std::string& params)
{
	// si tentative de modification d'username 
	if (client.getAuth() == 1)
	{
		this->replies_.push_back(ERR_ALREADYREGISTERED(client.getNickname()));
		this->status_.push_back(STATUS_OK);
	}

	// si pas d'username
	else if (params == "")
	{
		this->replies_.push_back(ERR_NEEDMOREPARAMS(client.getNickname(), "USER"));
		this->status_.push_back(STATUS_AUTHFAILED);
	}
	
	else
		client.setUsername(getUsername(params));
		
	// si le client a un nickname, valide l'authentification
	if (client.getNickname() != "*" && client.getAuth() == 0)
	{
		client.setAuth(1);
		this->replies_.push_back(RPL_WELCOME(client.getNickname()) + RPL_YOURHOST(client.getNickname(), SERVER_NAME, SERVER_VERSION) + RPL_CREATED(client.getNickname(), CREATION_DAY) + RPL_MYINFO(client.getNickname(), SERVER_NAME, SERVER_VERSION));
		this->status_.push_back(STATUS_OK);
	}
}
