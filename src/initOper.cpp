/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initOper.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:00:59 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/25 18:08:34 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::string getWord(std::string& line, int *end)
{
	int	start;
	
	while (line[*end] && line[*end] == ' ')
		(*end)++;
	if (!line[*end])
		return "";
			
	start = *end;
	while (line[*end] && line[*end] != ' ')
		(*end)++;
		
	return line.substr(start, *end - start);
}

void Server::initOperList()
{
	std::ifstream	file;
	std::string		line;
	std::string		name;
	std::string		password;
	std::string		host;
	int				i;

	file.open("ircd.conf");
	if (file.fail())
		throw OpenFailed();
		
	while (std::getline(file, line))
	{	
		if (line == "")
			continue;
		
		i = 0;
		
		name = getWord(line, &i);
		if (name == "")
			continue;
			
		password = getWord(line, &i);
		if (password == "")
			continue;

		host = getWord(line, &i);
		if (host == "")
			continue;

		this->serverOperators_.push_back(setServerOperator(name, password, host));
	}
}