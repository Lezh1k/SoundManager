#ifndef CWAVEFILESPECTROGRAMVISUALIZER_H
#define CWAVEFILESPECTROGRAMVISUALIZER_H

#include "Commons/Commons.h"
#include "WaveFile/WaveFile.h"
#include "WaveFile/FFTWindow.h"
#include "WaveFile/Fourier.h"

class CWaveFileSpectrogramVisualizer
{
private:
  static const int DEFAULT_DT = 0x1000;

  CWavFile* m_lpWf;
  int m_channelNumber;

  int m_dt;
  int m_nDt;

  double m_start_time;
  double m_end_time;

  double* m_rChannelData;
  double* m_iChannelData;

  double* m_rTmp;
  double* m_iTmp;

  double * m_windows;
  CFtItem** m_ftData;

  int m_real_len; //len of data
  int m_mem_len;
  /***********************************/

  void InitChannelData(void);
  void InitWindows(WindowFunctions wfunc);
  void InitFFTData(void);

public:
  explicit CWaveFileSpectrogramVisualizer(CWavFile* lpWf, int channelNum, WindowFunctions wfunc = WF_Rectangle);
  ~CWaveFileSpectrogramVisualizer();  

  int PartsCount(void)  const {return m_nDt;}
  int PartElemCount(void) const {return m_dt;}  

  CFtItem ** FtData(void) const {return m_ftData;}
};

#endif // CWAVEFILESPECTROGRAMVISUALIZER_H
