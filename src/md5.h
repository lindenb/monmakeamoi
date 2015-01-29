/* The MIT License

   Permission is hereby granted, free of charge, to any person obtaining
   a copy of this software and associated documentation files (the
   "Software"), to deal in the Software without restriction, including
   without limitation the rights to use, copy, modify, merge, publish,
   distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to do so, subject to
   the following conditions:

   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
   BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.

   contact: Pierre Lindenbaum PhD @yokofakun


History:
   * Jan 2015 first commit
   * Orignal C++ code from Aaron Ucko / NCBI(National Center for Biotechnology Information) /Public Domain
     Converted back to C by Pierre Lindenbaum


*/
#ifndef MON_MAKE_MD5_H
#define MON_MAKE_MD5_H
#include <stddef.h>


 // Block size defined by algorithm;
#define kBlockSize  ((int)64)

/* struct for computing Message Digest version 5 checksums */
typedef struct  CMD5_t
  {
    uint32_t       m_Buf[4];
    int64_t        m_Bits; // must be a 64-bit count
    unsigned char  m_In[kBlockSize];
    int            m_Finalized;
  } CMD5;

/* create a new CMD5 */
CMD5* CMD5New(void);
/* Update state to reflect the concatenation of another buffer full of bytes. */
void CMD5Update(CMD5* ptr,const char* buf, size_t length);
/* // Final wrapup - pad to kBlockSize-byte boundary with the bit pattern */
void CMD5Finalize(CMD5* ptr,unsigned char digest[16]);

#endif


