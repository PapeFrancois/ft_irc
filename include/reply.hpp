/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:44:43 by hepompid          #+#    #+#             */
/*   Updated: 2025/04/29 17:08:31 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HPP
# define ERROR_HPP

typedef std::string str;

# define RPL_WELCOME(client) ("001 " + str(client) + " :Salut ma couille\r\n")
# define RPL_YOURHOST(client, serverName, version) ("002 " + str(client) + " :Your host is " + str(serverName) + " running in version " + str(version) + "\r\n")
# define RPL_CREATED(client, dateTime) ("003 " + str(client) + " :This server was created " + str(dateTime) + "\r\n")
# define RPL_MYINFO(client, serverName, version) ("004 " + str(client) + " :" + str(serverName) + " " + str(version) + "\r\n")
# define ERR_NOSUCHNICK(client, target) ("401 " + str(client) + " " + str(target) + " :No such nick\r\n")
# define ERR_CANNOTSENDTOCHAN(client, channel) ("404 " + str(client) + " " + str(channel) + " :Cannot send to channel\r\n")
# define ERR_NOTEXTTOSEND(client) ("412 " + str(client) + " :No text to send\r\n")
# define ERR_NONICKNAMEGIVEN(client) ("431 " + str(client) + " :No nickname given\r\n")
# define ERR_ERRONEUSNICKNAME(client, nickname) ("432 " + str(client) + " " + str(nickname) + ":Erroneus nickname\r\n")
# define ERR_NICKNAMEINUSE(client, nickname) ("433 " + str(client) + " " + str(nickname) + " :Nickname is already in use\r\n")
# define ERR_NEEDMOREPARAMS(client, command) ("461 " + str(client) + " " + str(command) + " :Not enough parameters\r\n")
# define ERR_ALREADYREGISTERED(client) ("462 " + str(client) + " :You may not reregister\r\n")
# define ERR_PASSWDMISMATCH(client) ("464 " + str(client) + " :Password incorrect\r\n")

# define QUIT_MSG ":ERROR Connection ended from client\r\n"
// # define NICK_CHANGE(oldNick, newNick) (":" + str(oldNick) + "!hepompid@127.0.0.1 " + " NICK :" + str(newNick) + "\r\n")

#endif
