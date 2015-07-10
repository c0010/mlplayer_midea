#include "stdafx.h"
#if defined(PLAT_AND)
#include "iconv.h"
#endif

static const size_t utf8_skip_data[256] = {
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
    3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,6,6,1,1
};

char *utf8ncpy(char *dst, const char *src, size_t maxncpy)
{
    char *dst_r = dst;
    size_t utf8_size;

    if (src == NULL) return dst;

    if (maxncpy > 0) {
        while (*src != '\0' && (utf8_size = utf8_skip_data[*((unsigned char *)src)]) <= maxncpy) {
            maxncpy -= utf8_size;
            switch (utf8_size) {
                case 6: *dst ++ = *src ++;
                case 5: *dst ++ = *src ++;
                case 4: *dst ++ = *src ++;
                case 3: *dst ++ = *src ++;
                case 2: *dst ++ = *src ++;
                case 1: *dst ++ = *src ++;
            }
        }
        *dst= '\0';
    }
    return dst_r;
}

#if defined(PLAT_AND)
//utf8->utf16
unsigned short* UTF8toUTF16(char* in, size_t* len)
{

    iconv_t conv = iconv_open("UTF-16LE", "UTF-8");

    char* pin = in;
    size_t inleft = (len != NULL && *len > 0)?*len:strlen(pin);
    size_t outleft = inleft*2+1;
    unsigned short* out = (unsigned short*)calloc(outleft, 1);
    char* pout = (char*)out;

//    CM_ERRP("iconv start iconv_t %d len %d str %s", conv, inleft, pin);
    iconv(conv, NULL, NULL, NULL, NULL);
    if (iconv(conv, &pin, &inleft, &pout, &outleft) == -1 || iconv(conv, NULL,NULL, &pout,&outleft) == -1)
    {
    	CM_ERRP("UTF8toUTF16 failed errno %d, str %s",errno, in);
    	iconv_close(conv);
    	free(out);
    	len = 0;
    	return NULL;
    }

    iconv_close(conv);
    if (len != NULL)
    	*len = (unsigned short*)pout - out;
    return out;
}

//utf16->utf8
char* UTF16toUTF8(unsigned short* in, size_t* len)
{
    iconv_t conv = iconv_open("UTF-8", "UTF-16LE");

    char* pin = (char*)in;
    size_t inleft = (len != NULL && *len > 0)?*len*2:wcslen((wchar_t*)in)*2;
    size_t outleft = inleft*2+1;
    char* out = (char*)calloc(outleft, 1);
    char* pout = out;

    iconv(conv, NULL, NULL, NULL, NULL);
    if (iconv(conv, &pin, &inleft, &pout, &outleft) == -1 || iconv(conv, NULL,NULL, &pout,&outleft) == -1)
    {
    	CM_ERRP("UTF16toUTF8 failed errno %d, str %s",errno, in);
    	iconv_close(conv);
    	free(out);
    	len = 0;
    	return NULL;
    }

    iconv_close(conv);
    if (len != NULL)
    	*len = pout - out;
    return out;
}
#endif
