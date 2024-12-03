/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:44:43 by hepompid          #+#    #+#             */
/*   Updated: 2024/12/03 19:42:47 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HPP
# define ERROR_HPP

typedef std::string str;

# define RPL_WELCOME(nick) ("001 " + str(nick) + " :Salut ma couille\r\n")
# define ERR_NONICKNAMEGIVEN(nick) ("431 " + str(nick) + " :No nickname given\r\n")
# define ERR_ERRONEUSNICKNAME(nick, wantedNick) ("432 " + str(nick) + str(wantedNick) + ":Erroneus nickname\r\n")
# define ERR_NICKNAMEINUSE(nick, wantedNick) ("433 " + str(nick) + str(wantedNick) + " :Nickname is already in use\r\n")
# define ERR_NEEDMOREPARAMS(nick, command) ("461 " + str(nick) + " " + str(command) + " :Not enough parameters\r\n")
# define ERR_ALREADYREGISTERED(nick) ("462 " + str(nick) + " :You may not reregister\r\n")
# define ERR_PASSWDMISMATCH(nick) ("464 " + str(nick) + " :Password incorrect\r\n")

#endif
