#include "system.h"


void SYSTEM_Initialize(void)
{
    oscConfig();
    
    pines_Conf_Init();
    
    //SPI1_Init(FAST);
    
    //SPI2_Init();
    
    INTERRUPT_Initialize();
    
    EXT_INT_Initialize();
    
    TMR1_Initialize();
    
    INTERRUPT_GlobalEnable(); 
    
    //Initialize module ADC1
    //ADC1_Initialize();
    
    //DS3234_Init();
    
     // Initialize accelerometer
    //ADXL355_Init();
    
    //Initialize module nRF24L01
    //RF24L01_Init();
    
    /*
    //It Check that the uSD stay connected
    SD_Check();
    if(sdF.detected==1){
        //Initialize and If it is successful Turn on Led,
         //Update the flag
        if(SD_Init()== SUCCESSFUL_INIT){
          sdF.init_ok = 1;
            SD_Led_On();
        }       
    }
     */

}

/**
 End of File
*/