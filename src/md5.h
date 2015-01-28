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

