#ifndef DS3234_H
#define DS3234_H
#include "spi2.h"

/*****************************************************************************/
/* DS3234 Variables */

/*****************************************************************************/
// Variable of time and date
typedef struct {
    //00-59
    uint8_t seconds;
    //00-59
    uint8_t minutes;
    //00-23
    uint8_t hours;
    //00-07
    uint8_t day;
    //00-31
    uint8_t date;
    //01-12
    uint8_t month;
    //00-99
    uint8_t year;
} ds3234_data_time;

typedef struct{
    //00-59
    uint8_t seconds;
    //00-59
    uint8_t minutes;
    //00-23
    uint8_t hours;
}ds3234_time;

/*Variables with field of bits structure*/
typedef struct{
    // Alarm 1 Interrupt Enable
    uint8_t A1IE : 1;
    // Alarm 2 Interrupt Enable
    uint8_t A2IE : 1;
    // Interrupt Control
    uint8_t INTCN : 1;
    // Rate Select
    uint8_t RS1 : 1;
    // Rate Select
    uint8_t RS2 : 1;
    // Convert Temperature
    uint8_t CONV : 1;
    // Battery-Backed Square-Wave Enable
    uint8_t BBSQW : 1;
    // Enable Oscillator
    uint8_t EOSCC : 1;
} ds3234_control_register;


#define bcd_to_int(X)  (10*((X) >> 4)) + ((X) & 0x0F)

#define int_to_bcd(X) ((X) - ((X)/10)*10) | (((X) / 10) << 4)

//Define Port to Use
#define SQW_OUT PORTAbits.RA2
//Define chip select DS3234
#define DS3234_ChepSelect PORTBbits.RB6

/*****************************************************************************/
/* DS3234 Define address register name */
/*****************************************************************************/
#define WRITE_TIME_REG      0x80
#define READ_TIME_REG       0x00
#define WRITE_CONTROL_REG   0x8E
#define READ_CONTROL_REG    0x0E


/*****************************************************************************/
/* DS3234 Function Prototyping */
/*****************************************************************************/
void DS3234_Init(void);

void DS3234_readTime(ds3234_data_time*);

void DS3234_Time(ds3234_time*);

void DS3234_setTime(ds3234_data_time data_time);


#endif// End DS3234_H