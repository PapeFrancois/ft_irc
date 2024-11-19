/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:06:33 by hepompid          #+#    #+#             */
/*   Updated: 2024/11/19 19:10:37 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

int parsePort(char *arg)
{
	std::string	port = arg;
	
	for (size_t i = 0; i < port.length(); i++)
	{
		if (!std::isdigit(port[i]))
			throw NotNumber();
	}

	if (port.length() > 5)
		throw NumberTooBig();

	return std::atoi(arg);
}

int main(int argc, char** argv)
{
	int port;
	
	if (argc != 3)
	{
		std::cerr << RED << "Error: This program expects 2 arguments" << RESET << std::endl;
		return 1;
	}

	try
	{
		port = parsePort(argv[1]);
	}
	catch (std::exception& e)
	{
		std::cerr << RED << "Error: " << e.what() << RESET << std::endl;
		return 2;
	}
	
	Server server(port, argv[2]);

	// std::cout << server.getPort() << std::endl << server.getPassword() << std::endl;

	try
	{
		server.launchServer();
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << "Error: " << e.what() << RESET << std::endl;
		return 3;
	}

	return 0;
}
