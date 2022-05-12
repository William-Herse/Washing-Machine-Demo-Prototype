# Washing-Machine-Demo-Prototype

Designed a power electronics driver system controlled by an Arduino micro-controller to drive a washing machine to work in different directions, speeds and under various loads.

# Overview
Using a micro-controller (Arduino Uno) and a H-Bridge power converter we designed a driver that converted a 12 volt Single Phase AC power supply to DC. On top of this, by controlling the switching frequencies of the H bridge we were able to control the voltage and therefore the speed at which the motor span. Finally, the motor had a encoder which feed back a value for how fast the motor was spinning. By using this we could design a closed loop controller to regulate that the motor always span at the same speed regardless of the load applied.

# AC to DC Conversion

![image](https://user-images.githubusercontent.com/58684645/168007908-db8e6ee4-f8d7-467d-ab16-7c0bb3c95dd0.png)


# Hardware

Depicted below is the hardware used for this prototype:

![image](https://user-images.githubusercontent.com/58684645/168006645-29df2934-606f-4524-9891-7fcc55377fe1.png)

The hardware consists of a PCB H-Bridge, a Arduino Uno, the motor and gear unit and a breadboard used for swtich and button interaction.




# References and Citation
