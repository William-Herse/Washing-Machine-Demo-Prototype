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

An Emergency Stop button was connected to immediately stop the system when pressed. This button was connected to the pull up interrupt input on pin 3.

Finally, a 100 Ohms resistor and LED was connected to pin 7 to signify activation of the emergency stop.

# Software

The software interfaced with the hardware at 6 different point:
Inputs
  From Encoder
  State Change Button
  Emergency Stop Interrupt
Outputs
  PWM signal
  Inverted PWM signal
  EStop LED

## State Diagram
The State Diagram shown below forms the backbone of protype software archetecture:
![image](https://user-images.githubusercontent.com/58684645/168018650-80cd3a6f-c6a4-4fbf-ba30-bb1bd02ba4de.png)

Within the state diagram there are two superstates for the purpose of the demonstration. Firstly, superstate 0 or the open loop state consists of 4 sub-states. These sub-states are Stop, Wash, Dry and Spin.

## Stop
The Stop cycle consists of stopping the motor.
![image](https://user-images.githubusercontent.com/58684645/168020574-8b6111e3-e378-428b-a688-93c7bb40ed19.png)

## Wash
The Wash cycle consists of spinning the washing machine quickly in one direction, then
slowing it and then repeating this in the other direction.
![image](https://user-images.githubusercontent.com/58684645/168020761-92beeced-7393-4d99-b316-fb1d8e797974.png)

## Dry
The Dry cycle consists of the motor starting slow and speeding up to max speed before
slowing down and eventually stoping.
![image](https://user-images.githubusercontent.com/58684645/168020515-e9222b24-ddec-419a-a155-81816e5860f3.png)

## Spin
The spin cycle consists of spinning fast in one direction and then rapidly changing to
spinning in the other direction.
![image](https://user-images.githubusercontent.com/58684645/168020892-de049a3c-4eb6-4df6-8224-78b6dbe0f8c8.png)

## Sub-State Change Interrupt
Which state the motor is in is dependent on a button driven interrupt which steps
through the states. The function for which is below:
![image](https://user-images.githubusercontent.com/58684645/168021013-0729b737-9cc9-4d3a-a109-27ccede2dcd8.png)

The second superstate or closed loop state consists of a feedback driven controller
which acts to maintain the motor at a certain speed regardless of the resistance the
motor experiences. 

## Closed Loop Controller
The controller is as follows:
![image](https://user-images.githubusercontent.com/58684645/168021373-d219a77a-9001-45cb-a4ac-2316499dccfa.png)

## Emergency Stop Interrupt
Finally, we have a button-based emergency stop interrupt:
![image](https://user-images.githubusercontent.com/58684645/168021563-4d24f3af-4490-49fb-8f61-5229eba8e91b.png)
When the interrupt is called, the motor is immediately stopped and the emergency LED
is switched on. The microcontroller then enters a continuous loop which effectively
freezes the motor. The only way to return the motor to operation is to perform a full
reset.

# References and Citation
The H-Bridge Diagram is taken from Weidong Xiao, University of Sydney

