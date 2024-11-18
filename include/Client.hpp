/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:16:31 by hepompid          #+#    #+#             */
/*   Updated: 2024/11/18 16:56:51 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <string>

class Client
{
	private:
		std::string	nick_;
		std::string	user_;
		const int	sockFd_;

	public:
		Client();
		Client(const Client& other);
		~Client();

		Client&	operator = (const Client& other);

		std::string&	getNick();
		std::string&	getUser();
		const int&		getSockFd();
};

#endif
