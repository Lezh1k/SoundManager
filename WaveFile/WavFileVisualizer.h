#ifndef WAVFILEVISUALIZER_H
#define WAVFILEVISUALIZER_H

#include "WaveFile.h"
#include "Commons/Commons.h"

class CWavFileVisualizer {

private:
  CWavFile* m_lpWf;  
  double m_start_sec;
  double m_end_sec;

  unsigned int m_vis_p_count; //visualization points count. (paint window width in pixels or another points)

  double **m_lppChannelData;
  word_t **m_lppVisChannelsData; //quantizied  
  double *m_chanelMaxVals;  //abs(val) . to count mastab

  void FreeVisChannelsData();

public:  
  explicit CWavFileVisualizer(CWavFile *lpWf);
  ~CWavFileVisualizer(void);

  //RefreshChannelData. without memory reallocation
  int RefreshChannelData(void);
  //RefreshChannelData. with memory reallocation
  int RecountChannelData(void);

  //////////////////////////////////////////////////////////////////////////
  double start_sec() const {return m_start_sec;}
  void set_start_sec(double start_sec) {
    m_start_sec = start_sec;
    if (start_sec < 0.0) m_start_sec = 0.0;
    if (start_sec > m_lpWf->RecordTimeSec()) m_start_sec = m_lpWf->RecordTimeSec();
  }

  double end_sec() const {return m_end_sec;}
  void set_end_sec(double end_sec) {
    m_end_sec = end_sec;
    if (end_sec < m_start_sec) m_end_sec = m_start_sec;
    if (end_sec > m_lpWf->RecordTimeSec()) m_end_sec = m_lpWf->RecordTimeSec();
  }

  unsigned int vis_p_count() const {return m_vis_p_count;}
  void set_vis_p_count(int vis_p_count) {m_vis_p_count = vis_p_count;}

  word_t **ChannelsData() const{ return m_lppVisChannelsData;}
  double ChannelMax(int i) const {return m_chanelMaxVals[i];}
};

#endif // WAVFILEVISUALIZER_H
