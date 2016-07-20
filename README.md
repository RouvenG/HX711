# HX711 
README not finished but will be completed 20.07.2016

Basic driver for the HX711 load cell to connect with the raspberry pi2 b+
https://cdn.sparkfun.com/datasheets/Sensors/ForceFlex/hx711_english.pdf

At first you have to calibrate your scale.


First you will have 3 functions which are interesting for you those are
int init();  int mesure(); int tare();
As first you have to use init(), the HX711 gets initialized, init() calls tare() once.
Now you can start to measure weight with the function measure(). The return value of the function is
the weight in gram as an integer. If you want to have a different unity please change the toGram() funtion in the code.



Compile Process:

g++ -l wiringPi yourprogramm.c hx711.c -o yourProgrammName
