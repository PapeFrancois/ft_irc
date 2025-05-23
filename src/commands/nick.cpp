/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:05:24 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/23 12:27:56 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool validNick(std::string& nickname)
{
	for (size_t i = 0; i < nickname.length(); i++)
	{
		if (nickname[i] < '0')
			return false;
		else if (nickname[i] > '9' && nickname[i] < 'A')
			return false;
		else if (nickname[i] > ']' && nickname[i] < 'a')
			return false;
		else if (nickname[i] > '}')
			return false;
	}	
	return true;
}

std::string tolower(const std::string &nickname)
{
	std::string tolower;

	for (int i = 0; nickname[i]; i++)
	{
		if (nickname[i] >= 'A' && nickname[i] <= 'Z')
			tolower += nickname[i] + 32;
		else
			tolower += nickname[i];
	}
	return tolower;
}

bool uniqueNick(std::map<int, Client>& clients, std::string& nickname)
{
	typedef std::map<int, Client>::iterator iterator;

	for (iterator it = clients.begin(); it != clients.end(); it++)
		if (tolower(it->second.getNickname()) == tolower(nickname))
			return false;
	return true;
}

void Server::nick(Client& client, std::string& nickname)
{
	
	// si aucun nickname n'est donne lors de l'authentification
	if (nickname == "" && client.getAuth() == 0)
		this->replies_.push_back(setReply(ERR_NONICKNAMEGIVEN(SERVER_NAME, client.getNickname()), STATUS_OK, client.getSockFd()));

	// si commande nick seule et client authentifie
	else if (nickname == "" && client.getAuth() == 1)
		this->replies_.push_back(setReply(client.getNickname() + "\r\n", STATUS_OK, client.getSockFd()));

	// si le nickname n'est pas valide
	else if (validNick(nickname) == false)
	{
		if (client.getAuth() == 0)
			this->replies_.push_back(setReply(ERR_ERRONEUSNICKNAME(SERVER_NAME, client.getNickname(), nickname), STATUS_AUTHFAILED, client.getSockFd()));
		else
			this->replies_.push_back(setReply(ERR_ERRONEUSNICKNAME(SERVER_NAME, client.getNickname(), nickname), STATUS_OK, client.getSockFd()));
	}

	// si le nickname est deja pris
	else if (uniqueNick(this->fdCli_, nickname) == false)
	{
		if (client.getAuth() == 0)
			this->replies_.push_back(setReply(ERR_NICKNAMEINUSE(SERVER_NAME, client.getNickname(), nickname), STATUS_AUTHFAILED, client.getSockFd()));
		else
			this->replies_.push_back(setReply(ERR_NICKNAMEINUSE(SERVER_NAME, client.getNickname(), nickname), STATUS_OK, client.getSockFd()));
	}

	// nickname accepte
	else
	{
		// changement de nickname post auth
		if (client.getAuth() == 1)
			this->replies_.push_back(setReply(NICK_CHANGE(client.getNickname(), client.getUsername(), SERVER_HOST, nickname), STATUS_OK, client.getSockFd()));
		
		client.setNickname(nickname);
		
		// si un username est deja rempli, valide l'authentification sauf si on attend cap end
		if (client.getAuth() == 0 && client.getUsername() != "" && client.getCap() == 0)
			validateAuth(client);
	}

}
