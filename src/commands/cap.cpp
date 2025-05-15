/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 00:25:45 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/15 13:26:58 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::cap(Client& client, std::string& params)
{
	if (params == "LS")
	{
		// client.setCap(1);
		// this->replies_.push_back("CAP * LS :\r\n");
		// this->status_.push_back(STATUS_OK);
	}
	else if (params == "END" && client.getNickname() != "*" && client.getUsername() != "")
	{
		std::cout << BLUE << "end" << RESET << std::endl;
		client.setAuth(1);
		this->clients_[client.getNickname()] = client;
		this->replies_.push_back("\r\n" + RPL_WELCOME(client.getNickname()) + RPL_YOURHOST(client.getNickname(), SERVER_NAME, SERVER_VERSION) + RPL_CREATED(client.getNickname(), CREATION_DAY) + RPL_MYINFO(client.getNickname(), SERVER_NAME, SERVER_VERSION));
		this->status_.push_back(STATUS_OK);
	}
}
