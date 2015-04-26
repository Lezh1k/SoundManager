#include "WavFileChannelVisualizer.h"
#include "Commons/Commons.h"
#include "WaveFile/Fourier.h"

CWavFileChannelVisualizer::CWavFileChannelVisualizer(CWavFile *lpWf, int channelNum) :
  m_lpWf(lpWf),
  m_start_sec(0.0),
  m_end_sec(m_lpWf->RecordTimeSec()),
  m_visSize(0, 0),
  m_lpChannelData(NULL),
  m_lpVisChannelsData(NULL),
  m_channelMaxVal(0.0),
  m_channelNumber(channelNum),
  m_timePerPixel(0.0)
{
  //init channel data
  int len = (lpWf->Header()->data.header.chunkSize / lpWf->Header()->fmt.options.numChannels);
  len /= lpWf->BytesPerSample();
  m_lpChannelData = new double[CFourier::NextPowerOfTwo(len)];

  if (lpWf->BytesPerSample() == 1) {
    for (int i = 0, index = m_channelNumber; i < len; ++i, index+=lpWf->Header()->fmt.options.numChannels) {
      m_lpChannelData[i] = lpWf->Data().ubPtr[index];
    }
  }
  else if (lpWf->BytesPerSample() == 2) {
    for (int i = 0, index = m_channelNumber; i < len; ++i, index+=lpWf->Header()->fmt.options.numChannels) {
      m_lpChannelData[i] = lpWf->Data().wPtr[index];
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

  m_channelMaxVal = m_lpVisChannelsData[0];
  for (unsigned j = 0; j < m_visSize.width; ++j) {
    if (m_channelMaxVal < std::abs(m_lpVisChannelsData[j]))
      m_channelMaxVal = std::abs(m_lpVisChannelsData[j]);
  }

  return 0;
}
//////////////////////////////////////////////////////////////////////////

int CWavFileChannelVisualizer::RecountChannelData()
{  
  if (m_lpVisChannelsData)
    delete [] m_lpVisChannelsData;
  m_lpVisChannelsData = new word_t[m_visSize.width];
  return RefreshChannelData();
}
//////////////////////////////////////////////////////////////////////////

void CWavFileChannelVisualizer::set_time(double start_sec, double end_sec)
{
  //too many checks.
  if (m_start_sec != start_sec)
    m_start_sec = std::min(std::max(start_sec, 0.0), max_time());
  if (m_end_sec != end_sec)
    m_end_sec = std::max(0.0, std::min(end_sec, max_time()));

  ResetTimePerPixel();
  RefreshChannelData();
}
//////////////////////////////////////////////////////////////////////////

void CWavFileChannelVisualizer::set_size(unsigned int width, unsigned int height)
{
  bool recount = m_visSize.width != width;
  m_visSize.width = width;
  m_visSize.height = height;
  ResetTimePerPixel();
  if (recount) RecountChannelData();
  else RefreshChannelData();
}

void CWavFileChannelVisualizer::set_size(const CVisSize &visSize)
{
  set_size(visSize.width, visSize.height);
}
//////////////////////////////////////////////////////////////////////////

void CWavFileChannelVisualizer::ResetTimePerPixel()
{
  m_timePerPixel = (m_end_sec - m_start_sec) / m_visSize.width;
}
//////////////////////////////////////////////////////////////////////////
