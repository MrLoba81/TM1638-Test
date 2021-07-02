# TM1638-Test
A simple Arduino sketch with an animation to test the TM1638 with a common anode custom display with 8 digits and 8 little bars

The sketch does not make use of `dalay()`, this is a good practice to write non blocking code

## The display

[@Katodo](http://www.katodo.com/) kindly sent me some seven-segment [displays](https://www.instagram.com/p/CQjNuIhl7A8/?utm_source=ig_web_copy_link).
I want to thanks him and also thanks to [@cyb3rn0id](https://www.instagram.com/cyb3rn0id/) that made this possible.

They have two lines of four digits with different size and colors and also eight indicators bars
1. First line - bigger and green
2. Second line - smaller and red
So in total there are nine digits to drive.

They are common anode display with two rows of nine pins with standard horizontal spacing but non standard vertical spacing, the 7th pin on the first row is not connected.

You can find the pinout on my instagram [post](https://www.instagram.com/p/CQluUURsMMK/ "Display pinouts")

## The driver TM1638

It supports up to ten digits with eight segments in common anode mode and has also a key scan feature that permits to drive a keypad up to 24 keys, is housed in a SOP28 package so has to be [soldered](https://www.instagram.com/p/CQwO8B5FK0p/ "TM1638 soldering") on an adapter to be used on a protoboard

I found it while reading [Elettronica In](https://www.elettronicain.it/) n.253, an Italian magazine about electronics published by [@futuragroupsrl](https://www.futurashop.it/)

## The protoype

I assembled the display and the TM1638 on a breadboard with an Arduino Nano.

Take a look at the [post](https://www.instagram.com/p/CQyn6d0FTOU/) on my instagram, there is a video of the simple animation.

![IMG20210701171704](https://user-images.githubusercontent.com/84834981/124252643-7353a080-db27-11eb-99bd-d4eb79a28b20.jpg)
