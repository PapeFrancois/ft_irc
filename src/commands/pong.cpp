/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:30:52 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/20 14:34:47 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::pong(Client& client, std::string& params)
{
	if (params == "")
	{
		// this->replies_.push_back(ERR_NEEDMOREPARAMS(SERVER_NAME, client.getNickname(), "PONG"));
		// this->status_.push_back(STATUS_OK);

		this->replies_.push_back(setReply(ERR_NEEDMOREPARAMS(SERVER_NAME, client.getNickname(), "PONG"), STATUS_OK, client.getSockFd()));
	}
	else
	{
		// this->replies_.push_back(":" + str(SERVER_NAME) + " PONG " + params + "\r\n");
		// this->status_.push_back(STATUS_OK);

		this->replies_.push_back(setReply(PONG_MSG(SERVER_NAME), STATUS_OK, client.getSockFd()));
	}
}