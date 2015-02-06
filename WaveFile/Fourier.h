#ifndef FOURIER_H
#define FOURIER_H

#include <complex>
#include <math.h>
#include <vector>
#include "Commons/Commons.h"

typedef struct CFtItem
{
  double frequency;
  double amplitude;

  CFtItem(void):frequency(0.0), amplitude(0.0){}
  //frequency = (i * inputFrequency) / (m_numSamples);
  //i - номер элемента. inputFrequency - wf.header.opt.sampleRate. numSamples - количество отчетов.
  CFtItem(double rp, double ip, double frequency):
    frequency(frequency),
    amplitude(sqrt(rp*rp + ip*ip)) {}  
} CFtItem;
/////////////////////////////////////////////////////////////////////////

class CFourier {
public:
  static const int MAX_LOG2_N = 32;
  
private:
  CFourier(void);
  ~CFourier(void);

public:
  static bool FT(double* RSrcData, double *ISrcData,
                 double* RDstData, double *IDstData,
                 int N, bool inv);
  
  typedef std::complex<double> complex_double;
  static bool FFT( std::vector<complex_double> &a, bool inv ); //optimized i think :)
  static bool FFT_d(double *Rdat, double *Idat, int N, int LogN, bool inv); //best of the best of the best
  static bool FFT_f(float *Rdat, float *Idat, int N, int LogN, bool inv); //best of the best of the best


  static unsigned int NextPowerOfTwo(unsigned int N) {
    --N;
    N |= N >> 1;
    N |= N >> 2;
    N |= N >> 4;
    N |= N >> 8;
    N |= N >> 16;
    return ++N;
  }
};
#endif //FOURIER_H
