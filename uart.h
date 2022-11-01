#ifndef UART_H_INCLUDED
#define UART_H_INCLUDED

int open_file();
void close_conection(int uart_filestream);
int uart_tx(int tx_code, int uart_filestream);
char * uart_rx(int uart_filestream);

#endif // UART_H_INCLUDED