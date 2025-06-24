import socket
import json
import threading
import sys

# Configurações do servidor
SERVER_IP = "127.0.0.1" 
PORT = 8080

def receive_messages(sock):
    """
    Função para receber mensagens do servidor em uma thread separada.
    """
    while True:
        try:
            data = sock.recv(4096).decode('utf-8')
            if not data:
                print("\nServidor desconectado.")
                break
            
            try:
                received_json = json.loads(data)
                if "username" in received_json and "message" in received_json:
                    print(f"\n[{received_json['username']}]: {received_json['message']}")
                else:
                    print(f"\n[Servidor]: {data}")
            except json.JSONDecodeError:
                print(f"\n[Servidor]: {data}")
            
            sys.stdout.write("> ")
            sys.stdout.flush()

        except ConnectionResetError:
            print("\nConexão com o servidor foi redefinida.")
            break
        except Exception as e:
            print(f"\nErro ao receber dados: {e}")
            break

def main():
    if len(sys.argv) != 2:
        print(f"Uso: python {sys.argv[0]} <username>")
        return

    username = sys.argv[1]
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        client_socket.connect((SERVER_IP, PORT))
        print(f"Conectado ao servidor de chat como {username}!")
        print("Digite 'exit' para sair.")
    except ConnectionRefusedError:
        print(f"Erro: Conexão recusada. Verifique se o servidor está rodando em {SERVER_IP}:{PORT}")
        return
    except Exception as e:
        print(f"Erro ao conectar: {e}")
        return

    receive_thread = threading.Thread(target=receive_messages, args=(client_socket,))
    receive_thread.daemon = True
    receive_thread.start()

    while True:
        message_content = input("> ")

        if message_content.lower() == 'exit':
            exit_message = {
                "username": username,
                "message": "exit"
            }
            client_socket.send(json.dumps(exit_message).encode('utf-8'))
            print("Desconectando...")
            break
        
        chat_message = {
            "username": username,
            "message": message_content
        }
        
        try:
            client_socket.send(json.dumps(chat_message).encode('utf-8'))
        except BrokenPipeError:
            print("Erro: A conexão foi quebrada. O servidor pode ter sido desconectado.")
            break
        except Exception as e:
            print(f"Erro ao enviar mensagem: {e}")
            break

    client_socket.close()
    print("Cliente encerrado.")

if __name__ == "__main__":
    main()