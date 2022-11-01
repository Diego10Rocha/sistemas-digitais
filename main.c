#include <stdio.h>
#include <stdbool.h>
#include "uart.h"

void main(){
    int tx_code;
    int uart_filestream;
    
    int uart_filestream = open_file();
    if (uart_filestream == -1){
        printf("\nErro: não é posssivel abrir o arquivo da UART.\n");
    }

    while (true){
        tx_code = 0;

        while (true){   // menu de opções para transmissão de dados da uart
            printf("Escolha uma opção:\n");
            printf("1 - Solicitar a situação atual do sensor\n");
            printf("2 - Solicitar o valor da entrada analógica\n");
            printf("3 - Solicitar o valor de uma das entradas digitais\n");
            printf("4 - Acender o led da NodeMCU\n");
            printf("5 - Finalizar programa\n");

            scanf("%i", &tx_code);

            if (tx_code < 1 || tx_code > 4){
                printf("Digite um valor válido.");
            }
            else if (tx_code == 5){
            	break;
            }
            else{
            	uart_filestream = uart_tx(tx_code,  uart_filestream);
        	
        	if (uart_filestream == -1){
			printf("\nErro: não é possível enviar a mensagem.\n");
		}
		else{
			printf("\nRequisicao sendo enviada. Aguarde uns instantes.\n"); 
            		break;
            	}
            }
        }
        
        while (true){   // menu de opções para recebimento de dados da uart
        	if (uart_filestream == -1){
        		printf("\nFalha na abertura do arquivo");
        		break;
        	}
        
		char response_command = uart_rx(uart_filestream);
		
		int rx_length = strlen(response_command);
		
		if (rx_length < 0){
			printf("\nOcorreu um erro na leitura de dados\n");
		}
		else if (rx_length == 0){
			printf("\nNenhum dado lido\n");
		}
		else{
			//Byte recebido
			comandoResposta[rx_length] = '\0';
			printf("\nDado recebido: %s \n", comandoResposta);
			break;
		}
		
		printf("\nDeseja continuar requisitando uma resposta?\n");
		printf("s -> sim ou n -> não\n");
		
		scanf("%c", stop_request);
		
		if (stop_request == "s"){
			break;
		}
	}
	
	printf("\nFinalizar o programa?");
	printf("s -> sim ou n -> não\n");
		
	scanf("%c", stop_request);
	
	if (stop_request == "s"){
		break;
	}
	     
        
    }

}
