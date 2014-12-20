#ifndef WAVFILEVISUALIZER_H
#define WAVFILEVISUALIZER_H

#include "WaveFile.h"
#include "Commons/Commons.h"

class CWavFileVisualizer {

private:
  static const double MIN_MASTAB  = 0.00001;
  static const double MAX_MASTAB  = 10000;

  CWavFile* m_lpWf;  
  double m_start_sec;
  double m_end_sec;
  double m_mastab;
  unsigned int m_vis_p_count; //visualization points count. (paint window width in pixels or another points)

  double **m_lppChannelData;
  word_t **m_lppVisChannelsData; //quantizied

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

  double mastab() const {return m_mastab;}
  void set_mastab(double mastab) {
    m_mastab = mastab;
    if (mastab > MAX_MASTAB) m_mastab = MAX_MASTAB;
    if (mastab < MIN_MASTAB) m_mastab = MIN_MASTAB;
  }

  word_t **ChannelsData() const{ return m_lppVisChannelsData;}
};

#endif // WAVFILEVISUALIZER_H
