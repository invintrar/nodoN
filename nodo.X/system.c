#include "system.h"

void SYSTEM_Initialize(void) {
    oscConfig();

    pines_Conf_Init();

    SPI1_Init(FAST);

    SPI2_Init();

    INTERRUPT_Initialize();

    EXT_INT_Initialize();

    //TMR1_Initialize();

    //Initialize module ADC1
    ADC1_Initialize();

    INTERRUPT_GlobalEnable();


    DS3234_Init();

    // Initialize accelerometer
    //ADXL355_Init();

    //Initialize module nRF24L01
    RF24L01_Init();
    
    //uSDState = SD_Init();

}

/**
 End of File
 */