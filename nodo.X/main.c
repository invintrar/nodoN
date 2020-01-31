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


/*----------------------------------------------------------------------------
 VARIABLE GLOBALES
 -----------------------------------------------------------------------------*/
uint8_t bufferE[512];
uint8_t bufferR[512];
uint8_t dataAdxl[63];
uint8_t rx_addr[5], tx_addr[5];
uint8_t nrfDataRx[8], nrfDataTx[8];
uint8_t uSDState, bWriteuSD;
uint8_t bExInt1, bNrf, bData, bInicioBloque, bMrx;
ds3234_data_time rtc;
ds3234_time rtcTime;
uint32_t sector;
uint16_t vAdc;
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
    RF24L01_setup(tx_addr, rx_addr, 22);

    //Turn on ADXL255
    //ADXL355_Write_Byte(POWER_CTL, MEASURING);
    //__delay_ms(250);

    DS3234_setTime(rtc);

    // Start measuring
    ADC1_SamplingStart();
    ADC1_SamplingStop();

    //Set Mode RX
    //RF24L01_set_mode_RX();

    // Loop Infinite
    while (1) {
        Led_verde_toggle();
        __delay_ms(250);


        switch (bNrf) {
            case 1://Data Ready
                if (bMrx == 1) {
                    bNrf = 0;
                    bMrx = 0;
                    RF24L01_set_mode_RX();
                } else {
                    bNrf = 3;
                    rtc.seconds = nrfDataRx[0];
                    rtc.minutes = nrfDataRx[1];
                    rtc.hours = nrfDataRx[2];
                    rtc.day = nrfDataRx[3];
                    rtc.month = nrfDataRx[4];
                    rtc.date = nrfDataRx[5];
                    rtc.year = nrfDataRx[6];
                    // Set Time of the RTC
                    DS3234_setTime(rtc);
                }
                break;
            case 2://Data sent TX
                bNrf = 1;
                bMrx = 1;
                break;
            case 3://MAX_RT TX
                // Start measuring
                ADC1_SamplingStart();
                ADC1_SamplingStop();

                // Read RTC time
                DS3234_Time(&rtcTime);

                // Add data to send
                nrfDataTx[0]= 0x48;
                nrfDataTx[1] = rtcTime.seconds;
                nrfDataTx[2] = rtcTime.minutes;
                nrfDataTx[3] = rtcTime.hours;
                // Check Data ACS722
                nrfDataTx[4] = vAdc;
                nrfDataTx[5] = vAdc >> 8;
                nrfDataTx[6] = dataAdxl[0];
                nrfDataTx[7] = dataAdxl[1];
                RF24L01_sendData(nrfDataTx, sizeof (nrfDataTx));
                break;
            default:
                break;
        }


    }// end loop
    return 0;
}

void initVariables() {
    uint16_t i;
    bExInt1 = 0;
    bData = 0;
    bNrf = 1;
    bMrx = 1;
    bInicioBloque = 0;
    //Sector write uSD
    sector = 35000;
    bWriteuSD = 1;

    // Put all values of the time to cero 
    (*(uint8_t *) & rtc) = 0x00;

    // Address NrF24L01 RX and TX
    for (i = 0; i < 5; i++) {
        //RX Address 
        rx_addr[i] = 0x78;
        //TX Address
        tx_addr[i] = 0x78;
    }
    
    for (i=0; i<63; i++){
        dataAdxl[i]= 0x00;
    }
    for (i = 0; i < 8; i++) {
        nrfDataRx[i] = 0x00;
        nrfDataTx[i] = 0x00;
    }

    /* Initialization the variable of uSD to 0xAA*/
    for (i = 0; i < 512; i++) {
        bufferE[i] = 0x5A;
    }
}
