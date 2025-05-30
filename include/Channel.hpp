/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:20:07 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/30 16:04:48 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include <vector>

# include "ansiCodes.hpp"
# include "Client.hpp"

class Channel
{
	private:
		const std::string 		name_;
		std::string 			topic_;
		std::string				key_;
		int						numberOfMembers_;
		int						limitOfMembers_;
		
		std::vector<Client*>	members_;
		std::vector<Client*>	operators_;
		std::vector<Client*>	invitedUsers_;
		
		bool						iMode_;
		bool						tMode_;
		
	public:
		Channel();
		Channel(const std::string& name, Client* creator);
		Channel(const Channel &other);
		~Channel();

		Channel& operator = (const Channel& other);

		const std::string&	getName() const;
		const std::string&	getTopic() const;
		const int&			getNumberOfMembers() const;
		const int&			getLimitOfMembers() const;
		const std::string&	getKey() const;
		const bool&			getIMode() const;
		const bool&			getTMode() const;

		void				setTopic(const std::string& newTopic);
		void				setKey(const std::string& newKey);
		void				setLimitOfMembers(const int& newLimitOfUsers);
		void				setIMode(const bool& newIMode);
		void				setTMode(const bool& newTMode);
		
		void				printMembers() const;
		void				printOperators() const;
		void				printInvitedUsers() const;
		
		void				addMember(Client* user);
		void				removeMember(Client* user);
		void				addOperator(Client* user);
		void				removeOperator(Client* user);
		void				addInvitedUser(Client* user);
		void				removeInvitedUser(Client* user);
		void				clearInvitedUsers();
		
		bool				userIsInvited(Client* user) const;
		std::vector<int>	getMembersFd() const;
		std::string			getMembersNickList() const;
		bool				isOper(Client* user) const;
		bool				isMember(Client *user) const;
};

#endif
