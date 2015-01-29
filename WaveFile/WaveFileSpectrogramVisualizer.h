#ifndef CWAVEFILESPECTROGRAMVISUALIZER_H
#define CWAVEFILESPECTROGRAMVISUALIZER_H

#include "Commons/Commons.h"
#include "WaveFile/WaveFile.h"

class CWaveFileSpectrogramVisualizer
{
private:
  static const int DEFAULT_DT = 0x100;

  CWavFile* m_lpWf;
  int m_channelNumber;

  int m_dt;
  int m_nDt;

  double m_start_time;
  double m_end_time;

  double* m_rChannelData;
  double* m_iChannelData;

  double** m_r_parts;
  double** m_i_parts;

  int m_real_len; //len of data
  int m_mem_len;
  /***********************************/

  void InitChannelData();
  void InitFFTParts();

public:
  explicit CWaveFileSpectrogramVisualizer(CWavFile* lpWf, int channelNum);
  ~CWaveFileSpectrogramVisualizer();  

  int PartsCount(void)  const {return m_nDt;}
  int PartElemCount(void) const {return m_dt;}
  double** RParts(void) const {return m_r_parts;}
  double** IParts(void) const {return m_i_parts;}
};

#endif // CWAVEFILESPECTROGRAMVISUALIZER_H
