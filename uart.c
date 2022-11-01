#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>	 // usado para UART
#include <fcntl.h>	 // usado para UART
#include <termios.h>	 // usado para UART


	int sensor=0; // armazena a opção do sensor selecionado pelo usuário
	int comando=0; // armazena a opção de comando selecionado pelo usuário
 	unsigned char comandoResposta[9]; // armazena o comando de resposta lido pelo rx

	char situacao[]="0x03";   // solicitação de situação atual do sensor
	char analogico[]="0x04"; // solicitação do valor da entrada analógica
	char digital[]="0x05";	  // solicitação do valor de uma das entradas digitais
	char led_nodeMCU[]="0x06";	// acende o led da NodeMCU

// abertura do arquivo da UART
int open_file(){
	int uart_filestream = -1;
	uart_filestream = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY);	// abre em modo escrita/leitura bloqueado
	if (uart_filestream == -1){
		return uart_filestream;
	}
	return 0;
}

// fecha a conexao com a UART
void close_connection(int uart_filestream){
	close(uart_filestream); 
	return 0;
}

// envia os dados na UART
int uart_tx(int tx_code, int uart_filestream){
	char* tx_string;

	switch (tx_code){
		case 1:
			tx_string = situacao;
		break;
		case 2:
			tx_string = analogico;
		break;
		case 3:
			tx_string = digital;
		break;
		case 4:
			tx_string = led_nodeMCU;
		break;

	if (uart_filestream != -1){// se abriu o arquivo da UART
		write(uart_filestream, tx_string, strlen(tx_string)); // filestream, mensagem enviada, tamanho da mensagem
	}	
	else{
		return uart_filestream;
	}
	return 0;
}

// recebe os dados na UART
char * uart_rx(int uart_filestream){
	char dado[9];
	int rx_length, aux = 0;
	
	if (uart_filestream != -1){
		while(aux < 8){
			rx_length = read(uart_filestream, (void*)response_command, 8); // filestream, buffer para armazenar, numero maximo de bytes lidos
			aux += rx_length;
			strcat(dado, response_command);
		}
		
			strcpy(response_command, dado);
		
		if (rx_length != 0){
			response_command[rx_length] = '\0';
			return response_command;	
		}
		return response_command;
		
	}

}
