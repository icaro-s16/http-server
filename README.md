# Simple HTTP Server in C

## Descrição

Este projeto consiste em uma implementação minimalista de um servidor HTTP escrito em C puro. O objetivo do projeto era me desafiar diante de um projeto complexo e com uma base teórica grande. Estou extremamente feliz com o resultado e pretendo deixar o código mais robusto com o tempo!
Demonstração

Aqui está o servidor em ação, compilando e respondendo a requisições:

![Demonstração do Servidor Rodando](demo/2026-03-17 15-41-15.mp4)

## Funcionalidades

* Processamento básico de requisições GET.
* Serviço de arquivos estáticos.
* Log simples de requisições e respostas no terminal.

## Principais implementações
* Hash map criado do zero.
* Estrutura Bytes para lidar com os blocos de bytes recebidos e enviados pelo servidor.
* Multithreading, criando a dinâmica de uma thread controladora e três threads empregadas que lidam com as requisições.

## Pré-requisitos
* CMake (versão 3.10 ou superior)
* Ambiente baseado em Unix/Linux

**OBS:** É necessário o uso de Linux, pois o projeto utiliza apenas as APIs POSIX; não há portabilidade para as APIs do Windows.

## Como Compilar

**Siga os passos abaixo para compilar o projeto:**

* Clone o repositório:
```Bash
git clone https://github.com/icaro-s16/http-server.git
cd http-server
```

* Crie um diretório de build e navegue para ele:
```Bash
mkdir build
cd build
```

* Gere os arquivos de build com o CMake:
```Bash
cmake ..
```

* Compile o projeto:
```Bash
cmake --build .
```

## Observações

O conteúdo acessível pelo navegador deve estar presente na mesma pasta que o seu executável. Portanto, se você for manter o executável na pasta build, crie o diretório public_http e adicione o conteúdo que você deseja!

## Contribuições

Se você encontrar qualquer erro, fique à vontade para abrir issues ou enviar um pull request!