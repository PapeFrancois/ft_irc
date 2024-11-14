
#include "Client.hpp"

Client::Client() {}

Client::Client(const Client& other)
{
	this->nick_ = other.nick_;
	this->user_ = other.user_;
}

Client::~Client() {}