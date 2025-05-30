/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:56:31 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/30 19:07:09 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::pass(Client& client, std::vector<std::string>& args)
{
	std::string	key;
	
	// pas de mot de passe donne dans la commande
	if (args.size() == 1)
	{
		std::cout << RED_BG << "1" << RESET << std::endl;
		this->replies_.push_back(setReply(ERR_NEEDMOREPARAMS(SERVER_NAME, client.getNickname(), "PASS"), STATUS_AUTHFAILED, client.getSockFd()));
		return;
	}
		
	// le client est deja enregistre
	if (client.getAuth() == 1)
	{
		std::cout << RED_BG << "2" << RESET << std::endl;
		this->replies_.push_back(setReply(ERR_ALREADYREGISTERED(SERVER_NAME, client.getNickname()), STATUS_OK, client.getSockFd()));
		return;
	}

	key = args.at(1);
	std::cout << "arg 1 = " << args.at(1) << " key = " << key << std::endl;
	
	// le mot de passe est mauvais
	if (key != this->password_)
	{
		std::cout << RED_BG << "3" << RESET << std::endl;
		this->replies_.push_back(setReply(ERR_PASSWDMISMATCH(SERVER_NAME, client.getNickname()), STATUS_AUTHFAILED, client.getSockFd()));
		return;
	}
		
	// le mot de passe est bon
	client.setPassOK(1);
	std::cout << GREEN_BG << "mdp valide" << RESET << std::endl;
}