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
uint8_t bExInt1, bNrf, bData, bInicioBloque, bAdc, bMrx;
ds3234_data_time rtc;
ds3234_time rtcTime;
uint32_t sector;
uint16_t vAdc, delay;
uint16_t i;
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
    //ADC1_SamplingStart();
    //ADC1_SamplingStop();

    //Set Mode RX
    //RF24L01_set_mode_RX();

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
        Led_verde_toggle();
        __delay_ms(250);

        switch (bNrf) {
            case 1:
                bNrf = 0;
                if (bMrx == 1) {
                    bMrx = 0;
                    RF24L01_set_mode_RX();
                } else {
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
            case 2:
                __delay_us(130);
                // Start measuring
                ADC1_SamplingStart();
                ADC1_SamplingStop();


                /*
                 * PREPARE THE RESPONSE
                 */

                // Read RTC time
                DS3234_Time(&rtcTime);

                // Add data to send
                nrfDataTx[0] = 0x48;
                nrfDataTx[1] = rtcTime.seconds;
                nrfDataTx[2] = rtcTime.minutes;
                nrfDataTx[3] = rtcTime.hours;
                // Check Data ACS722
                if (bAdc) {
                    nrfDataTx[4] = vAdc;
                    nrfDataTx[5] = vAdc >> 8;
                    bAdc = 0;
                } else {
                    nrfDataTx[4] = 0x48;
                    nrfDataTx[5] = 0x48;
                }

                nrfDataTx[6] = 0x48;
                nrfDataTx[7] = 0x48;

                //Send Data
                RF24L01_sendData(nrfDataTx, sizeof (nrfDataTx));
                break;
            case 3:
                __delay_ms(1);
                //MAX_RT TX 
                RF24L01_sendData(nrfDataTx, sizeof (nrfDataTx));
                break;
            default:
                break;
        }


    }// end loop
    return 0;
}

void initVariables() {
    bExInt1 = 0;
    bData = 0;
    bNrf = 1;
    bMrx = 1;
    bInicioBloque = 0;
    //Sector write uSD
    sector = 35000;
    bWriteuSD = 0;
    bAdc = 0;

    // Put all values of the time to cero 
    (*(uint8_t *) & rtc) = 0x00;

    // Address NrF24L01 RX and TX
    for (i = 0; i < 5; i++) {
        //RX Address 
        rx_addr[i] = 0x78;
        //TX Address
        tx_addr[i] = 0x78;
    }

    for (i = 0; i < 32; i++) {
        nrfDataRx[i] = 0x00;
        nrfDataTx[i] = 0x0A;
    }

    /* Initialization the variable of uSD to 0xAA*/
    for (i = 0; i < 512; i++) {
        bufferE[i] = 0x5A;
    }
}
