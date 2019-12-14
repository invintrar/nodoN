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
uint8_t rx_addr[5], tx_addr[5];
uint8_t nrfDataRx[8], nrfDataTx[8];
uint8_t uSDState, bWriteuSD;
uint8_t fInt1;
uint8_t bNrf, mutex, bInicioBloque, bAdc;
ds3234_data_time rtc;
ds3234_time rtcTime;
uint32_t sector;
uint16_t vADC;
uint16_t i;
uint8_t j;
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

    //Setup  RF24L01
    RF24L01_setup(tx_addr, rx_addr, 12);

    //Turn on ADXL255
    //ADXL355_Write_Byte(POWER_CTL, MEASURING);
    //__delay_ms(250);

    //DS3234_setTime(rtc);

    // Start measuring
    //ADC1_SamplingStart();
    //ADC1_SamplingStop();


    // Loop Infinite
    while (1) {

        /*
        if (fInt1 == 1) {
            if (bInicioBloque == 0) {
                //0.8us
                //DS3234_Time(&rtcTime);
                bufferE[0] = 0x48;
                bufferE[1] = rtcTime.hours;
                bufferE[2] = rtcTime.minutes;
                bufferE[3] = rtcTime.seconds;
                bufferE[4] = vADC;
                bufferE[5] = vADC >> 8;
                bufferE[6] = 0x48;
                bInicioBloque = 1;
                i = 7;
            }
            for (j = 0; j < 63; j++) {
                bufferE[i] = dataCBuffer[j];
                i++;
                if (i == 511) {
                    bufferE[i] = 0x48;
                    bWriteuSD = 1;
                    bInicioBloque = 0;
                }
            }
        }
        //110 us for write uSD
        if (uSDState == SUCCESSFUL_INIT && bWriteuSD == 1) {
            SD_Write_Block(bufferE, sector);
            bWriteuSD = 0;
            sector++;
        } else {
            uSDState = SD_Init();
        }
         */


        //Set Mode RX
        RF24L01_set_mode_RX();

        //Wait Interruption
        while (!mutex);

        if (mutex == 1) {
            RF24L01_read_payload(nrfDataRx, sizeof (nrfDataRx));
        }

        unsigned short delay = 0xFFF;
        while (delay--);

        // Start measuring
        ADC1_SamplingStart();
        ADC1_SamplingStop();


        rtc.seconds = nrfDataRx[0];
        rtc.minutes = nrfDataRx[1];
        rtc.hours = nrfDataRx[2];
        rtc.day = nrfDataRx[3];
        rtc.month = nrfDataRx[4];
        rtc.date = nrfDataRx[5];
        rtc.year = nrfDataRx[6];

        DS3234_setTime(rtc);

        /*
         * PREPARE THE RESPONSE
         */

        // Read RTC time
        DS3234_Time(&rtcTime);

        nrfDataTx[0] = 0x48;
        nrfDataTx[1] = rtcTime.seconds;
        nrfDataTx[2] = rtcTime.minutes;
        nrfDataTx[3] = rtcTime.hours;
        // Test data available
        while (!bAdc) {
            nrfDataTx[4] = vADC >> 8;
            nrfDataTx[5] = vADC;
            bAdc = 0;
        }
        nrfDataTx[6] = 0x48;
        nrfDataTx[7] = 0x48;

        
        mutex = 0;

        //Set Mode TX
        RF24L01_set_mode_TX();

        //Write Payload
        RF24L01_write_payload(nrfDataTx, sizeof (nrfDataTx));

        delay = 0xFFF;
        while (delay--);

    }
    return 0;
}

void initVariables() {
    fInt1 = 0;
    mutex = 0;
    bInicioBloque = 0;
    //Sector write uSD
    sector = 35000;
    bWriteuSD = 0;
    bAdc = 0;

    // Address NrF24L01 RX and TX
    for (i = 0; i < 5; i++) {
        //RX Address 
        rx_addr[i] = 0x78;
        //TX Address
        tx_addr[i] = 0x78;
    }

    for (i = 0; i < 8; i++) {
        nrfDataRx[i] = 0x00;
        nrfDataTx[i] = 0x00;
    }

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
