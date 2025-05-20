/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:01:29 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/20 15:19:35 by hepompid         ###   ########.fr       */
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

// bool findUser(std::string& target, std::map<int, Client>& clients)
// {
// 	typedef std::map<int, Client>::const_iterator	it;

// 	for (it it = clients.begin(); it != clients.end(); it++)
// 		if (it->second.getNickname() == target)
// 			return true;
// 	return false;
// }

// bool findChannel(std::string& target, std::vector<std::string>& channels)
// {
// 	typedef std::vector<std::string>::const_iterator	it;

// 	for (it it = channels.begin(); it != channels.end(); it++)
// 		if (*it == target)
// 			return true;
// 	return false;
// }

// Channel getChannel(std::string& target, std::vector<std::string>& channels)
// {
// 	typedef std::vector<std::string>::const_iterator	it;

// 	for (it it = channels.begin(); it != channels.end(); it++)
// 		if (*it == target)
// 			return *it;
			
// 	// sinon compile pas
// 	return *channels.begin();
// }

// int getTargetFd(std::string& target, std::map<int, Client>& clients)
// {
// 	typedef std::map<int, Client>::const_iterator	it;

// 	for (it it = clients.begin(); it != clients.end(); it++)
// 		if (it->second.getNickname() == target)
// 			return it->first;

// 	// sinon compile pas
// 	return 0;
// }

void Server::privmsg(Client& client, std::string& params)
{
    std::string target;
	int			targetFd;
    std::string message;

    target = extractTarget(params);
    message = extractMessage(params);
    std::cout << PURPLE_BG << "target = " << target << ", message = " << message << RESET << std::endl;
	
	// target mais pas de message
	if (message.empty())
		this->replies_.push_back(setReply(ERR_NOTEXTTOSEND(SERVER_NAME, client.getNickname()), STATUS_OK, client.getSockFd()));

	// target est un user
	else if (message[0] != '#')
	{
		// l'user n'existe pas
		if (!getClientFromNick(target))
			this->replies_.push_back(setReply(ERR_NOSUCHNICK(SERVER_NAME, client.getNickname(), target), STATUS_OK, client.getSockFd()));
		// envoi du message a l'user
		else
		{
			targetFd = getClientFromNick(target)->getSockFd();
			this->replies_.push_back(setReply(PRIVMSG(client.getNickname(), target, message), STATUS_OK, targetFd));
		}
	}

	// target est un channel
	else if (message[0] == '#')
	{
		// le channel existe mais le mode i ou k est active
		if (this->channels_.find(target) != this->channels_.end() 
			&& (this->channels_[target].getIMode() == true
				|| this->channels_[target].getKey() != ""))
		{
			this->replies_.push_back(setReply(ERR_CANNOTSENDTOCHAN(SERVER_NAME, client.getNickname(), target), STATUS_OK, client.getSockFd()));
		}
	}


}


/*

3 cas d'erreur :
- target mais pas de message
- username incorrect
- si le channel n'existe pas, le creer
- channel dans lequel l'user ne fait pas partie, et dont le mode i ou k est actif

*/