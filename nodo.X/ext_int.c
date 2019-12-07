/**
   Section: Includes
 */
#include "ext_int.h"

unsigned char bNrf = 0;
/**
   Section: External Interrupt Handlers
 */

void __attribute__((weak)) EX_INT0_CallBack(void) {
    // Add your custom callback code here
}

/**
  Interrupt Handler for EX_INT0 - INT0
 */
void __attribute__((interrupt, no_auto_psv)) _INT0Interrupt(void) {
    //***User Area Begin->code: External Interrupt 0***

    EX_INT0_CallBack();

    //***User Area End->code: External Interrupt 0***
    EX_INT0_InterruptFlagClear();
}

void __attribute__((weak)) EX_INT1_CallBack(void) {
    // Add your custom callback code here
    Led_verde_toggle();
    //banderInt1 = 0;
    //banderCont = 0;
    //ADXL355_Read_FIFO_Full();

}

/**
  Interrupt Handler for EX_INT1 - INT1
 */
void __attribute__((interrupt, no_auto_psv)) _INT1Interrupt(void) {
    //***User Area Begin->code: External Interrupt 1***

    EX_INT1_CallBack();

    //***User Area End->code: External Interrupt 1***
    EX_INT1_InterruptFlagClear();
}

void __attribute__((weak)) EX_INT2_CallBack(void) {
    uint8_t sent_info = 0;

    Led_verde_toggle();

    /*Check data was sent*/
    if ((sent_info = RF24L01_was_data_sent())) {
        //Packet was sent or max retries reached
        bNrf = sent_info;
        RF24L01_clear_interrupts();
        return;
    }
    /*Check data is available*/
    if (RF24L01_is_data_available()) {
        //Packet was received
        mutex = 1;
        RF24L01_clear_interrupts();
        return;
    }

    RF24L01_clear_interrupts();
}

/**
  Interrupt Handler for EX_INT2 - INT2
 */
void __attribute__((interrupt, no_auto_psv)) _INT2Interrupt(void) {
    //***User Area Begin->code: External Interrupt 2***

    EX_INT2_CallBack();

    //***User Area End->code: External Interrupt 2***
    EX_INT2_InterruptFlagClear();
}
/**
    Section: External Interrupt Initializers
 */

/**
    void EXT_INT_Initialize(void)

    Initializer for the following external interrupts
    INT0
    INT1
    INT2
 */
void EXT_INT_Initialize(void) {
    /*******
     * INT0
     * Clear the interrupt flag
     * Set the external interrupt edge detect
     * Enable the interrupt, if enabled in the UI. 
     ********/
    EX_INT0_InterruptFlagClear();
    EX_INT0_PositiveEdgeSet();
    EX_INT0_InterruptDisable();
    /*******
     * INT1
     * Clear the interrupt flag
     * Set the external interrupt edge detect
     * Enable the interrupt, if enabled in the UI. 
     ********/
    EX_INT1_InterruptFlagClear();
    EX_INT1_PositiveEdgeSet();
    EX_INT1_InterruptEnable();
    /*******
     * INT2
     * Clear the interrupt flag
     * Set the external interrupt edge detect
     * Enable the interrupt, if enabled in the UI. 
     ********/
    EX_INT2_InterruptFlagClear();
    EX_INT2_NegativeEdgeSet();
    EX_INT2_InterruptEnable();
}
