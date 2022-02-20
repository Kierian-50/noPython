# NoPython
This project aims to create a snake game on the STM32 card. But we didn't want to just create a regular snake game, we wanted to add our touch.

**Version 1.0.0**


## Contributors

- Kierian Tirlemont ; university mail : <tirlemont@et.esiea.fr> ; personal mail : <tirlemontkierian@gmail.com>
- Matéo Castella ; university mail : <castella@et.esiea.fr>
- If you want to contribute to this project you're welcome.

## Date

 - February 2022

## Language used

 - C

#### Library/Framework/Device

- LL
- PuTTY
- Timer (PA06, 3.3) : Buzzer (Passive)
- Joystick (PA00, PA01, 3.3V, GND)
- Analog to Digital Converter
- USART (PA02, PA03)
- Clavier (ZQSD) on PuTTY via USART


#### Development environment

- We have developed on the IDE: stM32CubeIDE  1.7.0

#### Link to github repository

- https://github.com/0xARK/noPython

## In which context did I this project?
 
We did this project as part of our studies in IT at ESIEA. In fact, we did it as part of our course on the embedded system development focused on the devices part. We have two and a half days to complete the project.

## The goal of the project

The goal of the project was to create a snake game with the STM32 card. The first goal was to create the game loop in c using "zqsd" keys and to have a functional game using the PuTTY and the USART communication. The second goal was to play with a joystick connected to the PA00, PA01, 3.3V and GND using an ADC. The third goal was to add a music while playing to the game. Fun fact: I did many projects/games as part of my studies and the teachers and people in general really appreciates this difference. In fact they didn't talk about the game or others functionnalities, they always talk about the music. The fourth goal was to create a 2D led matrix and display the game on it instead of on the PuTTY interface. The final goal was to create a 3D led matrix to play in 3 dimension with the joystick and the music using the STM32 card.

## The progress of the project

After two and a half days, we implement the snake game, and it works very well without known bug. It displays the game board on the PuTTY interface, and you can play using the keyboard (with the "zqsd" keys) or with the joystick connected to the PA00, the PA01, the 3.3V and the GND using an ADC. The development of the game rules was not easy, and it takes us the majority of the time, but we have the time to implement the music's part using a passive buzzer. So, we implement the Mario theme music (after modifying the code found here https://www.hackster.io/jrance/super-mario-theme-song-w-piezo-buzzer-and-arduino-1cc2e4) and the Megalovania theme music (again after modifying the code found here https://github.com/AnonymousAlly/Arduino-Music-Codes/blob/master/Megalovania.ino), a big thank you for sharing your works, that saved us a lot of time. Sadly, we could not go any further. Finally, in the loop game, we can choose the music to play during the game.

## Possible improvements

We didn't reach our final goal to create a 3D snake game, but this is a very good foundation to go further in the developing of a 2D and 3D led matrix board game. It would be better to create a box for the joystick because it's quite uncomfortable. It would be also better to have a game loop which will allow to launch several game. 

## The required file to execute this software

You mustn't have a special file to launch this project. Quite easy?

## Installation

* First, you will have to clone the project on your computer.

* To install the project on your card, you have to connect a joystick to the PA00 on the VRX of your joystick and the PA01 on the VRY. Then, you can connect the GND on the GND and the 5V on the 3.3V or 5V according to the voltage of your card.

* Next, you have to connect a buzzer to the PA06 (SCK/D13, it's the Tim22). Then you can connect to the GND and the 3.3V. 

* At this point, you can open and connect via PuTTY to the card using USART.

* Now, everything is ready: you can compile and execute the code on your card, and it should work.
