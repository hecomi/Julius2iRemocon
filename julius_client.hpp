#ifndef INCLUDE_JULIUSCLIENT_HPP
#define INCLUDE_JULIUSCLIENT_HPP

#include <map>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include "interpreter.hpp"
#include "iremocon_client.hpp"

class JuliusClient {
private:
	boost::asio::ip::tcp::endpoint ep_;
	std::map<std::string, boost::function<void()>> commands_;
public:
	JuliusClient(const std::string& ip, const int port);
	void connect(Interpreter& ip, iRemoconClient& ir);
};

#endif // INCLUDE_JULIUSCLIENT_HPP
