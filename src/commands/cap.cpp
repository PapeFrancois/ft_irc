/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 00:25:45 by hepompid          #+#    #+#             */
/*   Updated: 2024/12/03 18:09:38 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::cap(std::string& params)
{
	if (params == "LS 302")
	{
		this->replies_.push_back("CAP * LS :\r\n");
		this->status_.push_back(0);
	}
}
