/* MD5 for GNU make

This file is part of GNU Make.

GNU Make is free software; you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation; either version 3 of the License, or (at your option) any later
version.

GNU Make is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <http://www.gnu.org/licenses/>.

Orignal C++ code from Aaron Ucko / NCBI(National Center for Biotechnology Information) /Public Domain
Converted back to C by Pierre Lindenbaum

*/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "makeint.h"
#include "md5.h"



#ifdef __BIG_ENDIAN__
static void s_ByteReverse(unsigned char* buf, size_t longs)
  {
    uint32_t t;
    do {
        t = (uint32_t ) ((unsigned) buf[3] << 8 | buf[2]) << 16 |
          ((unsigned) buf[1] << 8 | buf[0]);
        *((uint32_t*)(buf)) = t;
        buf += 4;
    } while (--longs);
  }
#endif



// The four core functions - F1 is optimized somewhat

// #define F1(x, y, z) (x & y | ~x & z)
#define F1(x, y, z) (z ^ (x & (y ^ z)))
#define F2(x, y, z) ((z & x) | (~z & y))
#define F3(x, y, z) (x ^ (y ^ z))
#define F4(x, y, z) (y ^ (x | ~z))

// This is the central step in the MD5 algorithm.
#define MD5STEP(f, w, x, y, z, data, s) \
        ( w += f(x, y, z) + data,  w = w<<s | w>>(32-s),  w += x )

// The core of the MD5 algorithm, this alters an existing MD5 hash to
// reflect the addition of 16 longwords of new data.  MD5Update blocks
// the data and converts bytes into longwords for this routine.
static
void CMD5Transform(CMD5* ptr)
{
  uint32_t  a, b, c, d;
  uint32_t* inw = (uint32_t*)(ptr->m_In);

  a = ptr->m_Buf[0];
  b = ptr->m_Buf[1];
  c = ptr->m_Buf[2];
  d = ptr->m_Buf[3];

  MD5STEP(F1, a, b, c, d, inw[0]  + 0xd76aa478,  7);
  MD5STEP(F1, d, a, b, c, inw[1]  + 0xe8c7b756, 12);
  MD5STEP(F1, c, d, a, b, inw[2]  + 0x242070db, 17);
  MD5STEP(F1, b, c, d, a, inw[3]  + 0xc1bdceee, 22);
  MD5STEP(F1, a, b, c, d, inw[4]  + 0xf57c0faf,  7);
  MD5STEP(F1, d, a, b, c, inw[5]  + 0x4787c62a, 12);
  MD5STEP(F1, c, d, a, b, inw[6]  + 0xa8304613, 17);
  MD5STEP(F1, b, c, d, a, inw[7]  + 0xfd469501, 22);
  MD5STEP(F1, a, b, c, d, inw[8]  + 0x698098d8,  7);
  MD5STEP(F1, d, a, b, c, inw[9]  + 0x8b44f7af, 12);
  MD5STEP(F1, c, d, a, b, inw[10] + 0xffff5bb1, 17);
  MD5STEP(F1, b, c, d, a, inw[11] + 0x895cd7be, 22);
  MD5STEP(F1, a, b, c, d, inw[12] + 0x6b901122,  7);
  MD5STEP(F1, d, a, b, c, inw[13] + 0xfd987193, 12);
  MD5STEP(F1, c, d, a, b, inw[14] + 0xa679438e, 17);
  MD5STEP(F1, b, c, d, a, inw[15] + 0x49b40821, 22);

  MD5STEP(F2, a, b, c, d, inw[1]  + 0xf61e2562,  5);
  MD5STEP(F2, d, a, b, c, inw[6]  + 0xc040b340,  9);
  MD5STEP(F2, c, d, a, b, inw[11] + 0x265e5a51, 14);
  MD5STEP(F2, b, c, d, a, inw[0]  + 0xe9b6c7aa, 20);
  MD5STEP(F2, a, b, c, d, inw[5]  + 0xd62f105d,  5);
  MD5STEP(F2, d, a, b, c, inw[10] + 0x02441453,  9);
  MD5STEP(F2, c, d, a, b, inw[15] + 0xd8a1e681, 14);
  MD5STEP(F2, b, c, d, a, inw[4]  + 0xe7d3fbc8, 20);
  MD5STEP(F2, a, b, c, d, inw[9]  + 0x21e1cde6,  5);
  MD5STEP(F2, d, a, b, c, inw[14] + 0xc33707d6,  9);
  MD5STEP(F2, c, d, a, b, inw[3]  + 0xf4d50d87, 14);
  MD5STEP(F2, b, c, d, a, inw[8]  + 0x455a14ed, 20);
  MD5STEP(F2, a, b, c, d, inw[13] + 0xa9e3e905,  5);
  MD5STEP(F2, d, a, b, c, inw[2]  + 0xfcefa3f8,  9);
  MD5STEP(F2, c, d, a, b, inw[7]  + 0x676f02d9, 14);
  MD5STEP(F2, b, c, d, a, inw[12] + 0x8d2a4c8a, 20);

  MD5STEP(F3, a, b, c, d, inw[5]  + 0xfffa3942,  4);
  MD5STEP(F3, d, a, b, c, inw[8]  + 0x8771f681, 11);
  MD5STEP(F3, c, d, a, b, inw[11] + 0x6d9d6122, 16);
  MD5STEP(F3, b, c, d, a, inw[14] + 0xfde5380c, 23);
  MD5STEP(F3, a, b, c, d, inw[1]  + 0xa4beea44,  4);
  MD5STEP(F3, d, a, b, c, inw[4]  + 0x4bdecfa9, 11);
  MD5STEP(F3, c, d, a, b, inw[7]  + 0xf6bb4b60, 16);
  MD5STEP(F3, b, c, d, a, inw[10] + 0xbebfbc70, 23);
  MD5STEP(F3, a, b, c, d, inw[13] + 0x289b7ec6,  4);
  MD5STEP(F3, d, a, b, c, inw[0]  + 0xeaa127fa, 11);
  MD5STEP(F3, c, d, a, b, inw[3]  + 0xd4ef3085, 16);
  MD5STEP(F3, b, c, d, a, inw[6]  + 0x04881d05, 23);
  MD5STEP(F3, a, b, c, d, inw[9]  + 0xd9d4d039,  4);
  MD5STEP(F3, d, a, b, c, inw[12] + 0xe6db99e5, 11);
  MD5STEP(F3, c, d, a, b, inw[15] + 0x1fa27cf8, 16);
  MD5STEP(F3, b, c, d, a, inw[2]  + 0xc4ac5665, 23);

  MD5STEP(F4, a, b, c, d, inw[0]  + 0xf4292244,  6);
  MD5STEP(F4, d, a, b, c, inw[7]  + 0x432aff97, 10);
  MD5STEP(F4, c, d, a, b, inw[14] + 0xab9423a7, 15);
  MD5STEP(F4, b, c, d, a, inw[5]  + 0xfc93a039, 21);
  MD5STEP(F4, a, b, c, d, inw[12] + 0x655b59c3,  6);
  MD5STEP(F4, d, a, b, c, inw[3]  + 0x8f0ccc92, 10);
  MD5STEP(F4, c, d, a, b, inw[10] + 0xffeff47d, 15);
  MD5STEP(F4, b, c, d, a, inw[1]  + 0x85845dd1, 21);
  MD5STEP(F4, a, b, c, d, inw[8]  + 0x6fa87e4f,  6);
  MD5STEP(F4, d, a, b, c, inw[15] + 0xfe2ce6e0, 10);
  MD5STEP(F4, c, d, a, b, inw[6]  + 0xa3014314, 15);
  MD5STEP(F4, b, c, d, a, inw[13] + 0x4e0811a1, 21);
  MD5STEP(F4, a, b, c, d, inw[4]  + 0xf7537e82,  6);
  MD5STEP(F4, d, a, b, c, inw[11] + 0xbd3af235, 10);
  MD5STEP(F4, c, d, a, b, inw[2]  + 0x2ad7d2bb, 15);
  MD5STEP(F4, b, c, d, a, inw[9]  + 0xeb86d391, 21);

  ptr->m_Buf[0] += a;
  ptr->m_Buf[1] += b;
  ptr->m_Buf[2] += c;
  ptr->m_Buf[3] += d;
}



// Start MD5 accumulation.  Set bit count to 0 and buffer to mysterious
// initialization constants.
CMD5* CMD5New(void)
{
  CMD5* p = (CMD5*)xmalloc(sizeof(CMD5));
  p->m_Bits = 0;
  p->m_Buf[0] = 0x67452301;
  p->m_Buf[1] = 0xefcdab89;
  p->m_Buf[2] = 0x98badcfe;
  p->m_Buf[3] = 0x10325476;
  p->m_Finalized = 0;
  return p;
}


// Update state to reflect the concatenation of another buffer full of bytes.
void CMD5Update(CMD5* ptr,const char* buf, size_t length)
{
  unsigned int  tmp;
  if ( ptr->m_Finalized )
    {
     O (fatal, NILF, _("attempt to update a finalized MD5 instance"));
    }

  // Number of leftover bytes in m_In
  tmp = (unsigned int)((ptr->m_Bits >> 3) % (sizeof(ptr->m_In)) );

  // Update bit count
  ptr->m_Bits += length << 3;

  // Handle any leading odd-sized chunks
  if ( tmp )
    {
      unsigned char* p = ptr->m_In + tmp;
      
      tmp = kBlockSize - tmp;
      if (length < tmp)
        {
          memcpy(p, buf, length);
          return;
        }
      memcpy(p, buf, tmp);
      #ifdef __BIG_ENDIAN__
        s_ByteReverse(ptr->m_In, 16);
      #endif
      CMD5Transform(ptr);
      buf    += tmp;
      length -= tmp;
    }

  // Process remaining data in kBlockSize-byte chunks
  while (length >= kBlockSize)
    {
      memcpy(ptr->m_In, buf, kBlockSize);
      #ifdef __BIG_ENDIAN__
        s_ByteReversep->(ptr->m_In, 16);
      #endif
      CMD5Transform(ptr);
      buf    += kBlockSize;
      length -= kBlockSize;
    }

  // Handle any remaining bytes of data
  memcpy(ptr->m_In, buf, length);
}


// Final wrapup - pad to kBlockSize-byte boundary with the bit pattern
// 1 0* (64-bit count of bits processed, MSB-first).
void CMD5Finalize(CMD5* ptr,unsigned char digest[16])
{
  int  count;
  unsigned char *p;
  if ( ptr->m_Finalized )
    {
      memcpy(digest, ptr->m_Buf, 16);
      return;
    }

  // Compute number of bytes mod kBlockSize
  count = (int)((ptr->m_Bits >> 3) % kBlockSize);

  // Set the first char of padding to 0x80.  This is safe since there is
  // always at least one byte free.
  p = ptr->m_In + count;
  *p++ = 0x80;

  // Bytes of padding needed to make kBlockSize bytes
  count = kBlockSize - 1 - count;

  // Pad out to 56 mod kBlockSize
  if (count < 8)
    {
      // Two lots of padding:  Pad the first block to kBlockSize bytes
      memset(p, 0, count);
      #ifdef __BIG_ENDIAN__
        s_ByteReverse(ptr->m_In, 16);
      #endif
      CMD5Transform(ptr);

      // Now fill the next block with 56 bytes
      memset(ptr->m_In, 0, kBlockSize - 8);
    }
  else
  {
    // Pad block to 56 bytes
    memset(p, 0, count - 8);
    #ifdef __BIG_ENDIAN__
      s_ByteReverse(ptr->m_In, 14);
    #endif
  }

  // Append length in bits and transform
  ((uint32_t*)ptr->m_In)[14] = (uint32_t)(ptr->m_Bits);
  ((uint32_t*)ptr->m_In)[15] = (uint32_t)(ptr->m_Bits >> 32);

  CMD5Transform(ptr);
  #ifdef __BIG_ENDIAN__
    s_ByteReverse((unsigned char*)(ptr->m_Buf), 4);
  #endif
  memcpy(digest, ptr->m_Buf, 16);
  memset(ptr->m_In, 0, kBlockSize); // may be sensitive
  ptr->m_Finalized = 1;
  }


