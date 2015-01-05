#ifndef COMMONS_H
#define COMMONS_H

#define UNUSED_ARG(x) ((void)x)

typedef unsigned char             ubyte_t;
typedef unsigned short            uword_t;
typedef unsigned int              udword_t;
typedef unsigned long             uqword_t; //for 64-bit compiler

typedef char       byte_t;
typedef short      word_t;
typedef int        dword_t;
typedef long       qword_t;

#ifndef NULL
#define NULL ((void*)0)
#endif

#include <stdio.h>

class CCommons {
private:
  CCommons(void);
  ~CCommons(void);

  static CCommons m_instance;
  static ubyte_t m_tblBytesWithReorderedBits[];

public:

  static inline ubyte_t GetByteWithReorderedBits(ubyte_t src);
  static int ReverseBits(unsigned int n, int lg_n);

  static inline int RoundUpToNextN(int val, int N) { return (val + N-1) & -N;}

  template<class T> static void PrintBinary(T src) {
    int nBits = sizeof(T)*8;
    char *tmp = new char[nBits];
    for (int i = 0; i < nBits; i++, src>>=1)
      tmp[i] = src&1;
    --nBits;
    for (nBits; nBits >= 0; --nBits)
      printf("%d", tmp[nBits]);
    delete[] tmp;
  }
  //////////////////////////////////////////////////////////////////////////

  template<class TSrc, class TDst> static void MergeArrays(register TSrc *lpSrc,
                                                           register int src_len,
                                                           register TDst *lpDst,
                                                           register int dst_len)
  {
    register float coeff = (float)src_len / (float)dst_len;
    register float tmp = coeff;
    register int nTmp, i;

    while (--dst_len >= 0) {
      while (tmp < 1.0 && dst_len > 0) {
        lpDst[--dst_len] = 0.0;
        tmp+=coeff;
      }
      nTmp = (int)tmp;

      double val = 0.0;
      for (i = 0; i < nTmp; ++i) {
        val += lpSrc[--src_len];
      }
      lpDst[dst_len] = (TDst)(val / nTmp);

      tmp -= nTmp - coeff;
    }
  }
  //////////////////////////////////////////////////////////////////////////
};

#endif
