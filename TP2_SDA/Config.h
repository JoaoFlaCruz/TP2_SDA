#pragma once

#include <string>

/*
    Arquivo: Config.h

    Descri��o:
    Este arquivo cont�m declara��es de constantes globais utilizadas para
    configurar e padronizar a conex�o entre clientes e servidores OPC DA (OLE for Process Control).

    Este arquivo tamb�m cont�m declara��es de constantes globais utilizadas para
    configurar e padronizar a conex�o entre clientes e servidores TCP/IP.

    Objetivo:
    Centralizar e unificar configura��es comuns de conex�o, garantindo consist�ncia
    e facilitando a manuten��o da aplica��o.
*/

//  ProgID do servidor OPC DA a ser conectado
#define OPC_SERVER_PROG_ID "Matrikon.OPC.Simulation.1";

// Request Update Rate - Taxa de atualiza��o das vari�veis de processo pelo Servidor OPC DA (em milisegundos)
#define OPC_SERVER_REQ_UPDATE_RATE 5000;

//  Porta TCP que ser� disponibilizada pelo servidor TCP
#define TCP_PORT 4885;