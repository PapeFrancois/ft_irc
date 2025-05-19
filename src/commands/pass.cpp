/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:56:31 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/19 19:02:57 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::pass(Client& client, std::string params)
{	
	if (params == this->password_)
		client.setPassOK(1);
	else if (params == "")
	{
		this->replies_.push_back(ERR_NEEDMOREPARAMS(SERVER_NAME, client.getNickname(), "PASS"));
		this->status_.push_back(STATUS_AUTHFAILED);
	}
	else if (client.getAuth() == 1)
	{
		this->replies_.push_back(ERR_ALREADYREGISTERED(SERVER_NAME, client.getNickname()));
		this->status_.push_back(STATUS_OK);
	}
	else
	{
		this->replies_.push_back(ERR_PASSWDMISMATCH(SERVER_NAME, client.getNickname()));
		this->status_.push_back(STATUS_AUTHFAILED);
	}
}