/*
 * File:   main.c
 * Author: Darwin
 *
 * Created on June 26, 2019, 12:15 AM
 */

/*----------------------------------------------------------------------------
 HEADER FILES
 -----------------------------------------------------------------------------*/
#include "main.h"
#include "ds3234.h"
#include <stdio.h>

/*----------------------------------------------------------------------------
 VARIABLE GLOBALES
 -----------------------------------------------------------------------------*/
uint8_t bufferE[512];
uint8_t bufferR[512];
uint8_t banderInt1;
uint8_t banderaSPI1;
uint16_t banderCont;
ds3234_data_time rtc;
ds3234_time rtcTime;
uint32_t sector;

/*
 * VARIABLES EXTERN
 */
extern uint16_t vADC;
extern uint8_t bNrf;
uint16_t i;

uint8_t mutex;

uint8_t seconds;
uint8_t minutes;
uint8_t hours;
/*----------------------------------------------------------------------------
 FUNCTION PROTOTYPES
 -----------------------------------------------------------------------------*/

/*============================================================================
 FUNCTION MAIN
 =============================================================================*/
int main(void) {

    /* Direction RX*/
    //unsigned char rx_addr[5] = {0x78, 0x78, 0x78, 0x78, 0x78};
    //unsigned char tx_addr[5] = {0x78, 0x78, 0x78, 0x78, 0x78};
    /*
    banderInt1 = 1;
    banderCont = 0;
    banderaSPI1 = 0;
    sdF.detected = 0;
    sdF.init_ok = 0;
    sdF.saving = 0;
    int i;
    //int continuar = 0;
    //sector = 2051;
    //sector = 34816;
    mutex = 0;
     */

    SYSTEM_Initialize();
    __delay_ms(250);


    /* Incializamos la variable de la memoria a 0*/
    //for (i = 0; i < 512; i++) {
    //  bufferE[i] = 0xAA;
    //}

    //Configuramos  RF24L01
    //RF24L01_setup(tx_addr, rx_addr, 12);

    /*Encendemos el ADXL255*/
    //ADXL355_Write_Byte(POWER_CTL, MEASURING);
    //__delay_ms(250);

    //00-60 seconds
    rtc.seconds = 0;
    //00-60 minute
    rtc.minutes = 12;
    //00-24 hour
    rtc.hours = 17;
    //Sunday = 1, Monday = 2, ...
    rtc.day = 5;
    rtc.date = 12;
    rtc.month = 12;
    rtc.year = 19;

    DS3234_setTime(rtc);
    
    LATAbits.LATA1 = 0;

    // Bucle Infinito
    while (1) {
        __delay_ms(1000);
        
        // Start measuring
        //ADC1_SamplingStart();
        //ADC1_SamplingStop();
        DS3234_Time(&rtcTime);
        
        /*
        while(continuar < 511){
            bufferE[continuar] = (ADCValue & 0x00FF);
            bufferE[continuar+1] = (ADCValue >> 8);
            continuar += 2;
        }
         */

        /*Comprobamos que la microSD siga conectada*/

        //SD_Check();

        //if (sdF.detected) {
        /* Compromabos si esta inicializamos*/
        //  if (!sdF.init_ok) {
        /* Inicializamos microSD*/
        //    if (SD_Init() == SUCCESSFUL_INIT) {
        //      sdF.init_ok = 1;
        //    SD_Led_On();
        //}
        //}
        //SD_Write_Block(bufferE, sector);
        //sector++;
        //} else {
        //SD_Led_Off();
        //}


        /*Set Mode RX*/
        //RF24L01_set_mode_RX();

        /*Wait interrupt*/
        //while (!mutex);
        //if (mutex == 1) {
        //  unsigned char recv_data[32];
        //RF24L01_read_payload(recv_data, sizeof (recv_data));
        //received = *((data_received *) & recv_data);

        //asm("nop"); //Place a breakpoint here to see memmory

        //} else {
        //Something happened
        //  to_send.resp = 0;
        //}
        //unsigned short delay = 0xFFF;
        //while (delay--);

        /*
         * PREPARE THE RESPONSE
         */

        //Prepare the buffer to send from the data_to_send struct
        //unsigned char buffer_to_send[32];
        //for (i = 0; i < 32; i++) {
        //  buffer_to_send[i] = 0xAA;
        //}


        //*((data_to_sent *) & buffer_to_send) = to_send;

        //mutex = 0;

        /*Set Mode TX*/
        //RF24L01_set_mode_TX();

        /*Write Payload*/
        //RF24L01_write_payload(buffer_to_send, sizeof (buffer_to_send));

        //while (!mutex);
        //if (mutex != 1) {
        //The transmission failed
        //  LED_verde_setLow();
        //} else {
        //  LED_rojo_toggle();
        //}
        //__delay_ms(10);
        /*
                if (banderInt1 == 0) {
                    for (j = 0; j < 63; j++) {
                        bufferE[i] = dataCBuffer[j];
                        if (i < 512) {
                            i++;
                        } else {
                            if (sector > 975871)
                                break;
                            SD_Write_Block(bufferE, sector);
                            i = 0;
                            sector++;
                        }
                    }
                    banderInt1 = 1;
                }*/

    }

    return 0;
}
