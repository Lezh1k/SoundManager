#ifndef WAVFILEVISUALIZER_H
#define WAVFILEVISUALIZER_H

#include "WaveFile.h"
#include "Commons/Commons.h"

typedef struct CVisSize
{
  unsigned int width, height;
  CVisSize(unsigned int w, unsigned int h) : width(w), height(h){}
}CVisSize;

class CWavFileChannelVisualizer {

private:
  CWavFile* m_lpWf;  
  double m_start_sec;
  double m_end_sec;  
  CVisSize m_visSize;

  double *m_lpChannelData;
  word_t *m_lpVisChannelsData; //quantizied
  double m_chanelMaxVal;  //abs(val) . to count mastab
  int m_channelNumber;

public:  
  CWavFileChannelVisualizer(CWavFile *lpWf, int channelNum);
  ~CWavFileChannelVisualizer(void);

  //RefreshChannelData. without memory reallocation
  int RefreshChannelData(void);
  //RefreshChannelData. with memory reallocation
  int RecountChannelData(void);

  //////////////////////////////////////////////////////////////////////////
  double start_sec() const {return m_start_sec;}
  double end_sec() const {return m_end_sec;}
  void set_time(double start_sec, double end_sec);

  void set_size(unsigned int width, unsigned int height);
  void set_size(const CVisSize& visSize);

  word_t *ChannelsData() const {return m_lpVisChannelsData;}
  double ChannelMax() const {return m_chanelMaxVal;}
};

#endif // WAVFILEVISUALIZER_H
