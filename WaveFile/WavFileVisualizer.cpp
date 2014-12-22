#include "WavFileVisualizer.h"
#include "Commons/Commons.h"


CWavFileVisualizer::CWavFileVisualizer(CWavFile *lpWf)
  : m_lpWf(lpWf),
    m_start_sec(0.0),
    m_end_sec(m_lpWf->RecordTimeSec()),
    m_vis_p_count(0),
    m_lppChannelData(NULL),
    m_lppVisChannelsData(NULL),
    m_chanelMaxVals(NULL)
{
  m_lppVisChannelsData = new word_t*[lpWf->Header()->fmt.options.numChannels];
  m_lppChannelData = new double*[lpWf->Header()->fmt.options.numChannels];
  m_chanelMaxVals = new double[lpWf->Header()->fmt.options.numChannels];

  //init visualization channel data
  for (int i = 0; i < lpWf->Header()->fmt.options.numChannels; ++i) {
    m_lppVisChannelsData[i] = NULL;
  }
  //

  //init channel data
  int len = (lpWf->Header()->data.header.chunkSize / lpWf->Header()->fmt.options.numChannels);

  if (lpWf->BytesPerSample() == 1) {

    for (int i = 0; i < lpWf->Header()->fmt.options.numChannels; ++i) {
      m_lppChannelData[i] = new double[len];      
      for (int j = 0; j < len; ++j) {
        m_lppChannelData[i][j] = lpWf->Data().ubPtr[j * lpWf->Header()->fmt.options.numChannels + i];
      }
    }
  }
  else if (lpWf->BytesPerSample() == 2) {
    len /= 2;
    for (int i = 0; i < lpWf->Header()->fmt.options.numChannels; ++i) {
      m_lppChannelData[i] = new double[len];      
      for (int j = 0; j < len; ++j) {
        m_lppChannelData[i][j] = lpWf->Data().wPtr[j * lpWf->Header()->fmt.options.numChannels + i];        
      }
    }
  }
  else {
    throw -1;
  }
  //
}

CWavFileVisualizer::~CWavFileVisualizer()
{
  FreeVisChannelsData();
  if (m_lppChannelData) {
    for (int i = 0; i < m_lpWf->Header()->fmt.options.numChannels; ++i)
      delete [] m_lppChannelData[i];
    delete [] m_lppChannelData;
    m_lppChannelData = NULL;
  }
  if (m_chanelMaxVals) {
    delete [] m_chanelMaxVals;
    m_chanelMaxVals = NULL;
  }
}

void CWavFileVisualizer::FreeVisChannelsData()
{
  if (m_lppVisChannelsData) {
    for (int i = 0; i < m_lpWf->Header()->fmt.options.numChannels; ++i)
      delete [] m_lppVisChannelsData[i];
    delete [] m_lppVisChannelsData;
    m_lppVisChannelsData = NULL;
  }
}
//////////////////////////////////////////////////////////////////////////

int CWavFileVisualizer::RefreshChannelData()
{
  int bStart, bEnd, diff;
  bStart = m_lpWf->ByteOffsetBySec(m_start_sec) / m_lpWf->Header()->fmt.options.numChannels / m_lpWf->BytesPerSample();
  bEnd = m_lpWf->ByteOffsetBySec(m_end_sec) / m_lpWf->Header()->fmt.options.numChannels / m_lpWf->BytesPerSample();
  diff = std::abs(bEnd - bStart);

  for (int i = 0; i < m_lpWf->Header()->fmt.options.numChannels; ++i) {
    CCommons::MergeArrays<double, word_t>(&m_lppChannelData[i][bStart], diff,
                                           m_lppVisChannelsData[i], m_vis_p_count);

    m_chanelMaxVals[i] = m_lppVisChannelsData[i][0];
    for (int j = 0; j < m_vis_p_count; ++j) {
      if (m_chanelMaxVals[i] < std::abs(m_lppVisChannelsData[i][j]))
        m_chanelMaxVals[i] = std::abs(m_lppVisChannelsData[i][j]);
    }
  }
  return 0;
}
//////////////////////////////////////////////////////////////////////////

int CWavFileVisualizer::RecountChannelData()
{
  FreeVisChannelsData();
  m_lppVisChannelsData = new word_t*[m_lpWf->Header()->fmt.options.numChannels];
  for (int i = 0; i < m_lpWf->Header()->fmt.options.numChannels; ++i) {
    m_lppVisChannelsData[i] = new word_t[m_vis_p_count];
  }
  return RefreshChannelData();
}
//////////////////////////////////////////////////////////////////////////
