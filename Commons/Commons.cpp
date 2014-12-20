#include "Commons.h"

ubyte_t CCommons::m_tblBytesWithReorderedBits[] =
{
  0x00, 0X80, 0X40, 0XC0, 0X20, 0XA0, 0X60, 0XE0, 0X10, 0X90, 0X50, 0XD0, 0X30, 0XB0, 0X70, 0XF0,
  0X08, 0X88, 0X48, 0XC8, 0X28, 0XA8, 0X68, 0XE8, 0X18, 0X98, 0X58, 0XD8, 0X38, 0XB8, 0X78, 0XF8,
  0X04, 0X84, 0X44, 0XC4, 0X24, 0XA4, 0X64, 0XE4, 0X14, 0X94, 0X54, 0XD4, 0X34, 0XB4, 0X74, 0XF4,
  0X0C, 0X8C, 0X4C, 0XCC, 0X2C, 0XAC, 0X6C, 0XEC, 0X1C, 0X9C, 0X5C, 0XDC, 0X3C, 0XBC, 0X7C, 0XFC,
  0X02, 0X82, 0X42, 0XC2, 0X22, 0XA2, 0X62, 0XE2, 0X12, 0X92, 0X52, 0XD2, 0X32, 0XB2, 0X72, 0XF2,
  0X0A, 0X8A, 0X4A, 0XCA, 0X2A, 0XAA, 0X6A, 0XEA, 0X1A, 0X9A, 0X5A, 0XDA, 0X3A, 0XBA, 0X7A, 0XFA,
  0X06, 0X86, 0X46, 0XC6, 0X26, 0XA6, 0X66, 0XE6, 0X16, 0X96, 0X56, 0XD6, 0X36, 0XB6, 0X76, 0XF6,
  0X0E, 0X8E, 0X4E, 0XCE, 0X2E, 0XAE, 0X6E, 0XEE, 0X1E, 0X9E, 0X5E, 0XDE, 0X3E, 0XBE, 0X7E, 0XFE,
  0X01, 0X81, 0X41, 0XC1, 0X21, 0XA1, 0X61, 0XE1, 0X11, 0X91, 0X51, 0XD1, 0X31, 0XB1, 0X71, 0XF1,
  0X09, 0X89, 0X49, 0XC9, 0X29, 0XA9, 0X69, 0XE9, 0X19, 0X99, 0X59, 0XD9, 0X39, 0XB9, 0X79, 0XF9,
  0X05, 0X85, 0X45, 0XC5, 0X25, 0XA5, 0X65, 0XE5, 0X15, 0X95, 0X55, 0XD5, 0X35, 0XB5, 0X75, 0XF5,
  0X0D, 0X8D, 0X4D, 0XCD, 0X2D, 0XAD, 0X6D, 0XED, 0X1D, 0X9D, 0X5D, 0XDD, 0X3D, 0XBD, 0X7D, 0XFD,
  0X03, 0X83, 0X43, 0XC3, 0X23, 0XA3, 0X63, 0XE3, 0X13, 0X93, 0X53, 0XD3, 0X33, 0XB3, 0X73, 0XF3,
  0X0B, 0X8B, 0X4B, 0XCB, 0X2B, 0XAB, 0X6B, 0XEB, 0X1B, 0X9B, 0X5B, 0XDB, 0X3B, 0XBB, 0X7B, 0XFB,
  0X07, 0X87, 0X47, 0XC7, 0X27, 0XA7, 0X67, 0XE7, 0X17, 0X97, 0X57, 0XD7, 0X37, 0XB7, 0X77, 0XF7,
  0X0F, 0X8F, 0X4F, 0XCF, 0X2F, 0XAF, 0X6F, 0XEF, 0X1F, 0X9F, 0X5F, 0XDF, 0X3F, 0XBF, 0X7F, 0XFF
};
//////////////////////////////////////////////////////////////////////////

ubyte_t CCommons::GetByteWithReorderedBits( ubyte_t src ){
  return m_tblBytesWithReorderedBits[src];
}
//////////////////////////////////////////////////////////////////////////

int CCommons::ReverseBits( unsigned int n, int lg_n ){
  n = ((n & 0x55555555) << 1) |
      ((n >> 1) & 0x55555555);

  n = ((n & 0x33333333) << 2) |
      ((n >> 2) & 0x33333333);

  n = ((n & 0x0f0f0f0f) << 4) |
      ((n >> 4) & 0x0f0f0f0f);

  n = (n << 24) |
      (((n & 0xff00) << 8) | ((n >> 8) & 0xff00)) |
      (n>>24);
  
  return n >> (32 - lg_n);
}
//////////////////////////////////////////////////////////////////////////
