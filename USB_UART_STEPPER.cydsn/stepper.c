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
#include "stepper.h"
#include "project.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define STEPS_PER_REV 3200U
#define RPM_TIME_PERIOD_US (60000000)
float currentRpm = 20;

void stepper_move(float degrees){
    
    unsigned int steps,i,delayTime;
    
    if(degrees>0){
        Pin_Dir_Write(1);
    }else{
        Pin_Dir_Write(0);
    }
    
    CyDelayUs(1000);
    
    steps = ( STEPS_PER_REV / 360.0f ) * fabs( degrees );
    // devide by two to account for 50?duty cycle
    delayTime = ( RPM_TIME_PERIOD_US / currentRpm )/STEPS_PER_REV/2.0f;
    
    for (i = 0; i < steps; i++){
        Pin_Step_Write(1);
        CyDelayUs(delayTime);
        Pin_Step_Write(0);
        CyDelayUs(delayTime);
    }
}

void stepper_setRpm(float rpm){
    currentRpm = rpm;
}

void stepper_setup(){
    //set 1/16 microsteping
    Pin_AS1_Write(1);
    Pin_AS2_Write(1);
    
    //turn motor output on
    Pin_EN_Write(0);
    
    //turn driver on
    Pin_Pdn_Uart_Write(0);
    
    //set internal ocilator
    Pin_Clk_Write(0);
}
/* [] END OF FILE */
