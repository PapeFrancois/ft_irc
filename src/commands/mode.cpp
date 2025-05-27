/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:46:08 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/27 14:31:23 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

static std::string extractChannelName(std::string& params)
{
	int	spacePos;

	spacePos = params.find(" ");
	
	if (spacePos == -1)
		return params;
	else
		return params.substr(0, spacePos);
}

std::string extractMode(std::string& params)
{
	int	spacePos;

	spacePos = params.find(" ");
	
	if (spacePos == -1)
		return "";
		
	for (int i = spacePos; params[i]; i++)
	{
		if (params[i] != ' ')
			return params.substr(i, params.length() - i);
	}
	return "";
}

bool	kIsBeforeL(std::string& modeLetters)
{
	bool	l;

	l = 0;
	for (int i = 0; modeLetters[i]; i++)
	{
		if (modeLetters[i] == 'l')
			l = 1;
		else if (modeLetters[i] == 'k' && l == 1)
			return false;
		else if (modeLetters[i] == 'k' && l == 0)
			return true;
	}
	if (l == 1)
		return false;
	return true;
}

std::vector<std::string> getModeParams(std::string& mode)
{
	std::vector<std::string>	modeParams;
	size_t							start;
    

	for (size_t i = 0; i < mode.length(); i++)
	{
		while (i < mode.length() && mode[i] == ' ')
			i++;

		start = i;
		while (i < mode.length() && mode[i] != ' ')
			i++;
		if (start < i)
			modeParams.push_back(mode.substr(start, i - start));
	}

    return modeParams;
}

std::string getKeyArg(std::vector<std::string>& modeParams)
{
	std::string	key;
	
	if (kIsBeforeL(modeParams.at(0)) && modeParams.size() >= 2)
			key = modeParams.at(1);
		else if (!kIsBeforeL(modeParams.at(0)) && modeParams.size() >= 3)
			key = modeParams.at(2);
	return key;
}

std::string	getLimitArg(std::vector<std::string>& modeParams)
{
	std::string	limitOfMembers;

	if (!kIsBeforeL(modeParams.at(0)) && modeParams.size() >= 2)
		limitOfMembers = modeParams.at(1);
	else if (kIsBeforeL(modeParams.at(0)) && modeParams.size() >= 3)
		limitOfMembers = modeParams.at(2);
	return limitOfMembers;
}

void iModeManager(Channel& channel, char& sign)
{
	if (sign == '+')
		channel.setIMode(1);
	else
	{
		channel.clearInvitedUsers();
		channel.setIMode(0);
	}
}

void tModeManager(Channel& channel, char& sign)
{
	if (sign == '+')
		channel.setTMode(1);
	else
		channel.setTMode(0);
}

void kModeManager(Channel& channel, char& sign, std::string& key)
{
	if (sign == '+')
	{
		channel.setKey(key);
		
	}
	else
		channel.setKey("");
}

void lModeManager(Channel& channel, char& sign, std::string& limitOfMembersStr)
{
	int	limitOfMembersInt;

	std::istringstream	iss(limitOfMembersStr);

	iss >> limitOfMembersInt;

	if (iss.fail())
		return;
	
	if (sign == '+')
		channel.setLimitOfMembers(limitOfMembersInt);
	else
		channel.setLimitOfMembers(0);
}

void Server::mode(Client& client, std::string& params)
{
	std::string					channelName;
	std::string					mode;
	std::string					modeList;
	std::string					modeListSuffix;
	std::vector<std::string>	modeParams;
	std::string					modeLetters;
	std::string					key;
	std::string					limitOfMembers;
	std::vector<int>			membersFd;

	if (params == "")
	{
		this->replies_.push_back(setReply(ERR_NEEDMOREPARAMS(SERVER_NAME, client.getNickname(), "MODE"), STATUS_OK, client.getSockFd()));
		return;
	}

	channelName = extractChannelName(params);
	mode = extractMode(params);

	std::cout << PURPLE_BG << "channel name = " << channelName << RESET << std::endl;
	std::cout << PURPLE_BG << "mode = " << mode << RESET << std::endl;	
	
	// soit si le channel n'existe pas, soit si c'est un mode user
	if (this->channels_.find(channelName) == this->channels_.end())
		return;


	// donne les modes du channel
	if (mode == "")
	{
		modeList = "+";
		if (this->channels_[channelName].getIMode())
			modeList += "i";
		if (this->channels_[channelName].getTMode())
			modeList += "t";
		if (this->channels_[channelName].getKey() != "")
			modeList += "k";
		if (this->channels_[channelName].getLimitOfMembers() != 0)
			modeList += "l";
		modeList += " ";
		if (this->channels_[channelName].getKey() != "")
			modeList += this->channels_[channelName].getKey();
		if (this->channels_[channelName].getLimitOfMembers() != 0)
		{
			modeList += " ";
			modeList += this->channels_[channelName].getLimitOfMembers();
		}
		this->replies_.push_back(setReply(RPL_CHANNELMODEIS(SERVER_NAME, client.getNickname(), channelName, modeList), STATUS_OK, client.getSockFd()));
		return;
	}


	
	// dans le cas ou les modes sont modifies
	
	if (!this->channels_[channelName].isOper(&client))
	{
		this->replies_.push_back(setReply(ERR_CHANOPRIVSNEEDED(SERVER_NAME, client.getNickname(), channelName), STATUS_OK, client.getSockFd()));
		return;
	}

	
	modeParams = getModeParams(mode);
	key = getKeyArg(modeParams);
	limitOfMembers = getLimitArg(modeParams);
	
	std::cout << PURPLE_BG << "modeParams = " << RESET << std::endl;	
	for (std::vector<std::string>::iterator it = modeParams.begin(); it != modeParams.end(); it++)
		std::cout << *it << std::endl;

	if (mode[0] == '+')
		modeList = '+';
	else if (mode[0] == '-')
		modeList = '-';
	else
		return;
	
	modeLetters = modeParams.at(0);
	std::cout << "mode letters = " << modeLetters << std::endl;
	if (modeLetters.find('i') != std::string::npos)
	{
		iModeManager(this->channels_[channelName], mode[0]);
		modeList += 'i';
	}
	if (modeLetters.find('t') != std::string::npos)
	{
		tModeManager(this->channels_[channelName], mode[0]);
		modeList += 't';
	}
	if (modeLetters.find('k') != std::string::npos)
	{
		kModeManager(this->channels_[channelName], mode[0], key);
		modeList += 'k';
		modeListSuffix += key;
	}
	if (modeLetters.find('l') != std::string::npos)
	{
		lModeManager(this->channels_[channelName], mode[0], limitOfMembers);
		modeList += 'l';
		modeListSuffix += limitOfMembers;
	}

	if (modeListSuffix != "")
	{
		modeList += " ";
		modeList += modeListSuffix;
	}

	membersFd = this->channels_[channelName].getMembersFd();
	
	for (std::vector<int>::iterator it = membersFd.begin(); it != membersFd.end(); it++)
	{
		this->replies_.push_back(setReply(MODE_MSG(client.getNickname(), client.getUsername(), SERVER_HOST, channelName, modeList), STATUS_OK, *it));
		
	}
	

	// for (int i = 0; mode[i]; i++)
	// {
	// 	if (mode[i] == ' ')
	// 		break;
	// 	if (mode[i] == 'i')
	// 	{
	// 		iModeManager(this->channels_[channelName], mode[0]);
	// 		modeList += 'i';
	// 	}
	// 	else if (mode[i] == 't')
	// 	{
	// 		tModeManager(this->channels_[channelName], mode[0]);
	// 		modeList += 't';
	// 	}
	// 	else if (mode[i] ==  'k')
	// 	{
	// 		kModeManager(this->channels_[channelName], mode[0], modeParams);
	// 		modeList += 'k';
	// 	}
	// 	else if (mode[i] == 'l')
	// 	{
	// 		lModeManager(this->channels_[channelName], mode[0], modeParams);
	// 		modeList += 'l';
	// 	}
	// }
	
	
}
