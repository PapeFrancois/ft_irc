/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:01:29 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/13 19:39:43 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::string extractTarget(std::string& params)
{
	int	start;
	int	end;
	
	start = 0;
	while (params[start] == ' ')
		start++;
	
	end = start;
	while (params[end] != ' ' && params[end])
		end++;

	return params.substr(start, end - start);
}

std::string extractMessage(std::string& params)
{
	int			start;
	int			end;
	
	start = 0;
	while (params[start] == ' ')
		start++;
	while (params[start] != ' ' && params[start])
		start++;
	if (!params[start])
		return "";
	while (params[start] == ' ')
		start++;
		
	end = start;
	while (params[end])
		end++;

	return params.substr(start, end - start);
}

bool findUser(std::string& target, std::map<int, Client>& clients)
{
	typedef std::map<int, Client>::const_iterator	it;

	for (it it = clients.begin(); it != clients.end(); it++)
		if (it->second.getNickname() == target)
			return true;
	return false;
}

bool findChannel(std::string& target, std::vector<std::string>& channels)
{
	typedef std::vector<std::string>::const_iterator	it;

	for (it it = channels.begin(); it != channels.end(); it++)
		if (*it == target)
			return true;
	return false;
}

Channel getChannel(std::string& target, std::vector<std::string>& channels)
{
	typedef std::vector<std::string>::const_iterator	it;

	for (it it = channels.begin(); it != channels.end(); it++)
		if (*it == target)
			return *it;
			
	// sinon compile pas
	return *channels.begin();
}

int getTargetFd(std::string& target, std::map<int, Client>& clients)
{
	typedef std::map<int, Client>::const_iterator	it;

	for (it it = clients.begin(); it != clients.end(); it++)
		if (it->second.getNickname() == target)
			return it->first;

	// sinon compile pas
	return 0;
}

void Server::privmsg(Client& client, std::string& params)
{
    std::string target;
	int			targetFd;
    std::string message;
	std::string	reply;
    char		buffer[BUFFERSIZE + 1];

    target = extractTarget(params);
    message = extractMessage(params);
    std::cout << PURPLE_BG << "target = " << target << ", message = " << message << RESET << std::endl;
	
	// target mais pas de message
	if (message.empty())
	{
		this->replies_.push_back(ERR_NOTEXTTOSEND(client.getNickname()));
		this->status_.push_back(STATUS_OK);
	}

	// target est un user, mais il n'existe pas
	else if (message[0] != '#' && !findUser(target, this->clients_))
	{
		this->replies_.push_back(ERR_NOSUCHNICK(client.getNickname(), target));
		this->status_.push_back(STATUS_OK);
	}

	// target est un channel existant dont le mode i ou k est active
	else if (message[0] == '#' && findChannel(target, this->channels_)
				&& (getChannel(target, this->channels_).getIMode() == true
					|| getChannel(target, this->channels_).getKey() != ""))
	{
		this->replies_.push_back(ERR_CANNOTSENDTOCHAN(client.getNickname(), target));
		this->status_.push_back(STATUS_OK);
	}


	std::memset(buffer, 0, sizeof(buffer));
	std::strcpy(buffer, PRIVMSG(client.getNickname(), target, message).c_str());
	targetFd = getTargetFd(target, this->clients_);
	if (send(targetFd, buffer, BUFFERSIZE, 0) == -1)
	{
		endConnection(targetFd);
		std::cout << RED << "Error: Send failed for fd " << targetFd << RESET << std::endl;
	}
}


/*

3 cas d'erreur :
- target mais pas de message
- username incorrect
- si le channel n'existe pas, le creer
- channel dans lequel l'user ne fait pas partie, et dont le mode i ou k est actif

*/