#include <memory>
#include "WaveFileSpectrogramVisualizer.h"
#include "WaveFile/Fourier.h"

#include <QDebug>



CWaveFileSpectrogramVisualizer::CWaveFileSpectrogramVisualizer(CWavFile *lpWf, int channelNum) :
  m_lpWf(lpWf),
  m_channelNumber(channelNum),  
  m_dt(DEFAULT_DT), m_nDt(0),
  m_start_time(0.0),
  m_end_time(lpWf->RecordTimeSec()),
  m_rChannelData(NULL),
  m_iChannelData(NULL),
  m_r_parts(NULL),
  m_i_parts(NULL)
{
  InitChannelData();
  InitFFTParts();
}

CWaveFileSpectrogramVisualizer::~CWaveFileSpectrogramVisualizer()
{
  if (m_rChannelData) delete[] m_rChannelData;
  if (m_iChannelData) delete[] m_iChannelData;

  if (m_r_parts) {
    for (int i = 0; i < m_nDt; ++i)
      delete [] m_r_parts[i];
    delete [] m_r_parts;
  }

  if (m_i_parts) {
    for (int i = 0; i < m_nDt; ++i)
      delete [] m_r_parts[i];
    delete [] m_i_parts;
  }
}
/////////////////////////////////////////////////////////////////////////

void CWaveFileSpectrogramVisualizer::InitChannelData()
{
  m_real_len = (m_lpWf->Header()->data.header.chunkSize / m_lpWf->Header()->fmt.options.numChannels);
  m_mem_len = CFourier::NextPowerOfTwo(m_real_len);

  if (m_lpWf->BytesPerSample() == 1) {
    m_rChannelData = new double[m_mem_len];
    m_iChannelData = new double[m_mem_len];
    for (int j = 0; j < m_real_len; ++j) {
      m_rChannelData[j] = m_lpWf->Data().ubPtr[j * m_lpWf->Header()->fmt.options.numChannels + m_channelNumber];
    }
  }
  else if (m_lpWf->BytesPerSample() == 2) {
    m_mem_len /= 2; m_real_len /= 2;
    m_rChannelData = new double[m_mem_len];
    m_iChannelData = new double[m_mem_len];
    for (int j = 0; j < m_real_len; ++j) {
      m_rChannelData[j] = m_lpWf->Data().wPtr[j * m_lpWf->Header()->fmt.options.numChannels + m_channelNumber];
    }
  }
  for (int i = 0 ; i < m_real_len; ++i) m_iChannelData[i] = 0.0;

  for (unsigned j = m_real_len; j < m_mem_len; ++j) {
    m_rChannelData[j] = 0.0;
  }
}
/////////////////////////////////////////////////////////////////////////

void CWaveFileSpectrogramVisualizer::InitFFTParts()
{
  m_dt = CFourier::NextPowerOfTwo(m_lpWf->Header()->fmt.options.sampleRate / 2);
  m_nDt = m_mem_len / m_dt;
  m_r_parts = new double*[m_nDt];
  m_i_parts = new double*[m_nDt];

  //log2(N) = log10(N) / log10(2)
  int logN = log10((double)m_dt) / log10(2.0);
  //i - frequency
  for (int i = 0; i < m_nDt; ++i) {
    m_r_parts[i] = new double[m_dt];
    m_i_parts[i] = new double[m_dt];
    memcpy(m_r_parts[i], &m_rChannelData[i*m_dt], sizeof(double)*m_dt);
    memcpy(m_i_parts[i], &m_iChannelData[i*m_dt], sizeof(double)*m_dt);
    CFourier::FFT_d(m_r_parts[i], m_i_parts[i], m_dt, logN, false);
  }
}
/////////////////////////////////////////////////////////////////////////
