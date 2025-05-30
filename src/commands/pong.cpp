/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:30:52 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/30 12:49:47 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::pong(Client& client, std::vector<std::string>& args)
{
	if (args.size() < 2)
		this->replies_.push_back(setReply(ERR_NEEDMOREPARAMS(SERVER_NAME, client.getNickname(), "PONG"), STATUS_OK, client.getSockFd()));
	else
		this->replies_.push_back(setReply(PONG_MSG(SERVER_NAME, args.at(1)), STATUS_OK, client.getSockFd()));
}