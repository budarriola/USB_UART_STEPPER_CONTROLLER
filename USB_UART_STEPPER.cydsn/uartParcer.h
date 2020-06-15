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

//returns true when there is a command to be processed
int uart_NewData(unsigned char* uart_string, unsigned int len);
void initCallbacks(void (*turnFunction)(float degrees), void (*setRpmFunction)(float rpm));
//returns 1 on process
int processCommand();

/* [] END OF FILE */
