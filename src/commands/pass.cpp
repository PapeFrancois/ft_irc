/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:56:31 by hepompid          #+#    #+#             */
/*   Updated: 2024/11/28 00:12:49 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::pass(Client& client, std::string params)
{	
	if (params == this->password_)
		client.setAuth(1);
	else
	{
		client.setAuth(-1);
		this->replies_.push_back(ERR_PASSWDMISMATCH);
	}
}