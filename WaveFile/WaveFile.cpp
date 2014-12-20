#include <stdio.h>
#include <string.h>
#include <memory>
#include <math.h>

#include "WaveFile.h"
#include "WaveFileErrors.h"

CWavFile::CWavFile( const char* fileName , bool justInfo /*= false*/): 
  m_lastError(WFE_NOT_INITIALIZED), m_isInfoFile(justInfo)
{
  memset(&m_lpDataU, 0, sizeof(m_lpDataU));
  memset(&m_waveHeader, 0, sizeof(m_waveHeader));
  ReadFromFile(fileName);
}

CWavFile::~CWavFile( void )
{
  if (m_lpDataU.ubPtr != NULL)
    delete[] m_lpDataU.ubPtr;
}
//////////////////////////////////////////////////////////////////////////

int CWavFile::InternalReadFromFile(const char* filePath, CWavFile *wf )
{

  CFileWrapper fw(filePath, "rb");
  if (!fw.IsValid())
    return WFE_FOPEN_ERR;

  //temp function result
  int tfr = WFE_SUCCESS;
  
  tfr = (int) fw.FRead(&wf->m_waveHeader.riff, sizeof(RiffChunk), 1);
  if (tfr != 1)
    return WFE_FREAD_ERROR;

  if (wf->m_waveHeader.riff.header.chunIdU.dwId != CT_RIFF)
    return WFE_RIFF_NOT_FOUND;

  if (wf->m_waveHeader.riff.format.dwId != CT_WAVE)
    return WFE_WAVE_NOT_FOUND;

  ChunkHeader nextHdr;
  //read chunks :)
  for(;;){
    tfr = (int) fw.FRead(&nextHdr, sizeof(ChunkHeader), 1);
    
    if (tfr != 1) {
      if (fw.FEof()) break;
      return WFE_FREAD_ERROR;
    }
    
    switch(nextHdr.chunIdU.dwId){
    case CT_fmt:
      tfr = ReadFmtChunk(fw, wf, &nextHdr);
      if (tfr != WFE_SUCCESS)
        return tfr;
      break;
    case CT_data:
      tfr = ReadDataChunk(fw, wf, &nextHdr);
      if (tfr != WFE_SUCCESS)
        return tfr;
      break;
    default:
      if (fw.FSeek(nextHdr.chunkSize, SEEK_CUR)!=0)
        return WFE_FSEEK_ERROR;
    }
  }
  
  wf->m_time = wf->m_waveHeader.data.header.chunkSize /
      (double)wf->m_waveHeader.fmt.options.byteRate;
  wf->m_bytesPerSample = wf->m_waveHeader.fmt.options.bitsPerSample / 8;
  return WFE_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////

int CWavFile::ReadFmtChunk(const CFileWrapper& fw, CWavFile *wf, const ChunkHeader* lpHdr )
{
  size_t rbc = 0;
  memcpy(&wf->m_waveHeader.fmt.header, lpHdr, sizeof(ChunkHeader));
  rbc = fw.FRead(&wf->m_waveHeader.fmt.options, sizeof(FmtOptionsChunk), 1);
  if (rbc != 1)
    return WFE_FREAD_ERROR;

  int extSize = lpHdr->chunkSize - sizeof(FmtOptionsChunk);
  if (extSize == 0) return WFE_SUCCESS;

  rbc = fw.FRead(&wf->m_waveHeader.fmt.fmtExtensionChunk, extSize, 1);
  if (rbc != 1)
    return WFE_FREAD_ERROR;

  return WFE_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////

int CWavFile::ReadDataChunk(const CFileWrapper& fw, CWavFile *wf, const ChunkHeader* lpHdr )
{
  size_t rbc = 0;
  memcpy(&wf->m_waveHeader.data.header, lpHdr, sizeof(ChunkHeader));
  
  if (!wf->m_isInfoFile){
    try {
      wf->m_lpDataU.ubPtr = new ubyte_t[wf->m_waveHeader.data.header.chunkSize];
    }
    catch(...){
      return WFE_FREAD_ERROR;
    }
    rbc = fw.FRead(wf->m_lpDataU.ubPtr, wf->m_waveHeader.data.header.chunkSize, 1);
    if (rbc != 1)
      return WFE_FREAD_ERROR;
  }
  else {
    if (fw.FSeek(wf->m_waveHeader.data.header.chunkSize, SEEK_CUR)!=0)
      return WFE_FSEEK_ERROR;
  }

  return WFE_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////

void CWavFile::ReadFromFile( const char* fileName )
{
  m_lastError = InternalReadFromFile(fileName, this);
}
//////////////////////////////////////////////////////////////////////////

int CWavFile::ByteOffsetBySec( double sec ) const
{
  if (sec > m_time)
    return INVALID_DATA_OFFSET;

  return trunc(sec*m_waveHeader.fmt.options.sampleRate) *
      (m_waveHeader.fmt.options.bitsPerSample/8);
}
//////////////////////////////////////////////////////////////////////////
