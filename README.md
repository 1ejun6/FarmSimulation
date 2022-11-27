# FarmSimulation

Singapore aims to produce 30% of its nutritional needs by 2030.<br/>
Client- The Singapore Food Agency (SFA) has been supporting local farmers to adopt technology to boost the output of the vegetables grown by farmers.
<br><br/>
My team is tasked to produce a prototype for the automated farming system using microcontroller system. The proposed system shall be able to monitor the environmental conditions, so that measures can be taken to adjust the crop production.
<br><br/>
## Microcontroller- PIC16F18877
### Top view of the Board <br/>
![Alt text](/Main/Photo/TopBoard.png)
### Bottom view of the Board <br/>
![Alt text](/Main/Photo/BottomBoard.png)
## System <br/>
The system has a start up melody sound. Using the keypad to enter R1-R3 & B
Press C to cancel
>1 R1 2 R2 3 R3 3 R3<br> 
For simulation

### R1 ) LM35 Temperature Sensor
Using the ADC technique to read from the LM35. LM35 simulates the temperature sensor. The temperature reading is displayed on the LCD. If the temperature becomes too high, the sprinkler stimulate by the motor will activate to cool it down. 
<br><br/>
### R2 ) PHLevel
Using the ADC technique to read from the trimmer. The PH Level sensor is simulated by the trimmer. PH Level which is connected to 3 Led, Green- Healthy, Yellow- Acidic & Red- Base. Display message to the LCD Screen and 7 Segment.
<br><br/>
### R3 ) Irrigation System 
PWM Levels for Motor 4 different levels setting. Using pulse width to set the intensity of the irrigation system. 3 level of intensity. LCD displays “2 Level”, “3 Level”, “4 Level”. 
<br><br/>
### B ) Break In simualation
B simulates a break in. An alarm sound will play and a prompt will pop up 
>"Enter Verify Key 2 Stop" 

Once the correct verification key is enter the alarm would be disabled.<br/>
>"Wrong key. Try Again

If the wrong key is entered the alarm will continue to sound.
<br><br/>
### Sleep Mode
Timer0 to Sleep the System after 180s. ISR to interrupt stimulate with a push button to wake up the system.

