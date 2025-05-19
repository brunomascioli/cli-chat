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
	delete s;
}
