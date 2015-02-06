#ifndef FFTWINDOW_H
#define FFTWINDOW_H

#include <cmath>
#include <math.h>

typedef enum WindowFunctions {
  WF_Rectangle,
  WF_Sinus,
  WF_Sinc,
  WF_Treangle,
  WF_Hann,
  WF_Hamming,
  WF_Blackman,
  WF_Nutall,
  WF_Gaussian
} WindowFunctions;
/////////////////////////////////////////////////////////////////////////

typedef double (*lpWindowFunc)(double n, double N);

class CFftWindow
{
private:
  static inline double sinc(double x) {
    return sin(M_PI * x) / M_PI * x;
  }

  static inline double gauss(double n, double N, double sigm) {
    double A = (N - 1) / 2;
    double arg = pow(((n - A) / (sigm * A)), 2);
    return exp(-0.5 * arg);
  }
  /////////////////////////////////////////////////////////////////////////

  static inline double RectangleFunc(double, double) {
    return 1.0;
  }
  /////////////////////////////////////////////////////////////////////////

  static inline double SinusFunc(double n, double N) {
    return sin((M_PI*n) / (N-1));
  }
  /////////////////////////////////////////////////////////////////////////

  static inline double SincFunc(double n, double N) {
    return sinc((2*n)/(N-1) - 1);
  }
  /////////////////////////////////////////////////////////////////////////

  static inline double TreangleFunc(double n, double N) {
    return 1 - std::abs((2*n)/(N-1) - 1);
  }
  /////////////////////////////////////////////////////////////////////////

  static inline double HannFunc(double n, double N) {
    return 0.5 - 0.5 * cos((2*M_PI*n) / (N-1));
  }
  /////////////////////////////////////////////////////////////////////////

  static inline double HammingFunc(double n, double N) {
    return 0.54 - 0.46 * cos((2*M_PI*n) / (N-1));
  }
  /////////////////////////////////////////////////////////////////////////

  static inline double BlackmannFunc(double n, double N) {
    return 0.42 - 0.5 * cos((2*M_PI*n) / (N-1)) + 0.08 * cos((4*M_PI*n) / (N-1));
  }
  /////////////////////////////////////////////////////////////////////////

  static inline double NutallFunc(double n, double N) {
    return 0.355768 -
        0.487396 * cos((2*M_PI*n) / (N-1)) +
        0.1365995 * cos((4*M_PI*n) / (N-1)) -
        0.0106411 * cos((6*M_PI*n) / (N-1)) ;
  }
  /////////////////////////////////////////////////////////////////////////

  static inline double GaussianFunc(double n, double N) {
    return gauss(n, N, 0.3);
  }
  /////////////////////////////////////////////////////////////////////////

public:
  //n - номер отсчета. N - количество отсчетов.
  static lpWindowFunc GetWindowFunc(WindowFunctions wf)
  {
    switch(wf) {
    case WF_Sinus: return SinusFunc;
    case WF_Sinc: return SincFunc;
    case WF_Treangle: return TreangleFunc;
    case WF_Hann: return HannFunc;
    case WF_Hamming: return HammingFunc;
    case WF_Blackman: return BlackmannFunc;
    case WF_Nutall: return NutallFunc;
    case WF_Gaussian: return GaussianFunc;
    case WF_Rectangle:
    default:
      return RectangleFunc;
    }
  }

};

#endif // FFTWINDOW_H

