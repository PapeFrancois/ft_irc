/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:46:57 by hepompid          #+#    #+#             */
/*   Updated: 2025/04/24 10:59:54 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::quit()
{
    this->replies_.push_back("ERROR Connection ended from client\r\n");
    this->status_.push_back(STATUS_QUIT);
}
