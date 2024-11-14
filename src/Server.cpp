
#include "Server.hpp"

Server::Server() {}

Server::Server(const Server& other)
{
	this->clients_ = other.clients_;
}

Server::~Server() {}

int	Server::launchServer()
{

}
