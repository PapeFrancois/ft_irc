/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:16:31 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/07 10:42:12 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <string>

# include "ansiCodes.hpp"

class Client
{
	private:
		std::string	nickname_;
		std::string	username_;
		const int	sockFd_;
		int			passOK_;
		int			auth_;

	public:
		Client();
		Client(const int& sockFd);
		Client(const Client& other);
		~Client();

		Client&	operator = (const Client& other);

		const std::string&	getNickname()	const;
		const std::string&	getUsername()	const;
		const int&			getSockFd()		const;
		const int&			getPassOK() 	const;
		const int&			getAuth()		const;
		
		void				setPassOK(const int& status);
		void				setNickname(const std::string& newNickname);
		void				setUsername(const std::string& newUsername);
		void				setAuth(const int& status);
};

#endif
