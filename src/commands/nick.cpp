/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:05:24 by hepompid          #+#    #+#             */
/*   Updated: 2024/12/03 19:35:57 by hepompid         ###   ########.fr       */
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

bool uniqueNick(std::map<int, Client>& clients, std::string& nickname)
{
	typedef std::map<int, Client>::iterator iterator;

	for (iterator it = clients.begin(); it != clients.end(); it++)
	{
		if (it->second.getNickname() == nickname)
			return false;
	}
	return true;
}

void Server::nick(Client& client, std::string& nickname)
{
	if (nickname == "")
	{
		this->replies_.push_back(ERR_NONICKNAMEGIVEN(client.getNickname()));
		if (client.getAuth() == 0)
			this->status_.push_back(1);
		else
			this->status_.push_back(0);
	}
	else if (validNick(nickname) == false)
	{
		this->replies_.push_back(ERR_ERRONEUSNICKNAME(client.getNickname(), nickname));
		if (client.getAuth() == 0)
			this->status_.push_back(1);
		else
			this->status_.push_back(0);
	}
	else if (uniqueNick(this->clients_, nickname) == false)
	{
		this->replies_.push_back(ERR_NICKNAMEINUSE(client.getNickname(), nickname));
		if (client.getAuth() == 0)
			this->status_.push_back(1);
		else
			this->status_.push_back(0);
	}
	else
		client.setNickname(nickname);
}
