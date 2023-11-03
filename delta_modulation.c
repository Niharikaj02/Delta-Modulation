#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

#define FM 3400.0  // Frequency of the input signal in Hz
#define DELTA 0.1  // Delta value for delta modulation
#define SAMPLE_RATE 200000 // Sampling rate in Hz

int main() {
 double fm = 3400.0;
 double T = 1.0 / fm;
 double del = 0.1;
 // Sampling Operation
 double fs = 20.0 * fm; // Oversampling
 double Ts = 1.0 / fs;
 double n = 0.0;
 double yn = 0.0; // Declare yn here

 // Initialize variables for delta modulation and demodulation
 double xstaircase = 0.0;
 int digout = 0;
 double rsignal = 0.0; // Declare rsignal here
 double decsig = 0.0;
 double temp = 0.0;

 // Sampling loop
 while (n <= 2.0 * T) {
  yn = sin(2.0 * M_PI * fm * n);
  printf("%f, %f\n", n, yn); // Print sampled signal
  n += Ts;
 }

 // Reset n for delta modulation
 n = 0.0;

 // Delta Modulation
 while (n <= 2.0 * T - Ts) {
  if (xstaircase <= yn) {
   xstaircase += del;
   digout = 1;
  } else {
   xstaircase -= del;
   digout = 0;
  }
  printf("%f, %d\n", n, digout); // Print digital output signal
  n += Ts;
 }

 // Reset n for DM demodulation
 n = 0.0;

 // DM Demodulation
 while (n <= 2.0 * T - Ts) {
  rsignal = (digout + 1) / 2.0; // Assign digout to rsignal

  if (rsignal == 1) {
   decsig = del;
  } else {
   decsig = -del;
  }
  temp += decsig;
 
  // Print the demodulated signal to the console
  printf("%f, %f\n", n, temp);

  n += Ts;
 }

 return 0;
}
