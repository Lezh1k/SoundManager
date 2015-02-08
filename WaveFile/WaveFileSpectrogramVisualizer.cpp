#include <memory>
#include <assert.h>
#include "WaveFileSpectrogramVisualizer.h"
#include "WaveFile/Fourier.h"

#include <QDebug>

CWaveFileSpectrogramVisualizer::CWaveFileSpectrogramVisualizer(CWavFile *lpWf,
                                                               int channelNum,
                                                               WindowFunctions wfunc /* = WF_Rectangle*/) :
  m_lpWf(lpWf),
  m_channelNumber(channelNum),  
  m_dt(DEFAULT_DT),
  m_nDt(0),
  m_start_time(0.0),
  m_end_time(lpWf->RecordTimeSec()),
  m_rChannelData(NULL),
  m_iChannelData(NULL),
  m_rTmp(NULL),
  m_iTmp(NULL),
  m_windows(NULL),
  m_ftData(NULL)
{
  m_real_len = m_lpWf->Header()->data.header.chunkSize / m_lpWf->Header()->fmt.options.numChannels;
  m_real_len /= m_lpWf->BytesPerSample();
  m_mem_len = CFourier::NextPowerOfTwo(m_real_len);

  InitWindows(wfunc);
  InitChannelData();
  InitFFTData();
}

CWaveFileSpectrogramVisualizer::~CWaveFileSpectrogramVisualizer(void)
{
  if (m_rChannelData) delete[] m_rChannelData;
  if (m_iChannelData) delete[] m_iChannelData;

  if (m_rTmp) delete [] m_rTmp;
  if (m_iTmp) delete [] m_iTmp;

  if (m_ftData) {
    for (int i = 0; i < m_nDt; ++i) {
      delete [] m_ftData[i];
    }
    delete [] m_ftData;
  }

  if (m_windows) delete[] m_windows;
}
/////////////////////////////////////////////////////////////////////////

void CWaveFileSpectrogramVisualizer::InitChannelData(void)
{
  m_rChannelData = new double[m_mem_len];
  m_iChannelData = new double[m_mem_len];
  int step = m_lpWf->Header()->fmt.options.numChannels * m_lpWf->BytesPerSample();

  if (m_lpWf->BytesPerSample() == 1) {
    ubyte_t* start = &m_lpWf->Data().ubPtr[m_channelNumber];
    for (int i = 0; i < m_real_len; ++i, start += step)
      m_rChannelData[i] = (*start) * m_windows[i];
  }
  else if (m_lpWf->BytesPerSample() == 2) {
    word_t* start = &m_lpWf->Data().wPtr[m_channelNumber];
    for (int i = 0; i < m_real_len; ++i, start += step)
      m_rChannelData[i] = (*start) * m_windows[i];
  }

  for (int i = 0 ; i < m_real_len; ++i)
    m_iChannelData[i] = 0.0;

  for (int i = m_real_len; i < m_mem_len; ++i) {
    m_rChannelData[i] = 0.0;
    m_iChannelData[i] = 0.0;
  }
}
/////////////////////////////////////////////////////////////////////////

void CWaveFileSpectrogramVisualizer::InitWindows(WindowFunctions wfunc)
{
  assert(m_windows == NULL);
  m_windows = new double[m_real_len];
  double (*lpFunc)(double, double) = CFftWindow::GetWindowFunc(wfunc);
  for (int i = 0 ; i < m_real_len; ++i)
    m_windows[i] = lpFunc(i, m_real_len);
}
/////////////////////////////////////////////////////////////////////////

void CWaveFileSpectrogramVisualizer::InitFFTData(void)
{
  m_dt = CFourier::NextPowerOfTwo(m_dt);
  int n_fft = m_dt / 2;
  m_nDt = m_mem_len / m_dt;
  m_rTmp = new double[m_dt];
  m_iTmp = new double[m_dt];

  m_ftData = new CFtItem*[m_nDt];
  for (int i = 0; i < m_nDt; ++i) {
    m_ftData[i] = new CFtItem[n_fft];
  }

  //log2(N) = log10(N) / log10(2)
  int logN = log10((double)m_dt) / log10(2.0);
  //frequency = (i * inputFrequencty) / m_nDt
  for (int i = 0; i < m_nDt; ++i) {
    memcpy(m_rTmp, &m_rChannelData[i*m_dt], sizeof(double)*m_dt);
    memcpy(m_iTmp, &m_iChannelData[i*m_dt], sizeof(double)*m_dt);
    CFourier::FFT_d(m_rTmp, m_iTmp, m_dt, logN, false);

    double freq = 0.0;
    double freqStep = ((double)m_lpWf->Header()->fmt.options.sampleRate) / m_dt;
    for (int j = 0; j < n_fft; ++j, freq += freqStep) {
      m_ftData[i][j].amplitude = sqrt(m_rTmp[j]*m_rTmp[j] + m_iTmp[j]*m_iTmp[j]);
      m_ftData[i][j].frequency = freq;
    }
  }
}
/////////////////////////////////////////////////////////////////////////
