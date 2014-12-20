#ifndef FILEWRAPPER_H
#define FILEWRAPPER_H

#include <stdio.h>
#include <stdarg.h>

class CFileWrapper {
private:
  FILE *m_file;
  CFileWrapper(void);
  CFileWrapper(const CFileWrapper&);
  void operator=(const CFileWrapper&);

public:
  CFileWrapper(const char* fileName, const char* flags) { m_file = fopen(fileName, flags);}
  ~CFileWrapper(void) { if (IsValid()) fclose(m_file);}

  bool IsValid(void) const {return m_file != NULL;}
  size_t FRead(void* buff, size_t elemSize, size_t count) const { return fread(buff, elemSize, count, m_file);}
  size_t FWrite(void* str, size_t size, size_t count) const {return fwrite(str, size, count, m_file);}
  size_t FSeek(long offset, int origin) const {return fseek(m_file, offset, origin);}
  size_t FEof(void) const { return feof(m_file);}

  int FPrintf (const char* format, ...) {
    va_list args;
    va_start(args, format);
    int result = vfprintf(m_file, format, args);
    va_end(args);
    return result;
  }

};
#endif // FILEWRAPPER_H
