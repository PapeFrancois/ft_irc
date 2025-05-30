/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:13:00 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/30 12:35:09 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::oper(Client& client, std::vector<std::string>& args)
{
	std::string	name;
	std::string	password;
	
	// le client est deja operator
	if (client.getIsOper())
		return;
		
	// pas assez de params, on attend un name et un password
	if (args.size() < 3)
	{
		this->replies_.push_back(setReply(ERR_NEEDMOREPARAMS(SERVER_NAME, client.getNickname(), "OPER"), STATUS_OK, client.getSockFd()));
		return;
	}
		
	name = args.at(1);
	password = args.at(2);

	
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
