/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:16:21 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/30 12:48:19 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::user(Client& client, std::vector<std::string>& args)
{
	std::string	username;

	if (args.size() >= 2)
		username = args.at(1);
	else
		username = "";
	
	// si tentative de modification d'username 
	if (client.getAuth() == 1)
		this->replies_.push_back(setReply(ERR_ALREADYREGISTERED(SERVER_NAME, client.getNickname()), STATUS_OK, client.getSockFd()));

	// si pas d'username
	else if (username == "")
		this->replies_.push_back(setReply(ERR_NEEDMOREPARAMS(SERVER_NAME, client.getNickname(), "USER"), STATUS_AUTHFAILED, client.getSockFd()));
	
	else
		client.setUsername(username);
		
	// si le client a un nickname, valide l'authentification
	if (client.getNickname() != "*" && client.getAuth() == 0)
		validateAuth(client);
}
