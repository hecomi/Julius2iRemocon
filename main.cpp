#include "interpreter.hpp"
#include "julius_client.hpp"

int main(int argc, char const* argv[])
{
	iRemoconClient ir("192.168.0.3", 51013);
	Interpreter ip;

	if (!ip.learn_commands_from_xml("xml/commands.xml")) {
		std::cerr << "Error: XML is invalid" << std::endl;
	}

	JuliusClient jc("192.168.0.10", 10500);
	jc.connect(ip, ir);

	return 0;
}
