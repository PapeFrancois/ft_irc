/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:20:07 by hepompid          #+#    #+#             */
/*   Updated: 2025/05/07 10:17:51 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include <vector>

# include "ansiCodes.hpp"

class Channel
{
	private:
		const std::string 			name_;
		std::string 				topic_;
		std::string					key_;
		int							limitOfUsers_;
		
		std::vector<std::string>	members_; 		// nick des members
		std::vector<std::string>	operators_;		// nick des operators
		std::vector<std::string>	invitedUsers_;	// nick des users
		
		bool						iMode_; // 0
		bool						tMode_; // 0
		
	public:
		Channel();
		Channel(const Channel &other);
		~Channel();

		Channel& operator = (const Channel& other);

		const std::string&	getName() const;
		const std::string&	getTopic() const;
		const std::string&	getKey() const;
		const int&			getLimitOfUsers() const;
		const bool&			getIMode() const;
		const bool&			getTMode() const;

		void				setTopic(const std::string& newTopic);
		void				setKey(const std::string& newKey);
		void				setLimitOfUsers(const std::string& newLimitOfUsers);
		void				setIMode(const bool iMode);
		void				setTMode(const bool TMode);

		void				printMembers() const;
		void				printOperators() const;
		void				printInvitedUsers() const;

		void				addMember(const std::string& userNickname);
		void				removeMember(const std::string& userNickname);
		void				addOperator(const std::string& userNickname);
		void				removeOperator(const std::string& userNickname);
		void				addInvitedUser(const std::string& userNickname);
		void				removeInvitedUser(const std::string& userNickname);

		

		
};

#endif
