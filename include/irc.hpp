/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:37:30 by hepompid          #+#    #+#             */
/*   Updated: 2025/06/03 14:53:52 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

# include <iostream>
# include <string>
# include <cctype>

# include "Server.hpp"
# include "ansiCodes.hpp"

void stopServer(int signal);

class NotNumber : public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return "port argument has to be a number";
		}
};

class NumberTooBig : public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return "port argument has to fit in 16bit";
		}
};

#endif
