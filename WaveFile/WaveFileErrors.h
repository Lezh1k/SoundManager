#ifndef WAVE_FILE_ERRORS_H
#define WAVE_FILE_ERRORS_H

typedef enum WaveFileErrors {
  WFE_SUCCESS         = 0,
  WFE_NOT_INITIALIZED = 1,
  WFE_FOPEN_ERR       = 2,
  WFE_RIFF_NOT_FOUND  = 3,
  WFE_WAVE_NOT_FOUND  = 4,
  WFE_FREAD_ERROR     = 5,
  WFE_FSEEK_ERROR     = 6,
  WFE_OTHER = 0xffffffff
} WaveFileErrors;

#endif