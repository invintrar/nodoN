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

/*----------------------------------------------------------------------------
 VARIABLE GLOBALES
 -----------------------------------------------------------------------------*/
uint8_t bufferE[512];
uint8_t bufferR[512];
uint8_t banderInt1, j;
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
void initVariables(void);

/*============================================================================
 FUNCTION MAIN
 =============================================================================*/
int main(void) {
    // Set Variables
    initVariables();

    SYSTEM_Initialize();
    __delay_ms(250);

    //Configuramos  RF24L01
    //RF24L01_setup(tx_addr, rx_addr, 12);

    /*Encendemos el ADXL255*/
    //ADXL355_Write_Byte(POWER_CTL, MEASURING);
    //__delay_ms(250);

    //DS3234_setTime(rtc);

    // Start measuring
    //ADC1_SamplingStart();
    //ADC1_SamplingStop();


    // Loop Infinite
    while (1) {
        //__delay_ms(1000);

        //DS3234_Time(&rtcTime);

        /*
        //It Check that the uSD stay connected
        SD_Check();

        if (sdF.detected) {
            // It Check that It was initialized
            if (!sdF.init_ok) {
                //Initialize uSD
                if (SD_Init() == SUCCESSFUL_INIT) {
                    sdF.init_ok = 1;
                    SD_Led_On();
                }
            }
            SD_Write_Block(bufferE, sector);
            sector++;
        } else {
            SD_Led_Off();
        }
         */


        /*
        //Set Mode RX
        RF24L01_set_mode_RX();

        //Wait interrupt
        while (!mutex);
        if (mutex == 1) {
            unsigned char recv_data[32];
            RF24L01_read_payload(recv_data, sizeof (recv_data));
            received = *((data_received *) & recv_data);

            asm("nop"); //Place a breakpoint here to see memmory

        } else {
            //Something happened
            to_send.resp = 0;
        }
        unsigned short delay = 0xFFF;
        while (delay--);
         */

        /*
         * PREPARE THE RESPONSE
         */


        /*
        //Prepare the buffer to send from the data_to_send structure
        unsigned char buffer_to_send[32];
        for (i = 0; i < 32; i++) {
            buffer_to_send[i] = 0xAA;
        }


        *((data_to_sent *) & buffer_to_send) = to_send;

        mutex = 0;

        //Set Mode TX
        RF24L01_set_mode_TX();

        //Write Payload
        RF24L01_write_payload(buffer_to_send, sizeof (buffer_to_send));



        while (!mutex);
        if (mutex != 1) {
            //The transmission failed
        } else if (banderInt1 == 0) {
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
        }
         */

    }

    return 0;
}

void initVariables() {
    /* Direction RX*/
    //unsigned char rx_addr[5] = {0x78, 0x78, 0x78, 0x78, 0x78};
    //unsigned char tx_addr[5] = {0x78, 0x78, 0x78, 0x78, 0x78};

    //banderInt1 = 1;
    //banderCont = 0;
    //banderaSPI1 = 0;

    //uSD Flags
    sdF.detected = 0;
    sdF.init_ok = 0;
    sdF.saving = 0;

    //int i;
    //int continuar = 0;
    //sector = 2051;
    //sector = 34816;
    sector = 35000;
    mutex = 1;


    /* Initialization the variable of uSD to 0xAA*/
    for (i = 0; i < 512; i++) {
        bufferE[i] = 0x5A;
    }

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
}
