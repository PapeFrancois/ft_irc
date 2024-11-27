/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:56:31 by hepompid          #+#    #+#             */
/*   Updated: 2024/11/27 23:15:30 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::pass(std::string params)
{	
	if (params == this->password_)
		this->passOK_ = 1;
	else
	{
		this->passOK_ = -1;
		this->replies_.push_back(ERR_PASSWDMISMATCH);
	}
}