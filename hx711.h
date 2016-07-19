#ifndef HX711
#define HX711
int init();
int mesure();
int receive24BitNumber();
void resetClock(int gain);
int sm2tc(int x);
int toGram(int numb);
void createFilesForCalibration();
int tare();
#endif
