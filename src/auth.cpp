/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auth.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:32:54 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/20 11:34:48 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::validateAuth(Client& client)
{
	client.setAuth(1);
	this->clients_[client.getNickname()] = client;
	this->replies_.push_back(RPL_WELCOME(SERVER_NAME, client.getNickname()) + RPL_YOURHOST(SERVER_NAME, client.getNickname(), SERVER_VERSION) + RPL_CREATED(SERVER_NAME, client.getNickname(), CREATION_DAY) + RPL_MYINFO(SERVER_NAME, client.getNickname(), SERVER_VERSION));
	this->status_.push_back(STATUS_OK);
	this->replies_.push_back(RPL_MOTDSTART(SERVER_NAME, client.getNickname()) + RPL_MOTD1(SERVER_NAME, client.getNickname()));
	this->status_.push_back(STATUS_OK);
	this->replies_.push_back(RPL_MOTD2 + RPL_ENDOFMOTD(SERVER_NAME, client.getNickname()));
	this->status_.push_back(STATUS_OK);
}