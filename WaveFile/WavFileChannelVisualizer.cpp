#include "WavFileChannelVisualizer.h"
#include "Commons/Commons.h"
#include "WaveFile/Fourier.h"


CWavFileChannelVisualizer::CWavFileChannelVisualizer(CWavFile *lpWf, int channelNum)
  : m_lpWf(lpWf),
    m_start_sec(0.0),
    m_end_sec(m_lpWf->RecordTimeSec()),
    m_visSize(0, 0),
    m_lpChannelData(NULL),
    m_lpVisChannelsData(NULL),
    m_chanelMaxVal(0.0),
    m_channelNumber(channelNum)
{
  //init channel data
  int len = (lpWf->Header()->data.header.chunkSize / lpWf->Header()->fmt.options.numChannels);

  if (lpWf->BytesPerSample() == 1) {
    m_lpChannelData = new double[CFourier::NextPowerOfTwo(len)];
    for (int j = 0; j < len; ++j) {
      m_lpChannelData[j] = lpWf->Data().ubPtr[j * lpWf->Header()->fmt.options.numChannels + m_channelNumber];
    }
  }
  else if (lpWf->BytesPerSample() == 2) {
    len /= 2;
    m_lpChannelData = new double[CFourier::NextPowerOfTwo(len)];
    for (int j = 0; j < len; ++j) {
      m_lpChannelData[j] = lpWf->Data().wPtr[j * lpWf->Header()->fmt.options.numChannels + m_channelNumber];
    }
  }
  //
  for (unsigned j = len; j < CFourier::NextPowerOfTwo(len); ++j) {
    m_lpChannelData[j] = 0.0;
  }
}

CWavFileChannelVisualizer::~CWavFileChannelVisualizer()
{
  //free all vis channels data
  if (m_lpVisChannelsData) {
    delete [] m_lpVisChannelsData;
    m_lpVisChannelsData = NULL;
  }
  //free all channels data
  if (m_lpChannelData) {
    delete [] m_lpChannelData;
    m_lpChannelData = NULL;
  }
}
//////////////////////////////////////////////////////////////////////////

int CWavFileChannelVisualizer::RefreshChannelData()
{
  int bStart, bEnd, diff;
  double coeff = 1.0 / (m_lpWf->Header()->fmt.options.numChannels * m_lpWf->BytesPerSample());
  bStart = m_lpWf->ByteOffsetBySec(m_start_sec) * coeff;
  bEnd = m_lpWf->ByteOffsetBySec(m_end_sec) * coeff;
  diff = std::abs(bEnd - bStart);

  CCommons::MergeArrays<double, word_t>(&m_lpChannelData[bStart], diff,
                                        m_lpVisChannelsData, m_visSize.width);

  m_chanelMaxVal = m_lpVisChannelsData[0];
  for (unsigned j = 0; j < m_visSize.width; ++j) {
    if (m_chanelMaxVal < std::abs(m_lpVisChannelsData[j]))
      m_chanelMaxVal = std::abs(m_lpVisChannelsData[j]);
  }
  return 0;
}
//////////////////////////////////////////////////////////////////////////
int CWavFileChannelVisualizer::RecountChannelData()
{  
  if (m_lpVisChannelsData != NULL) {
    delete [] m_lpVisChannelsData;
  }
  m_lpVisChannelsData = new word_t[m_visSize.width];
  return RefreshChannelData();
}
//////////////////////////////////////////////////////////////////////////

void CWavFileChannelVisualizer::set_time(double start_sec, double end_sec)
{
  if (m_start_sec != start_sec) {
    m_start_sec = start_sec;
    if (start_sec < 0.0) m_start_sec = 0.0;
    if (start_sec > m_lpWf->RecordTimeSec()) m_start_sec = m_lpWf->RecordTimeSec();
  }

  if (m_end_sec != end_sec) {
    m_end_sec = end_sec;
    if (end_sec < m_start_sec) m_end_sec = m_start_sec;
    if (end_sec > m_lpWf->RecordTimeSec()) m_end_sec = m_lpWf->RecordTimeSec();
  }

  RefreshChannelData();
}
//////////////////////////////////////////////////////////////////////////

void CWavFileChannelVisualizer::set_size(unsigned int width, unsigned int height)
{
  bool recount = m_visSize.width != width;
  m_visSize.width = width;
  m_visSize.height = height;
  if (recount) RecountChannelData();
  else RefreshChannelData();
}

void CWavFileChannelVisualizer::set_size(const CVisSize &visSize)
{
  bool recount = m_visSize.width != visSize.width;
  m_visSize = visSize;
  if (recount) RecountChannelData();
  else RefreshChannelData();
}
//////////////////////////////////////////////////////////////////////////
