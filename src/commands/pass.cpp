/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:56:31 by hepompid          #+#    #+#             */
/*   Updated: 2025/04/24 11:04:43 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::pass(Client& client, std::string params)
{	
	if (params == this->password_)
		client.setPassOK(1);
	else if (params == "")
	{
		this->replies_.push_back(ERR_NEEDMOREPARAMS(client.getNickname(), "PASS"));
		this->status_.push_back(STATUS_AUTHFAILED);
	}
	else if (client.getAuth() == 1)
	{
		this->replies_.push_back(ERR_ALREADYREGISTERED(client.getNickname()));
		this->status_.push_back(STATUS_OK);
	}
	else
	{
		this->replies_.push_back(ERR_PASSWDMISMATCH(client.getNickname()));
		this->status_.push_back(STATUS_AUTHFAILED);
	}
}