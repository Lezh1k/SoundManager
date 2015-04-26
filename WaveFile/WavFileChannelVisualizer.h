#ifndef WAVFILEVISUALIZER_H
#define WAVFILEVISUALIZER_H

#include "WaveFile.h"
#include "Commons/Commons.h"


class CWavFileChannelVisualizer {

private:
  CWavFile* m_lpWf;  
  double m_start_sec;
  double m_end_sec;  
  CVisSize m_visSize;

  double *m_lpChannelData;
  word_t *m_lpVisChannelsData; //quantizied
  double m_channelMaxVal;  //abs(val) . to count mastab
  int m_channelNumber;
  double m_timePerPixel;

  void ResetTimePerPixel(void);

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

  unsigned int vis_width(void) const {return m_visSize.width;}
  unsigned int vis_height(void) const {return m_visSize.height;}

  double time_per_pixel() const {return m_timePerPixel;}

  word_t *ChannelsData() const {return m_lpVisChannelsData;}
  double ChannelMax() const {return m_channelMaxVal;}

  double min_time() const {return 0.0;}
  double max_time() const {return m_lpWf->RecordTimeSec();}
};

#endif // WAVFILEVISUALIZER_H
