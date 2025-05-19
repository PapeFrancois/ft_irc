/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:05:24 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/19 19:02:42 by hepompid         ###   ########.fr       */
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
	{
		if (tolower(it->second.getNickname()) == tolower(nickname))
			return false;
	}
	return true;
}

void Server::nick(Client& client, std::string& nickname)
{
	
	// si aucun nickname n'est donne lors de l'authentification
	if (nickname == "" && client.getAuth() == 0)
	{
		this->replies_.push_back(ERR_NONICKNAMEGIVEN(SERVER_NAME, client.getNickname()));
		this->status_.push_back(STATUS_OK);
	}

	// si commande nick seule et client authentifie
	else if (nickname == "" && client.getAuth() == 1)
	{
		this->replies_.push_back(client.getNickname() + "\r\n");
		this->status_.push_back(STATUS_OK);
	}

	// si le nickname n'est pas valide
	else if (validNick(nickname) == false)
	{
		this->replies_.push_back(ERR_ERRONEUSNICKNAME(SERVER_NAME, client.getNickname(), nickname));
		if (client.getAuth() == 0)
			this->status_.push_back(STATUS_AUTHFAILED);
		else
			this->status_.push_back(STATUS_OK);
	}

	// si le nickname est deja pris
	else if (uniqueNick(this->fdCli_, nickname) == false)
	{
		this->replies_.push_back(ERR_NICKNAMEINUSE(SERVER_NAME, client.getNickname(), nickname));
		if (client.getAuth() == 0)
			this->status_.push_back(STATUS_AUTHFAILED);
		else
			this->status_.push_back(STATUS_OK);
	}

	// nickname accepte
	else
	{
		// changement de nickname post auth
		if (client.getAuth() == 1)
		{
			this->replies_.push_back(NICK_CHANGE(SERVER_NAME, client.getNickname(), nickname));
			this->status_.push_back(STATUS_OK);
		}
		
		client.setNickname(nickname);
		
		// si un username est deja rempli, valide l'authentification sauf si on attend cap end
		if (client.getAuth() == 0 && client.getUsername() != "" && client.getCap() == 0)
		{
			client.setAuth(1);
			this->clients_[client.getNickname()] = client;
			this->replies_.push_back(RPL_WELCOME(SERVER_NAME, client.getNickname()) + RPL_YOURHOST(SERVER_NAME, client.getNickname(), SERVER_VERSION) + RPL_CREATED(SERVER_NAME, client.getNickname(), CREATION_DAY) + RPL_MYINFO(SERVER_NAME, client.getNickname(), SERVER_VERSION));
			this->status_.push_back(STATUS_OK);
		}
		

		// std::cout << PURPLE_BG << "client nickname set to " << client.getNickname() << RESET << std::endl;
	}

}
