/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:30:52 by hepompid          #+#    #+#             */
/*   Updated: 2024/12/10 17:39:36 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::pong(Client& client, std::string& params)
{
	if (params == "")
	{
		this->replies_.push_back(ERR_NEEDMOREPARAMS(client.getNickname(), "PONG"));
		this->status_.push_back(0);
	}
	else
	{
		this->replies_.push_back("PONG " + params + "\r\n");
		this->status_.push_back(0);
	}
}