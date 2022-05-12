# Washing-Machine-Demo-Prototype

Designed a power electronics driver system controlled by an Arduino micro-controller to drive a washing machine to work in different directions, speeds and under various loads.

This project was performed for educational purposes.

# Overview
Using a micro-controller (Arduino Uno) and a H-Bridge power converter we designed a driver that converted a 12 volt Single Phase AC power supply to DC. On top of this, by controlling the switching frequencies of the H bridge we were able to control the voltage and therefore the speed at which the motor span. Finally, the motor had a encoder which feed back a value for how fast the motor was spinning. By using this we could design a closed loop controller to regulate that the motor always span at the same speed regardless of the load applied.

# AC to DC Conversion

As the input voltage was 12 volt single phase AC, this needed to be converted to DC to power the motor. A H-bridge converts AC to DC voltage by utillising the uni-directional nature of Diode (or in our case MOSFETs). 

![image](https://user-images.githubusercontent.com/58684645/168007908-db8e6ee4-f8d7-467d-ab16-7c0bb3c95dd0.png)

By switching which diode allows current through at certain frequencies we can insure that the current over the output load is always traveling in one direction and therfore is now DC current. As a extension of this, we can also use the length of time that the diodes are open and closed to control the DC voltage output. 

Finally, a RC low pass filter was used to smoothen the ripple in the DC output.

# Hardware

Depicted below is the hardware used for this prototype:

![image](https://user-images.githubusercontent.com/58684645/168006645-29df2934-606f-4524-9891-7fcc55377fe1.png)

The hardware consists of a PCB H-Bridge, a Arduino Uno, the motor and gear unit and a breadboard used for swtich and button interaction.

The Arudino was able to controll the H-Bridge by applying a PWM and inverted PWM singal (Digital Pins 9 and 10) to the MOSFETs. A PWM signal of 50 meant that the DC voltage supplied was 0. A PWM of 99 resulted in a maximum speed clockwise rotation and a PWM of 1 resulted in a maximum speed anti-clockwise rotation.

![image](https://user-images.githubusercontent.com/58684645/168011776-371edb73-52f9-4a9b-a89c-068b8ea3b79c.png)


The values from the encoder were fed into Digital Input Pin 5.

To control the swtich between open loop and closed loop we used a dip switch ocnnected to Digital Input Pin 12.

During Open loop control, a button was used to cycles states. THis button is connected to a pull up resistor and a deboucing capacitor to reduce unwanted state changes. The button is connected to Interrupt Pin 2.

An emergency Stop button was connected to immediately stop the system when pressed. This button was connected to the pull up interrupt input on pin 3.

Finally, a 100 Ohms resistor and LED was connected to pin 7 to signify activation of the emergency stop.

# Software

The software interfaced with the hardware at 6 different point 

# References and Citation

The H-Bridge Diagram is taken from Weidong Xiao, University of Sydney

