#ifndef WAVE_FILE_H
#define WAVE_FILE_H

#include <vector>
#include <complex>

#include "Commons/Commons.h"
#include "Commons/FileWrapper.h"

typedef enum CompressionCodes {
  WF_NONE           = 0x0000,
  WF_PCM            = 0x0001,
  WF_MS_ADPCM       = 0x0002,
  WF_IEEE_FLOAT     = 0x0003,
  WF_ALAW           = 0x0006,
  WF_MULAW          = 0x0007,
  WF_IDA_ADPCM      = 0x0011,
  WF_ITU_723_ADPCM  = 0x0016,
  WF_GSM            = 0x0031,
  WF_ITU_721_ADPCM  = 0x0040,
  WF_MPEG           = 0x0050,
  WF_EXTENSIBLE     = 0xfffe,
  WF_EXPERIMENTAL   = 0xffff
} CompressionCodes;
///////////////////////////////

//little-endian
//for optimizing by switch
typedef enum ChunkTypes{
  CT_cue  = 0x20657563,
  CT_fmt  = 0x20746d66,
  CT_WAVE = 0x45564157,
  CT_RIFF = 0x46464952,
  CT_data = 0x61746164,
  CT_note = 0x65746f6e,
  CT_labl = 0x6c62616c,
  CT_smpl = 0x6c706d73,
  CT_adtl = 0x6c746461,
  CT_wavl = 0x6c766177,
  CT_fact = 0x74636166,
  CT_slnt = 0x746e6c73,
  CT_list = 0x7473696c,
  CT_plst = 0x74736c70,
  CT_inst = 0x74736e69,
  CT_ltxt = 0x7478746c
}ChunkTypes;
///////////////////////////////

#pragma pack(push)
#pragma pack(1)
typedef union ChunkIdU{
  ubyte_t bId[4];
  udword_t dwId;
} ChunkIdU;
///////////////////////////////

typedef struct ChunkHeader {
  ChunkIdU  chunIdU;
  udword_t  chunkSize;
} ChunkHeader;
///////////////////////////////

typedef struct RiffChunk {
  ChunkHeader      header;             //Contains the letters "RIFF" in ASCII form  big-endian                                   
  ChunkIdU         format;             //Contains the letters "WAVE"
} RiffChunk;
///////////////////////////////

typedef struct FmtExtensionChunk {
  uword_t            extSize;
  uword_t            validBitsPerSample; //Number of valid bits
  udword_t           channelMask;        //Speaker position mask
  udword_t           subFormatGuid[4];   //GUID, including the data format code
} FmtExtensionChunk;
///////////////////////////////

typedef struct FmtOptionsChunk {
  uword_t            audioFormat;        //PCM = 1 (i.e. Linear quantization) Values other than 1 indicate some form of compression.
  uword_t            numChannels;        //Mono = 1, Stereo = 2, etc.
  udword_t           sampleRate;         //8000, 44100, etc.
  udword_t           byteRate;           //== SampleRate * NumChannels * BitsPerSample/8
  uword_t            blockAlign;         //== NumChannels * BitsPerSample/8
  uword_t            bitsPerSample; 
} FmtOptionsChunk;
///////////////////////////////

typedef struct FmtChunk {
  ChunkHeader       header;           //contains "fmt " big-endian and chunkSize.
  FmtOptionsChunk   options;
  FmtExtensionChunk fmtExtensionChunk;
} FmtChunk;
///////////////////////////////

typedef struct FactChunk {
  ChunkHeader     header;             //Contains the letters "fact " big-endian
  udword_t        sampleLength;       //Number of samples (per channel)
} FactChunk;
///////////////////////////////

typedef struct DataChunk {
  ChunkHeader    header;             //Contains the letters "data" big-endian
  //chunkSize = NumSamples * NumChannels * BitsPerSample/8
} DataChunk;
///////////////////////////////

//wave header with necessary for sound manager fields
typedef struct WaveHeader{
  RiffChunk riff;
  FmtChunk fmt;
  DataChunk data;
}WaveHeader;

//unsigned bytes or words in data :)
typedef union WaveDataU {
  ubyte_t* ubPtr;
  word_t* wPtr;
}WaveDataU;

#pragma pack(pop)

class CWavFile
{
private:

  WaveHeader m_waveHeader;
  WaveDataU m_lpDataU;

  int m_lastError;
  double m_time;
  bool m_isInfoFile;
  int m_bytesPerSample;

  static int ReadDataChunk( const CFileWrapper& fm, CWavFile* wf, const ChunkHeader* lpHdr ) ;
  static int ReadFmtChunk( const CFileWrapper& fm, CWavFile* wf, const ChunkHeader* lpHdr ) ;
  static int InternalReadFromFile(const char* filePath, CWavFile* wavFile) ;

  void ReadFromFile(const char* fileName);

  //
  CWavFile(void);

public:
  static const int INVALID_DATA_OFFSET = -1;

  explicit CWavFile(const char* fileName, bool justInfo = false);
  ~CWavFile(void);
  
  int LastError(void) const {return m_lastError;}
  double RecordTimeSec(void) const {return m_time;}
  int ByteOffsetBySec(double sec) const;
  int BytesPerSample(void) const {return m_bytesPerSample;}

  const WaveHeader* Header(void) {return &m_waveHeader;}
  WaveDataU Data(void) const {return m_lpDataU;}

}; //CWavFile

#endif
