/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:37:30 by hepompid          #+#    #+#             */
/*   Updated: 2024/11/18 18:01:10 by hepompid         ###   ########.fr       */
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
#  define RED "\033[31m"
#  define GREEN "\033[32m"
#  define YELLOW "\033[33m"
#  define UNDERLINE "\033[4m"
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
