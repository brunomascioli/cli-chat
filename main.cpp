#include "server.h"

/*
socket() 
	- chama a syscall socket() no kernel.
	- o kernel reserva recursos e cria uma estrutura socket 
	no espaço de kernel, associada ao processo.
	- retorna um file descriptor, como se fosse um arquivo normal
	- Com SOCK_STREAM, o kernel usa o protocolo TCP
	(implementado no driver de rede do sistema operacional)


bind()
	- Associa o socket a um endereço IP e porta específicos
	- O kernel liga o socket criado a uma porta local na tabela de sockets.
	- Essa ligação é registrada na tabela de escuta do kernel.
	- Verifica se a porta está disponível (caso contrário, falha com EADDRINUSE).
	- Permite que o SO saiba "qual processo está responsável pela porta 8080"

listen()
	- Coloca o socket em modo passivo, pronto para aceitar conexões
	- O socket passa para o estado LISTEN da máquina de estados TCP
	- O kernel escuta pacotes SYN (início do handshake TCP) e inicia o processo
	de three-way handshake

accept()
	- Aceita uma conexão pendente da fila e retorna um novo socket
	- Quando um cliente conecta, o kernel faz o handshake TCP 
	(SYN -> SYN-ACK -> ACK).
	- Se a conexão for bem-sucedida, accep() cria um novo socket
	(descritor separado)
	- Esse novo socket está ligado exclusivamente a esse cliente.
	- o `server_fd` original continua escutando por outras conexões

read() 
	- Lê dados enviados pelo cliente através do socket. 
	- O kernel lê os dados da pilha TCP, armazenados no buffer do socket.
	- Bloqueia (por padrão) até os dados estarem disponíveis
	- Copia os dados do espaço de kernel para o espaço do processo
	(buffer fornecido)

send()
	- Envia dados ao cliente através do socket
	- Copia os dados para o buffer de envio do kernel
	- A pilha TCP fragmenta, embala e envia os pacotes
	- Pode ser enviado imediatamente, ou acumulado para envio otimizado
	- O SO cuida da retransmissão e controle de congestionamento automaticamente.

recv()


close()
	- Fecha o socket e libera os recursos
	- Envia o pacote TCP FIN para o cliente, iniciando o encerramento da conexão TCP
	- Marca o socket como fechado na tabela do kernel
	- Remove os buffers, libera memória, e encerra o descritor no processo

* getaddrinfo()
 * 
 * */

int main() {
	Server* s = new Server();
	if(s->init(8080) == -1){
		perror("Erro ao iniciar servidor na porta ");
		delete s;	
	}
	Connection* conn;
	while (true) {
		conn = s->accept_connection();
		conn->read();
	}
	
}
