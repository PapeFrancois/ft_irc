/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:16:31 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/26 09:37:43 by hepompid         ###   ########.fr       */
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
		int			sockFd_;
		int			passOK_;
		int			auth_;
		bool		isOper_;
		std::string	ipAddress_;

	public:
		Client();
		Client(const int& sockFd, const std::string& ipAddress);
		Client(const Client& other);
		~Client();

		Client&	operator = (const Client& other);

		const std::string&	getNickname()	const;
		const std::string&	getUsername()	const;
		const int&			getSockFd()		const;
		const int&			getPassOK() 	const;
		const int&			getAuth()		const;
		const bool&			getIsOper()		const;
		const std::string&	getIpAddress()	const;
		
		
		void				setPassOK(const int& status);
		void				setNickname(const std::string& newNickname);
		void				setUsername(const std::string& newUsername);
		void				setAuth(const int& status);
		void				setIsOper(const bool& isOper);
};

#endif
