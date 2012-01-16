#ifndef INCLUDE_IREMOCON_CLIENT_HPP
#define INCLUDE_IREMOCON_CLIENT_HPP

#include <string>
#include <boost/asio.hpp>

class iRemoconClient
{
private:
	const boost::asio::ip::tcp::endpoint ep_;
public:
	iRemoconClient(const std::string& ip, const int port);
	bool exec_command(const std::string& cmd);
	bool ir_send(const int num);
	bool ir_recieve(const int num);
};

#endif // INCLUDE_IREMOCON_CLIENT_HPP
