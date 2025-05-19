#include "server.h"

using namespace CliChat;

int main() 
{
	Server* s = new Server();
	if(s->init(8080) == -1)
	{
		perror("Erro ao iniciar servidor na porta 8080");
		delete s;	
		exit(EXIT_FAILURE);
	}

	while (true) 
	{
		auto conn = s->accept_connection();
		if (!conn) 
		{
			std::cerr << "Erro: conexão inválida!" << std::endl;
			continue;
		}

		while (true)
		{
			auto request = conn->receive_data();

			if (!request) 
			{
				std::cerr << "Erro: request é null!" << std::endl;
				continue;
			}

			std::cout << request->get_username() << " : " << request->get_message() << std::endl; 
			
			conn->send_data(request->get_message());
		}		
	}

	delete s;
}
