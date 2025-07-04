#pragma once

#include <string>

/*
    Arquivo: Config.h

    Descrição:
    Este arquivo contém declarações de constantes globais utilizadas para
    configurar e padronizar a conexão entre clientes e servidores OPC DA (OLE for Process Control).

    Este arquivo também contém declarações de constantes globais utilizadas para
    configurar e padronizar a conexão entre clientes e servidores TCP/IP.

    Objetivo:
    Centralizar e unificar configurações comuns de conexão, garantindo consistência
    e facilitando a manutenção da aplicação.
*/

//  ProgID do servidor OPC DA a ser conectado
#define OPC_SERVER_PROG_ID "Matrikon.OPC.Simulation.1";

// Request Update Rate - Taxa de atualização das variáveis de processo pelo Servidor OPC DA (em milisegundos)
#define OPC_SERVER_REQ_UPDATE_RATE 5000;

//  Porta TCP que será disponibilizada pelo servidor TCP
#define TCP_PORT 4885;