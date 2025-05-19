/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:44:43 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/19 18:39:43 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HPP
# define ERROR_HPP

typedef std::string str;

# define RPL_WELCOME(name, client) (":" + str(name) + " 001 " + str(client) + " :Salut ma couille\r\n")
# define RPL_YOURHOST(name, client, version) (":" + str(name) + " 002 " + str(client) + " :Your host is " + str(name) + ", running in version " + str(version) + "\r\n")
# define RPL_CREATED(name, client, time) (":" + str(name) + " 003 " + str(client) + " :This server was created " + str(time) + "\r\n")
# define RPL_MYINFO(name, client, version) (":" + str(name) + " 004 " + str(client) + " :" + str(name) + " " + str(version) + "\r\n")

# define ERR_NOSUCHNICK(client, target) ("401 " + str(client) + " " + str(target) + " :No such nick\r\n")
# define ERR_CANNOTSENDTOCHAN(client, channel) ("404 " + str(client) + " " + str(channel) + " :Cannot send to channel\r\n")
# define ERR_NOTEXTTOSEND(client) ("412 " + str(client) + " :No text to send\r\n")
# define ERR_NONICKNAMEGIVEN(client) ("431 " + str(client) + " :No nickname given\r\n")
# define ERR_ERRONEUSNICKNAME(client, nickname) ("432 " + str(client) + " " + str(nickname) + ":Erroneus nickname\r\n")
# define ERR_NICKNAMEINUSE(client, nickname) ("433 " + str(client) + " " + str(nickname) + " :Nickname is already in use\r\n")
# define ERR_NEEDMOREPARAMS(client, command) ("461 " + str(client) + " " + str(command) + " :Not enough parameters\r\n")
# define ERR_ALREADYREGISTERED(client) ("462 " + str(client) + " :You may not reregister\r\n")
# define ERR_PASSWDMISMATCH(client) ("464 " + str(client) + " :Password incorrect\r\n")
# define ERR_CHANNELISFULL(client, channel) ("471 " + str(client) + " " + str(channel) + " :Cannot join channel (+l)\r\n")
# define ERR_INVITEONLYCHAN(client, channel) ("473 " + str(client) + " " + str(channel) + " :Cannot join channel (+i)\r\n")
# define ERR_BADCHANNELKEY(client, channel) ("475 " + str(client) + " " + str(channel) + " :Cannot join channel (+k)\r\n")
# define ERR_BADCHANMASK(channel) ("476 " + str(channel) + " :Bad Channel Mask\r\n")


# define PRIVMSG(client, target, message) (":" + str(client) + " PRIVMSG " + str(target) + " :" + str(message) + "\r\n")
# define QUIT_MSG ":ERROR Connection ended from client\r\n"
# define NICK_CHANGE(oldNick, newNick) (":" + str(oldNick) + " NICK :" + str(newNick) + "\r\n")

#endif
