/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:44:43 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/26 16:37:25 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HPP
# define ERROR_HPP

typedef std::string str;

# define RPL_WELCOME(name, client) (":" + str(name) + " 001 " + str(client) + " :It's britney bitch\r\n")
# define RPL_YOURHOST(name, client, version) (":" + str(name) + " 002 " + str(client) + " :Your host is " + str(name) + ", running in version " + str(version) + "\r\n")
# define RPL_CREATED(name, client, time) (":" + str(name) + " 003 " + str(client) + " :This server was created " + str(time) + "\r\n")
# define RPL_MYINFO(name, client, version) (":" + str(name) + " 004 " + str(client) + " :" + str(name) + " " + str(version) + "\r\n")

# define RPL_CHANNELMODEIS(name, client, channel, modes) (":" + str(name) + " 324 " + str(client) + " " + str(channel) + " " + str(modes) + "\r\n")
# define RPL_TOPIC(name, client, channel, topic) (":" + str(name) + " 332 " + str(client) + " " + str(channel) + " " + str(topic) + "\r\n")
# define RPL_INVITING(name, client, target, channel) (":" + str(name) + " 341 " + str(client) + " " + str(target) + " " + str(channel) + "\r\n")
# define RPL_NAMREPLY(name, client, channel, members) (":" + str(name) + " 353 " + str(client) + " = " + str(channel) + " :" + str(members) + "\r\n")
# define RPL_ENDOFNAMES(name, client, channel) (":" + str(name) + " 366 " + str(client) + " " + str(channel) + " :End of /NAMES list.\r\n")
# define RPL_ENDOFBANLIST(name, client, channel) (":" + str(name) + " 368 " + str(client) + " " + str(channel) + " :End of Channel Ban List\r\n")

# define RPL_MOTD1(name, client) (":" + str(name) + " 372 " + str(client) + " :\n\
-  _          _ _                                                    \n\
- | |        (_) |                                                   \n\
- | |__  _ __ _| |_ _ __   ___ _   _   ___ _ __   ___  __ _ _ __ ___ \n\
- | '_ \\| '__| | __| '_ \\ / _ \\ | | | / __| '_ \\ / _ \\/ _` | '__/ __|\n\
- | |_) | |  | | |_| | | |  __/ |_| | \\__ \\ |_) |  __/ (_| | |  \\__ \\\n")

 # define RPL_MOTD2 "\
- |_.__/|_|  |_|\\__|_| |_|\\___|\\__, | |___/ .__/ \\___|\\__,_|_|  |___/\n\
-                               __/ |     | |                        \n\
-                              |___/      |_|                        \r\n"


# define RPL_MOTDSTART(name, client) (":" + str(name) + " 375 " + str(client) + " :- " + str(name) + " Message of the day -\r\n")
# define RPL_ENDOFMOTD(name, client) (":" + str(name) + " 376 " + str(client) + " :- End of /MOTD command.\r\n")
# define RPL_YOUREOPER(name, client) (":" + str(name) + " 381 " + str(client) + " :You are now an IRC operator\r\n")


# define ERR_NOSUCHNICK(name, client, target) (":" + str(name) + " 401 " + str(client) + " " + str(target) + " :No such nick\r\n")
# define ERR_NOSUCHCHANNEL(name, client, channel) (":" + str(name) + " 403 " + str(client) + " " + str(channel) + " :No such channel\r\n")
# define ERR_CANNOTSENDTOCHAN(name, client, channel) (":" + str(name) + " 404 " + str(client) + " " + str(channel) + " :Cannot send to channel\r\n")
# define ERR_NOTEXTTOSEND(name, client) (":" + str(name) + " 412 " + str(client) + " :No text to send\r\n")
# define ERR_NONICKNAMEGIVEN(name, client) (":" + str(name) + " 431 " + str(client) + " :No nickname given\r\n")
# define ERR_ERRONEUSNICKNAME(name, client, nickname) (":" + str(name) + " 432 " + str(client) + " " + str(nickname) + ":Erroneus nickname\r\n")
# define ERR_NICKNAMEINUSE(name, client, nickname) (":" + str(name) + " 433 " + str(client) + " " + str(nickname) + " :Nickname is already in use\r\n")
# define ERR_USERNOTINCHANNEL(name, client, channel, user) (":" + str(name), + " 441 " + str(client) + " " + str(channel) + " " + str(user) + " :User is not on that channel\r\n")
# define ERR_NOTONCHANNEL(name, client, channel) (":" + str(name) + " 442 " + str(client) + " " + str(channel) + " :You're not on that channel\r\n")
# define ERR_USERONCHANNEL(name, client, nick, channel) (":" + str(name) + " 443 " + str(client) + " " + str(nick) + " " + str(channel) + ":Is already on channel\r\n")
# define ERR_NEEDMOREPARAMS(name, client, command) (":" + str(name) + " 461 " + str(client) + " " + str(command) + " :Not enough parameters\r\n")
# define ERR_ALREADYREGISTERED(name, client) (":" + str(name) + " 462 " + str(client) + " :You may not reregister\r\n")
# define ERR_PASSWDMISMATCH(name, client) (":" + str(name) + " 464 " + str(client) + " :Password incorrect\r\n")
# define ERR_CHANNELISFULL(name, client, channel) (":" + str(name) + " 471 " + str(client) + " " + str(channel) + " :Cannot join channel (+l)\r\n")
# define ERR_INVITEONLYCHAN(name, client, channel) (":" + str(name) + " 473 " + str(client) + " " + str(channel) + " :Cannot join channel (+i)\r\n")
# define ERR_BADCHANNELKEY(name, client, channel) (":" + str(name) + " 475 " + str(client) + " " + str(channel) + " :Cannot join channel (+k)\r\n")
# define ERR_BADCHANMASK(name, channel) (":" + str(name) + " 476 " + str(channel) + " :Bad Channel Mask\r\n")
# define ERR_NOPRIVILEGES(name, client) (":" + str(name) + " 481 " + str(client) + " :Permission Denied- You're not an IRC operator\r\n")
# define ERR_CHANOPRIVSNEEDED(name, client, channel) (":" + str(name) + " 482 " + str(client) + " " + str(channel) + " :You're not channel operator\r\n")
# define ERR_NOOPERHOST(name, client) (":" + str(name) + " 491 " + str(client) + " :No Oper block for your host\r\n")


# define PRIVMSG(client, user, host, target, message) (":" + str(client) + "!" + str(user) + "@" + str(host) + " PRIVMSG " + str(target) + " :" + str(message) + "\r\n")
# define QUIT_MSG(client, user, host, reason) (":" + str(client) + "!" + str(user) + "@" + str(host) + " QUIT " + str(reason) + "\r\n")
# define NICK_CHANGE(oldNick, user, host, newNick) (":" + str(oldNick) + "!" + str(user) + "@" + str(host) + " NICK :" + str(newNick) + "\r\n")
# define PONG_MSG(name) (":" + str(name) + " PONG " + params + "\r\n")
# define JOIN_MSG(client, user, host, channel) (":" + str(client) + "!" + str(user) + "@" + str(host) + " JOIN :" + str(channel) + "\r\n")
# define PART_MSG(client, user, host, channel) (":" + str(client) + "!" + str(user) + "@" + str(host) + " PART " + str(channel) + "\r\n")
# define KICK_MSG(client, user, host, channel, target, message) (":" + str(client) + "!" + str(user) + "@" + str(host) + " KICK " + str(channel) + " " + str(target) + " " + str(message) + "\r\n")
# define INVITE_MSG(client, user, host, target, channel) (":" + str(client) + "!" + str(user) + "@" + str(host) + " INVITE " + str(target) + " :" + str(channel) + "\r\n")
# define TOPIC_MSG(client, user, host, channel, topic) (":" + str(client) + "!" + str(user) + "@" + str(host) + " TOPIC " + str(channel) + " " + str(topic) + "\r\n")


# define PRINT_NICK(client, user, host) (":" + str(client) + "!" + str(user) + "@" + str(host) + " NICK :" + str(client) + "\r\n")
# define PRINT_TOPIC(client, user, host, topic) (":" + str(client) + "!" + str(user) + "@" + str(host) + " TOPIC :" + str(topic) + "\r\n")

#endif
