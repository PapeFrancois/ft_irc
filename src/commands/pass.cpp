/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:56:31 by hepompid          #+#    #+#             */
/*   Updated: 2025/06/01 16:18:37 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::pass(Client& client, std::vector<std::string>& args)
{
	std::string	key;
	
	// pas de mot de passe donne dans la commande
	if (args.size() == 1)
	{
		this->replies_.push_back(setReply(ERR_NEEDMOREPARAMS(SERVER_NAME, client.getNickname(), "PASS"), STATUS_AUTHFAILED, client.getSockFd()));
		return;
	}
		
	// le client est deja enregistre
	if (client.getAuth() == 1)
	{
		this->replies_.push_back(setReply(ERR_ALREADYREGISTERED(SERVER_NAME, client.getNickname()), STATUS_OK, client.getSockFd()));
		return;
	}

	key = args.at(1);
	
	// le mot de passe est mauvais
	if (key != this->password_)
	{
		this->replies_.push_back(setReply(ERR_PASSWDMISMATCH(SERVER_NAME, client.getNickname()), STATUS_AUTHFAILED, client.getSockFd()));
		return;
	}
		
	// le mot de passe est bon
	client.setPassOK(1);
}