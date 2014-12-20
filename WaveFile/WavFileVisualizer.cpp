#include "WavFileVisualizer.h"
#include "Commons/Commons.h"


CWavFileVisualizer::CWavFileVisualizer(CWavFile *lpWf)
  : m_lpWf(lpWf),
    m_start_sec(0.0),
    m_end_sec(m_lpWf->RecordTimeSec()),
    m_mastab(1.0),
    m_vis_p_count(0),
    m_lppChannelsData(NULL)
{
  m_lppChannelsData = new word_t*[lpWf->Header()->fmt.options.numChannels];
  for (int i = 0; i < lpWf->Header()->fmt.options.numChannels; ++i)
    m_lppChannelsData[i] = NULL;
}

CWavFileVisualizer::~CWavFileVisualizer()
{
  FreeChannelsData();
}

void CWavFileVisualizer::FreeChannelsData()
{
  if (m_lppChannelsData) {
    for (int i = 0; i < m_lpWf->Header()->fmt.options.numChannels; ++i)
      delete [] m_lppChannelsData[i];
    delete [] m_lppChannelsData;
    m_lppChannelsData = NULL;
  }
}
//////////////////////////////////////////////////////////////////////////

int CWavFileVisualizer::RefreshChannelData()
{
  int bStart, bEnd, diff;
  bStart = m_lpWf->ByteOffsetBySec(m_start_sec);
  bEnd = m_lpWf->ByteOffsetBySec(m_end_sec);

  if (m_lpWf->BytesPerSample() == 1) {
    diff = std::abs(bEnd - bStart);
    for (int i = 0; i < m_lpWf->Header()->fmt.options.numChannels; ++i) {
      CCommons::MergeArrays<ubyte_t, word_t>(m_lpWf->Data().ubPtr + bStart, diff,
                                             m_lppChannelsData[i], m_vis_p_count);
    }
  }
  else if (m_lpWf->BytesPerSample() == 2) {
    diff = std::abs(bEnd - bStart) / 2;
    for (int i = 0; i < m_lpWf->Header()->fmt.options.numChannels; ++i) {
      CCommons::MergeArrays<word_t, word_t>(m_lpWf->Data().wPtr + bStart, diff,
                                            m_lppChannelsData[i], m_vis_p_count);
    }
  }
  else {
    return -1;
  }
  return 0;
}
//////////////////////////////////////////////////////////////////////////

int CWavFileVisualizer::RecountChannelData()
{
  FreeChannelsData();
  m_lppChannelsData = new word_t*[m_lpWf->Header()->fmt.options.numChannels];
  for (int i = 0; i < m_lpWf->Header()->fmt.options.numChannels; ++i) {
    m_lppChannelsData[i] = new word_t[m_vis_p_count];
  }
  return RefreshChannelData();
}
//////////////////////////////////////////////////////////////////////////
