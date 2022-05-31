#include <stdint.h>
#include "uart.h"
#include "gpio.h"

#define NRF_UART0_BASE_ADRESS 0x40002000
#define UART0 ((NRF_UART_REG*) NRF_UART0_BASE_ADRESS)

#define UART0_TX_PIN 5 //GPIO0
#define UART0_RX_PIN 6  //GPIO0

typedef struct
{
    volatile uint32_t TASKS_STARTRX;
    volatile uint32_t TASKS_STOPRX;
    volatile uint32_t TASKS_STARTTX;
    volatile uint32_t TASKS_STOPTX;
    volatile uint32_t RESERVED0[3];
    volatile uint32_t TASKS_SUSPEND;
    volatile uint32_t RESERVED1[56];
    volatile uint32_t EVENTS_CTS;
    volatile uint32_t EVENTS_NCTS;
    volatile uint32_t EVENTS_RXDRDY;
    volatile uint32_t RESERVED2[4];
    volatile uint32_t EVENTS_TXDRDY;
    volatile uint32_t RESERVED3[1];
    volatile uint32_t EVENTS_ERROR;
    volatile uint32_t RESERVED4[7];
    volatile uint32_t EVENTS_RXTO;
    volatile uint32_t RESERVED5[46];
    volatile uint32_t SHORTS;
    volatile uint32_t RESERVED6[64];
    volatile uint32_t INTENSET;
    volatile uint32_t INTENCLR;
    volatile uint32_t RESERVED7[93];
    volatile uint32_t ERRORSRC;
    volatile uint32_t RESERVED8[31];
    volatile uint32_t ENABLE;
    volatile uint32_t RESERVED9[1];
    volatile uint32_t PSEL_RTS;
    volatile uint32_t PSEL_TXD;
    volatile uint32_t PSEL_CTS;
    volatile uint32_t PSEL_RXD;
    volatile uint32_t RXD;
    volatile uint32_t TXD;
    volatile uint32_t RESERVED10[1];
    volatile uint32_t BAUDRATE;
    volatile uint32_t RESERVED11[17];
    volatile uint32_t CONFIG;
    
} NRF_UART_REG;

void uart_init(){
    //GPIO dirset
    GPIO0->PIN_CNF[UART0_TX_PIN] = 0; // Output
    GPIO0->PIN_CNF[UART0_RX_PIN] = 1; // Input

    //Config UART pins
    UART0->PSEL_TXD = (UART0_TX_PIN | (1 << 5) | (1 << 31));
    UART0->PSEL_RXD = (UART0_TX_PIN | (1 << 5) | (1 << 31));

    //No flow control
    UART0->PSEL_CTS = 0xFFFFFFFF; //Disable
    UART0->PSEL_RTS = 0xFFFFFFFF; //Disable
    UART0->BAUDRATE = 0x00275000; //9600

    //Enable
    UART0->ENABLE = 4;
    //UART0->CONFIG = 0b10000; //2 stop bits
    UART0->TASKS_STARTRX = 1;    
}

void uart_send(char letter){
    
}