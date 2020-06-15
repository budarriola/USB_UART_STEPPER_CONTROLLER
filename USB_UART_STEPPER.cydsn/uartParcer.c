/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "uartParcer.h"
#include <stdlib.h>
#include <math.h>

#define BUFFER_SIZE 32

#define COMMAND_START '@'
#define COMMAND_END_1 '\r'
#define COMMAND_END_2 '\n'

#define COMMAND_TURN 'T'
#define COMMAND_SET_RPM 'R'

char strbuffer[BUFFER_SIZE+1];
unsigned int strbuffer_index = 0;
int command_started = 0;
int command_ready = 0;

void (*turnCallback)(float degrees) = NULL;
void (*setRpmCallback)(float rpm) = NULL;

void initCallbacks(void (*turnFunction)(float degrees), void (*setRpmFunction)(float rpm)){
    turnCallback = turnFunction;
    setRpmCallback  = setRpmFunction;
}



//if return 1 then there is a command to process
int uart_NewData(unsigned char* uart_string, unsigned int len){
    unsigned int i;
    
    for(i=0;i<len;i++){
        //if there is not a pending command
        if(!command_ready){
            switch(uart_string[i]){   
            
                case COMMAND_START:
                    //this was the start of a command
                    strbuffer_index = 0;
                    command_started = 1;
                    break;
            
                case COMMAND_END_1:
                case COMMAND_END_2:
                    if(command_started){
                        //we have a complete command
                        command_started = 0;
                        //strings end with the null char
                        strbuffer[strbuffer_index] = '\0';
                        strbuffer_index++;
                        command_ready = 1;
                        return 1;
                    }                    
                    break;
                
                default:
                    if(command_started){
                        //if there is space in the buffer
                        if(strbuffer_index<(BUFFER_SIZE-1)){
                            //save the byte
                            strbuffer[strbuffer_index] = uart_string[i];
                            strbuffer_index++;
                        }else{
                            command_started=0;
                            strbuffer_index=0;
                        }
                    }
            }
        }
        
    }
    return 0;
}

int processCommand(){
    float degrees,rpm;
    if(command_ready){
        command_ready = 0;
        
        switch(strbuffer[0]){
            
            case COMMAND_TURN:
            case (COMMAND_TURN+32):
                degrees = strtof(&strbuffer[1],NULL);
                if(fabs(degrees)>0){
                    turnCallback(degrees);
                    return 1;
                }
                break;
            
            case COMMAND_SET_RPM:
            case (COMMAND_SET_RPM+32):
                rpm = strtof(&strbuffer[1],NULL);
                if(rpm>0){
                    setRpmCallback(rpm);
                    return 1;
                }
                break;
        }
        
    }
    return 0;
}
/* [] END OF FILE */
