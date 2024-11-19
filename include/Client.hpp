/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:16:31 by hepompid          #+#    #+#             */
/*   Updated: 2024/11/18 19:23:55 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <string>

class Client
{
	private:
		std::string			nick_;
		const std::string	user_;
		const int			sockFd_;

	public:
		Client();
		Client(std::string& nick, const std::string& user, const int& sockFd);
		Client(const Client& other);
		~Client();

		Client&	operator = (const Client& other);

		const std::string&	getNick() const;
		const std::string&	getUser() const;
		const int&			getSockFd() const;
};

#endif
