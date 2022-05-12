#include "LedControl.h"
#include "arduinoFFT.h"

#define SAMPLES 64
#define MIC_IN A0 
#define xres 8
#define yres 8 
#define MAXVAL 500
#define MINABS 20

LedControl lc=LedControl(12,11,10,1);

unsigned long delaytime=100;

arduinoFFT FFT = arduinoFFT();

double vReal[SAMPLES];
double vImag[SAMPLES];

int Intensity[xres] = { };
int Displacement = 1;

void setup() {
  pinMode(MIC_IN, INPUT);
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
}

void writeBar (int row, int level) {
  byte bar[9]={B0000000, B10000000,B11000000,B11100000,B11110000,B11111000, B11111100, B11111110, B11111111};
  lc.setRow(0, row, bar[level]);
}

void loop() {
  for(int i = 0; i < SAMPLES; i++){
    vReal[i] = analogRead(MIC_IN);
    vImag[i] = 0;
  }

  //FFT
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

  double maxval = MAXVAL;
  
  for(int i = 2; i < (xres*Displacement)+2; i+=Displacement){
    if (vReal[i] > maxval)
      maxval = vReal[i];
  }
  
  for(int i = 2; i < (xres*Displacement)+2; i+=Displacement){
    vReal[i] = constrain(vReal[i],MINABS ,maxval);            // set max value for input data
    vReal[i] = map(vReal[i], MINABS, maxval, 0, yres);        // map data to fit our display

    Intensity[(i/Displacement)-2] --;                      // Decrease displayed value
    if (vReal[i] > Intensity[(i/Displacement)-2])          // Match displayed value to measured value
      Intensity[(i/Displacement)-2] = vReal[i];
  }

  for(int i = 0; i < xres; i++){
    writeBar(i, Intensity[i]);
  }
 }
