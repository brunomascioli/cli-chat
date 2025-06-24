# CLI-Chat

> Um sistema de chat cliente-servidor, simples e funcional, via linha de comando.

Este projeto implementa um sistema de chat básico, permitindo a comunicação entre múltiplos usuários através de terminais. Ele é composto por um servidor em C++ e um cliente em Python, que se comunicam usando sockets TCP/IP e o formato de dados JSON.

## Sobre o Projeto

O CLI-Chat foi desenvolvido como uma demonstração prática de conceitos de programação de rede, multithreading e manipulação de dados JSON em um ambiente cliente-servidor.

## Funcionalidades Principais

### Servidor (C++)

  - **Gerenciamento de Conexões:** Utiliza *threads* para gerenciar múltiplas conexões de clientes simultaneamente.
  - **Recepção de Mensagens:** Recebe mensagens dos clientes conectados.
  - **Transmissão (Broadcast):** Retransmite as mensagens recebidas para todos os outros clientes.
  - **Processamento de Dados:** Analisa e processa mensagens no formato JSON.

### Cliente (Python)

  - **Conexão Simples:** Conecta-se facilmente ao servidor C++.
  - **Envio de Mensagens:** Permite que o usuário defina um nome e envie mensagens de texto.
  - **Visualização em Tempo Real:** Exibe as mensagens recebidas de outros usuários instantaneamente.
  - **Formato de Dados:** Utiliza JSON para formatar as mensagens antes de enviá-las.

## Como Usar

### Pré-requisitos
  * `make`
  * Um compilador C++ (como `g++`)
  * `python3`

### 1\. Compilar o Servidor (C++)

No diretório raiz do projeto, execute o seguinte comando para compilar o servidor:

```bash
make
```

Isso criará o executável dentro do diretório `build/`.

### 2\. Iniciar o Servidor

Após a compilação, inicie o servidor:

```bash
./build/app
```

O servidor começará a rodar e aguardará por conexões na porta `8080`.

### 3\. Iniciar os Clientes (Python)

Abra um novo terminal para cada cliente que você deseja conectar. Execute o script do cliente fornecendo um nome de usuário como argumento.

**Exemplo - Cliente 1 (Alice):**

```bash
python3 client.py Alice
```

Abra outro terminal.

**Exemplo - Cliente 2 (Bob):**

```bash
python3 client.py Bob
```

Agora, tudo que for digitado no terminal de Alice aparecerá no terminal de Bob, e vice-versa.

### 4\. Sair do Chat

Para desconectar um cliente, simplesmente digite `exit` no terminal e pressione `Enter`.

## Vídeo de demonstração
https://youtu.be/BXX7KJhYHyg