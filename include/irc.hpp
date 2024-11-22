/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:37:30 by hepompid          #+#    #+#             */
/*   Updated: 2024/11/21 11:49:53 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

# include <iostream>
# include <string>
# include <cctype>

# include "Server.hpp"

# ifndef ANSI_CODES
#  define ANSI_CODES

#  define RESET "\033[0m"
#  define BOLD "\033[1m"
#  define UNDERLINE "\033[4m"

#  define BLACK "\033[30m"
#  define RED "\033[31m"
#  define GREEN "\033[32m"
#  define YELLOW "\033[33m"
#  define BLUE "\033[34m"
#  define PURPLE "\033[35m"
#  define CYAN "\033[36m"
#  define WHITE "\033[37m"

#  define BLACK_BG "\033[40m"
#  define RED_BG "\033[41m"
#  define GREEN_BG "\033[42m"
#  define YELLOW_BG "\033[43m"
#  define BLUE_BG "\033[44m"
#  define PURPLE_BG "\033[45m"
#  define CYAN_BG "\033[46m"
#  define WHITE_BG "\033[47m"
# endif

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
