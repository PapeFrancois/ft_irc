/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:30:52 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/19 18:31:36 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::pong(Client& client, std::string& params)
{
	if (params == "")
	{
		this->replies_.push_back(ERR_NEEDMOREPARAMS(client.getNickname(), "PONG"));
		this->status_.push_back(STATUS_OK);
	}
	else
	{
		this->replies_.push_back(":" + str(SERVER_NAME) + " PONG " + params + "\r\n");
		this->status_.push_back(STATUS_OK);
	}
}