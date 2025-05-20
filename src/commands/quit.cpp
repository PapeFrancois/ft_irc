/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:46:57 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/20 14:52:59 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::quit(Client& client)
{
    // this->replies_.push_back("ERROR Connection ended from client\r\n");
    // this->status_.push_back(STATUS_QUIT);

	this->replies_.push_back(setReply(QUIT_MSG(client.getNickname()), STATUS_QUIT, client.getSockFd()));
}
