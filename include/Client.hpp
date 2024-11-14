
#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>

class Client
{
	private:
		std::string nick_;
		std::string	user_;

	public:
		Client();
		Client(const Client& other);
		~Client();

		Client&	operator = (const Client& other);
};

#endif