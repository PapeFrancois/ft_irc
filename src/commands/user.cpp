/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:16:21 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/20 15:20:07 by hepompid         ###   ########.fr       */
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
		this->replies_.push_back(setReply(ERR_ALREADYREGISTERED(SERVER_NAME, client.getNickname()), STATUS_OK, client.getSockFd()));

	// si pas d'username
	else if (params == "")
		this->replies_.push_back(setReply(ERR_NEEDMOREPARAMS(SERVER_NAME, client.getNickname(), "USER"), STATUS_AUTHFAILED, client.getSockFd()));
	
	else
		client.setUsername(getUsername(params));
		
	// si le client a un nickname, valide l'authentification sauf si on attend capend
	if (client.getNickname() != "*" && client.getAuth() == 0 && client.getCap() == 0)
		validateAuth(client);
}
