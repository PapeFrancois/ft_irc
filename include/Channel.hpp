/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepompid <hepompid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:20:07 by hepompid          #+#    #+#             */
/*   Updated: 2025/04/29 17:29:15 by hepompid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>

# include "ansiCodes.hpp"

class Channel
{
	private:
		std::string name_;
		std::string topic_;
		bool		iMode_;
		bool		tMode_;
		bool		kMode_;
		bool		oMode_;
		bool		lMode_;
		
	public:
		Channel();
		Channel(const Channel &other);
		~Channel();

		Channel& operator = (const Channel& other);

		const std::string&	getName() const;
		const std::string&	getTopic() const;
		const bool&			getiMode() const;
		const bool&			gettMode() const;
		const bool&			getkMode() const;
		const bool&			getoMode() const;
		const bool&			getlMode() const;

		
};

#endif
