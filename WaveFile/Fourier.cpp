#include <assert.h>
#include "Fourier.h"



CFourier::CFourier(void)
{
}

CFourier::~CFourier(void)
{
}
//////////////////////////////////////////////////////////////////////////

const double M_PI_MUL_2 = 3.14159265358979323846 * 2.0;
bool CFourier::FT( double* RSrcData, double* ISrcData,
                   double *RDstData, double *IDstData,
                   int N, bool inv )
{
  if (RSrcData == NULL || ISrcData == NULL ||
      RDstData == NULL || IDstData == NULL) return false;
  if (N < 0)
    return false;

  int n, k;
  double w, sw, cw;
  double wCoef = inv ? 1.0 / N : -1.0 / N;

  for (k = 0; k < N; k++){
    RDstData[k] = IDstData[k] = 0.0;
    for (n = 0; n < N; n++){
      w = M_PI_MUL_2 * k * n * wCoef;
      sw = sin(w);
      cw = cos(w);
      RDstData[k] += (RSrcData[n]*cw - ISrcData[n]*sw);
      IDstData[k] += (RSrcData[n]*sw + ISrcData[n]*cw);
    }
  }

  if (!inv) return true;

  for (n = 0; n < N; n++){
    RDstData[n] *= wCoef;
    IDstData[n] *= wCoef;
  }

  return true;
}
//////////////////////////////////////////////////////////////////////////

static const int max_lgn = 63;
static double RPartTable[max_lgn] = {
  -1.00000000000000000, 0.00000000000000006, 0.70710678118654757,
  0.92387953251128674, 0.98078528040323043, 0.99518472667219693,
  0.99879545620517241, 0.99969881869620425, 0.99992470183914450,
  0.99998117528260111, 0.99999529380957619, 0.99999882345170188,
  0.99999970586288223, 0.99999992646571789, 0.99999998161642933,
  0.99999999540410733, 0.99999999885102686, 0.99999999971275666,
  0.99999999992818922, 0.99999999998204725, 0.99999999999551181,
  0.99999999999887801, 0.99999999999971945, 0.99999999999992983,
  0.99999999999998246, 0.99999999999999567, 0.99999999999999889,
  0.99999999999999978, 0.99999999999999989, 1.00000000000000000,
  1.00000000000000000, 1.00000000000000000, 1.00000000000000000,
  1.00000000000000000, 1.00000000000000000, 1.00000000000000000,
  1.00000000000000000, 1.00000000000000000, 1.00000000000000000,
  1.00000000000000000, 1.00000000000000000, 1.00000000000000000,
  1.00000000000000000, 1.00000000000000000, 1.00000000000000000,
  1.00000000000000000, 1.00000000000000000, 1.00000000000000000,
  1.00000000000000000, 1.00000000000000000, 1.00000000000000000,
  1.00000000000000000, 1.00000000000000000, 1.00000000000000000,
  1.00000000000000000, 1.00000000000000000, 1.00000000000000000,
  1.00000000000000000, 1.00000000000000000, 1.00000000000000000,
  1.00000000000000000, 1.00000000000000000, 1.00000000000000000 };

static double ImPartTable_direct[max_lgn] = {
  -0.00000000000000012, -1.00000000000000000, -0.70710678118654746,
  -0.38268343236508978, -0.19509032201612825, -0.09801714032956060,
  -0.04906767432741802, -0.02454122852291229, -0.01227153828571993,
  -0.00613588464915448, -0.00306795676296598, -0.00153398018628477,
  -0.00076699031874270, -0.00038349518757140, -0.00019174759731070,
  -0.00009587379909598, -0.00004793689960307, -0.00002396844980842,
  -0.00001198422490507, -0.00000599211245264, -0.00000299605622633,
  -0.00000149802811317, -0.00000074901405658, -0.00000037450702829,
  -0.00000018725351415, -0.00000009362675707, -0.00000004681337854,
  -0.00000002340668927, -0.00000001170334463, -0.00000000585167232,
  -0.00000000292583616, -0.00000000146291808, -0.00000000073145904,
  -0.00000000036572952, -0.00000000018286476, -0.00000000009143238,
  -0.00000000004571619, -0.00000000002285809, -0.00000000001142905,
  -0.00000000000571452, -0.00000000000285726, -0.00000000000142863,
  -0.00000000000071432, -0.00000000000035716, -0.00000000000017858,
  -0.00000000000008929, -0.00000000000004464, -0.00000000000002232,
  -0.00000000000001116, -0.00000000000000558, -0.00000000000000279,
  -0.00000000000000140, -0.00000000000000070, -0.00000000000000035,
  -0.00000000000000017, -0.00000000000000009, -0.00000000000000004,
  -0.00000000000000002, -0.00000000000000001, -0.00000000000000001,
  -0.00000000000000000, -0.00000000000000000, 0.00000000000000000 };

static double ImPartTable_reverse[max_lgn] = {
  0.00000000000000012, 1.00000000000000000, 0.70710678118654746,
  0.38268343236508978, 0.19509032201612825, 0.09801714032956060,
  0.04906767432741802, 0.02454122852291229, 0.01227153828571993,
  0.00613588464915448, 0.00306795676296598, 0.00153398018628477,
  0.00076699031874270, 0.00038349518757140, 0.00019174759731070,
  0.00009587379909598, 0.00004793689960307, 0.00002396844980842,
  0.00001198422490507, 0.00000599211245264, 0.00000299605622633,
  0.00000149802811317, 0.00000074901405658, 0.00000037450702829,
  0.00000018725351415, 0.00000009362675707, 0.00000004681337854,
  0.00000002340668927, 0.00000001170334463, 0.00000000585167232,
  0.00000000292583616, 0.00000000146291808, 0.00000000073145904,
  0.00000000036572952, 0.00000000018286476, 0.00000000009143238,
  0.00000000004571619, 0.00000000002285809, 0.00000000001142905,
  0.00000000000571452, 0.00000000000285726, 0.00000000000142863,
  0.00000000000071432, 0.00000000000035716, 0.00000000000017858,
  0.00000000000008929, 0.00000000000004464, 0.00000000000002232,
  0.00000000000001116, 0.00000000000000558, 0.00000000000000279,
  0.00000000000000140, 0.00000000000000070, 0.00000000000000035,
  0.00000000000000017, 0.00000000000000009, 0.00000000000000004,
  0.00000000000000002, 0.00000000000000001, 0.00000000000000001,
  0.00000000000000000, 0.00000000000000000, -0.00000000000000000 };

//hightest speed :)
bool CFourier::FFT( std::vector<complex_double> &a, bool inv )
{
  int n = (int) a.size();
  //invert bits in lg_n based number and reorder data in a sequence
  for (int i=1, j=0; i<n; ++i) {
    int bit = n >> 1;
    for (; j>=bit; bit>>=1)
      j -= bit;
    j += bit;
    if (i < j)
      std::swap(a[i], a[j]);
  }

  //work with blocks of len elements
  double *ImPartSourceTable = inv ? ImPartTable_reverse : ImPartTable_direct;
  for (int len = 2, lgn = 0; len <= n; len <<= 1, lgn++) {
    complex_double wlen(RPartTable[lgn], ImPartSourceTable[lgn]);

    //butterfly on each element in block
    for (int i = 0; i < n; i+=len){
      complex_double w(1.0);
      for (int j = 0; j < len/2; ++j){
        complex_double u = a[i+j], v = a[i+j+len/2] * w;
        a[i+j] = u + v;
        a[i+j+len/2] = u - v;
        w *= wlen;
      }
    }
  }

  if (inv){
    for (int i = 0; i < n; ++i)
      a[i] /= n;
  }
  return true;
}
//////////////////////////////////////////////////////////////////////////

static double RCoef[CFourier::MAX_LOG2_N] = {
  -1.00000000000000000000000000, 0.00000000000000006123233996, 0.70710678118654757273731093,
  0.92387953251128673848313611, 0.98078528040323043057924224, 0.99518472667219692873175063,
  0.99879545620517240500646494, 0.99969881869620424996725205, 0.99992470183914450299056398,
  0.99998117528260110908888691, 0.99999529380957619117964441, 0.99999882345170187925020855,
  0.99999970586288222662574299, 0.99999992646571789212117665, 0.99999998161642933425241608,
  0.99999999540410733356310402, 0.99999999885102686114635162, 0.99999999971275665977543667,
  0.99999999992818922045501040, 0.99999999998204724960260137, 0.99999999999551181240065034,
  0.99999999999887800861131382, 0.99999999999971944664167722, 0.99999999999992983390484369,
  0.99999999999998245847621092, 0.99999999999999567013020396, 0.99999999999999888977697537,
  0.99999999999999977795539507, 0.99999999999999988897769754, 1.00000000000000000000000000,
  1.00000000000000000000000000, 1.00000000000000000000000000
};

static double ICoef[CFourier::MAX_LOG2_N] = {
  0.00000000000000012246467991, 1.00000000000000000000000000, 0.70710678118654746171500847,
  0.38268343236508978177923268, 0.19509032201612824808378832, 0.09801714032956060362877793,
  0.04906767432741801493456535, 0.02454122852291228812360302, 0.01227153828571992538742919,
  0.00613588464915447526909498, 0.00306795676296597614324257, 0.00153398018628476550014039,
  0.00076699031874270448549957, 0.00038349518757139556320718, 0.00019174759731070329152845,
  0.00009587379909597734466923, 0.00004793689960306688130961, 0.00002396844980841821931778,
  0.00001198422490506970529769, 0.00000599211245264242752721, 0.00000299605622633466083516,
  0.00000149802811316901114271, 0.00000074901405658471574140, 0.00000037450702829238412872,
  0.00000018725351414619534661, 0.00000009362675707309808359, 0.00000004681337853654908812,
  0.00000002340668926827455068, 0.00000001170334463413727699, 0.00000000585167231706863850,
  0.00000000292583615853431925, 0.00000000146291807926715962
};
//////////////////////////////////////////////////////////////////////////

#define  NUMBER_IS_2_POW_K(x)   ((!((x)&((x)-1)))&&((x)>1))  // x is pow(2, k), k=1,2, ...

bool CFourier::FFT2(double *Rdat, double *Idat, int N, int LogN, bool inv)
{
  // parameters error check:
  assert(Rdat);
  assert(Idat);
  assert(NUMBER_IS_2_POW_K(N));
  assert(LogN >= 2 && LogN <= MAX_LOG2_N);

  register int  i, j, n, k, io, ie, in, nn;
  double        ru, iu, rtp, itp, rtq, itq, rw, iw, sr;

  nn = N >> 1;
  ie = N; //N для каждого из уровней. для первого N. Для второго N/2 и т.д.
  for(n=1; n<=LogN; n++) {
    //rw и iw - поворотный коэффициент для LogN.
    //w = -2.0 * M_PI / pow(2.0, n)
    rw = RCoef[LogN - n]; //cos(w)
    iw = ICoef[LogN - n]; //sin(w)

    if(inv) iw = -iw; //комплексно сопряженное.

    in = ie >> 1; //in - середина... N/2 для каждого уровня.

    //ru и iu - используемый поворотный коэффициент
    ru = 1.0F;
    iu = 0.0F;

    for(j=0; j<in; j++) {
      for(i=j; i<N; i+=ie) {
        io       = i + in; //io = i + N/2 для каждого из уровней...

        //s(2k) = s0(k) + s1(k)
        rtp      = Rdat[i]  + Rdat[io];
        itp      = Idat[i]  + Idat[io];

        //s0(k) - s1(k)
        rtq      = Rdat[i]  - Rdat[io];
        itq      = Idat[i]  - Idat[io];

        //s(2k+1) = Wkn * (s0(k) - s1(k))
        Rdat[io] = rtq * ru - itq * iu;
        Idat[io] = itq * ru + rtq * iu;

        Rdat[i]  = rtp;
        Idat[i]  = itp;
      }

      sr = ru;
      //Wk+1 = W*Wk
      ru = ru * rw - iu * iw;
      iu = iu * rw + sr * iw;
    }

    ie >>= 1;
  }
  //граф бабочка для всех уровней здесь уже завершен. дальше должна быть перестановка.

  //nn = N/2
  //bit-reversal permutation :)
  for(j=i=1; i<N; i++) {

    if(i < j) {
      //swap dat[io] and dat[in].
      io       = i - 1;
      in       = j - 1;
      rtp      = Rdat[in];
      itp      = Idat[in];
      Rdat[in] = Rdat[io];
      Idat[in] = Idat[io];
      Rdat[io] = rtp;
      Idat[io] = itp;
    }

    k = nn;

    while(k < j) {
      j   = j - k;
      k >>= 1;
    }

    j = j + k;
  }
  //перестановка завершена

  if(inv) return true;

  rw = 1.0F / N;

  for(i=0; i<N; i++) {
    Rdat[i] *= rw;
    Idat[i] *= rw;
  }

  return true;
}
