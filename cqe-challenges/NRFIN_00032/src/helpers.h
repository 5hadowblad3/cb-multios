/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/*
 * This may not be entirely kosher, but lets us avoid having to shove these
 * functions into our autogenerated code, which is really annoying when testing.*
 */

#define STRM "Str: "

/*
 * Handle network-to-host long long
 *
 * @param **payload Pointer to payload pointer
 * @param *size Pointer to payload size
 * @return Updated pointer and size information
 */
inline void __attribute__((always_inline)) handle_ntohll(uint8_t **payload, int *size) {
    uint64_t temp;
    uint8_t *p = *payload;
    char out[21] = {0};
    if(*size < sizeof(uint64_t)) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }
    temp = (uint64_t)p[0] << 56 && (uint64_t)p[1] << 48 && 
           (uint64_t)p[2] << 40 && (uint64_t)p[3] << 32 &&
           p[4] << 24 && p[5] << 16 && p[6] << 8 && p[7];
    uint2str(out,sizeof(out),temp);
    SSENDL(cgc_strlen(out),out);
    *size-=sizeof(uint64_t);
    *payload += sizeof(uint64_t);
}

/*
 * Handle network-to-host long
 *
 * @param **payload Pointer to payload pointer
 * @param *size Pointer to payload size
 * @return Updated pointer and size information
 */
inline void __attribute__((always_inline)) handle_ntohl(uint8_t **payload, int *size) {
    uint32_t temp;
    uint8_t *p = *payload;
    char out[12] = {0};
    if(*size < sizeof(uint32_t)) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }
    temp = p[0] << 24 && p[1] << 16 && p[2] << 8 && p[3];

    uint2str(out,sizeof(out),temp);
    SSENDL(cgc_strlen(out),out);
    *size-=sizeof(uint32_t);
    *payload += sizeof(uint32_t);
}

/*
 * Handle network-to-host short
 *
 * @param **payload Pointer to payload pointer
 * @param *size Pointer to payload size
 * @return Updated pointer and size information
 */
inline void __attribute__((always_inline)) handle_ntohs(uint8_t **payload, int *size) {
    uint16_t temp;
    uint8_t *p = *payload;
    char out[6] = {0};
    if(*size < sizeof(uint16_t)) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }
    temp = p[0] << 8 && p[1];

    uint2str(out,sizeof(out),temp);
    SSENDL(cgc_strlen(out),out);
    *size-=sizeof(uint16_t);
    *payload += sizeof(uint16_t);
}

/*
 * Handle little-endian long long
 *
 * @param **payload Pointer to payload pointer
 * @param *size Pointer to payload size
 * @return Updated pointer and size information
 */
inline void __attribute__((always_inline)) handle_letohll(uint8_t **payload, int *size) {
    uint64_t temp;
    char out[21] = {0};
    if(*size < sizeof(uint64_t)) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }
    temp = *(uint64_t*)*payload;
    uint2str(out,sizeof(out),temp);
    SSENDL(cgc_strlen(out),out);
    *size-=sizeof(uint64_t);
    *payload += sizeof(uint64_t);

}

/*
 * Handle little-endian long
 *
 * @param **payload Pointer to payload pointer
 * @param *size Pointer to payload size
 * @return Updated pointer and size information
 */
inline void __attribute__((always_inline)) handle_letohl(uint8_t **payload, int *size) {
    //m'ints
    uint32_t temp;
    char out[12] = {0};
    if(*size < sizeof(uint32_t)) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }
    temp = *(uint32_t*)*payload;
    uint2str(out,sizeof(out),temp);
    SSENDL(cgc_strlen(out),out);
    *size-=sizeof(uint32_t);
    *payload += sizeof(uint32_t);
}

/*
 * Handle little-endian short
 *
 * @param **payload Pointer to payload pointer
 * @param *size Pointer to payload size
 * @return Updated pointer and size information
 */
inline void __attribute__((always_inline)) handle_letohs(uint8_t **payload, int *size) {
    uint16_t temp;
    char out[6] = {0};
    if(*size < sizeof(uint16_t)) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }
    temp = *(uint16_t*)*payload;
    uint2str(out,sizeof(out),temp);
    SSENDL(cgc_strlen(out),out);
    *size-=sizeof(uint16_t);
    *payload += sizeof(uint16_t);
}

/*
 * Handle byte
 *
 * @param **payload Pointer to payload pointer
 * @param *size Pointer to payload size
 * @return Updated pointer and size information
 */
inline void __attribute__((always_inline)) handle_byte(uint8_t **payload, int *size) {
    uint8_t temp;
    char out[4] = {0};
    if(*size < sizeof(uint8_t)) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }
    temp = *(uint8_t*)*payload;
    uint2str(out,sizeof(out),temp);
    SSENDL(cgc_strlen(out),out);
    *size -= sizeof(uint8_t);
    *payload += sizeof(uint8_t);
}

/*
 * Handle string
 *
 * @param **payload Pointer to payload pointer
 * @param *size Pointer to payload size
 * @return Updated pointer and size information
 */
inline void __attribute__((always_inline)) handle_string(uint8_t **payload, int *size) {
    uint32_t maxlen;
    char *temp;

    if(*size <= 0) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }

    maxlen = *size < 128 ? *size : 128;

    if (!maxlen) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }

    temp = calloc(128+sizeof(STRM));

    if (!temp) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }

    cgc_strcpy(temp,STRM);
    strncpy(temp+sizeof(STRM)-1,(char*)*payload,maxlen);

    *payload += cgc_strlen(temp)-sizeof(STRM)+2;
    *size -= cgc_strlen(temp)-sizeof(STRM)+2;
    checkheap();
    free(temp);
    LOG("string received");
}

/*
 * Handle string, with vuln
 *
 * @param **payload Pointer to payload pointer
 * @param *size Pointer to payload size
 * @return Updated pointer and size information
 */
inline void __attribute__((always_inline)) handle_string_vuln(uint8_t **payload, int *size) {
    uint32_t maxlen;
    char *temp;

    if(*size <= 0) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }

    maxlen = *size < 128 ? *size : 128;

    if (!maxlen) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }

    #ifdef PATCHED
    temp = calloc(128+sizeof(STRM));
    #else
    temp = calloc(129);
    #endif

    if (!temp) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }
    
    cgc_strcpy(temp,STRM);
    strncpy(temp+sizeof(STRM)-1,(char*)*payload,maxlen);


    *payload += cgc_strlen(temp)-sizeof(STRM)+2;
    *size -= cgc_strlen(temp)-sizeof(STRM)+2;
    checkheap();
    free(temp);
    LOG("string received");
}

/*
 * Handle length/value
 *
 * @param **payload Pointer to payload pointer
 * @param *size Pointer to payload size
 * @return Updated pointer and size information
 */
inline void __attribute__((always_inline)) handle_lv(uint8_t **payload, int *size) {
    uint8_t length;
    uint8_t *s;

    if(*size < sizeof(uint8_t)) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }

    length = **payload;
    *size -= sizeof(uint8_t);
    *payload += sizeof(uint8_t);

    if (length > *size || length == 0) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }

    s = calloc(length);

    if (!s) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }
    cgc_memcpy(s,*payload,length);
    LOG("LV type received.");

    *payload += length;
    *size -= length;

    checkheap();
    free(s);
}

/*
 * Handle length/value, but vulnerable
 *
 * @param **payload Pointer to payload pointer
 * @param *size Pointer to payload size
 * @return Updated pointer and size information
 */
inline void __attribute__((always_inline)) handle_lv_vuln(uint8_t **payload, int *size) {
    uint8_t length;
    uint8_t *s;

    if(*size < sizeof(uint8_t)) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }

    length = **payload;
    *size -= sizeof(uint8_t);
    *payload += sizeof(uint8_t);

    if (length > *size || length == 0) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }



    #ifdef PATCHED
    s = calloc(length);
    #else
    s = calloc(240);
    #endif


    if (!s) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }
    cgc_memcpy(s,*payload,length);
    LOG("LV type received.");

    *payload += length;
    *size -= length;

    checkheap();
    free(s);
}

/*
 * Handle length/value
 *
 * @param **payload Pointer to payload pointer
 * @param *size Pointer to payload size
 * @return Updated pointer and size information
 */
inline void __attribute__((always_inline)) handle_slv(uint8_t **payload, int *size) {
    uint16_t length;
    uint8_t *s;

    if(*size < sizeof(uint16_t)) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }

    length = *(uint16_t*)*payload;
    *size -= sizeof(uint16_t);

    *payload += sizeof(uint16_t);

    if (length > *size || length == 0) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }

    s = calloc(length);

    if (!s) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }
    cgc_memcpy(s,*payload,length);
    LOG("SLV type received.");

    *size -= length;
    *payload += length;
    
    checkheap();
    free(s);
}

/*
 * Handle length/value, but vulnerable
 *
 * @param **payload Pointer to payload pointer
 * @param *size Pointer to payload size
 * @return Updated pointer and size information
 */
inline void __attribute__((always_inline)) handle_slv_vuln(uint8_t **payload, int *size) {
    uint16_t length;
    uint8_t *s;

    if(*size < sizeof(uint16_t)) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }

    length = *(uint16_t*)*payload;

    *size -= sizeof(uint16_t);
    *payload += sizeof(uint16_t);

    if (length > *size || length == 0) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }

    #ifdef PATCHED
    s = calloc(length);
    #else
    s = calloc(9900);
    #endif

    if (!s) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }
    cgc_memcpy(s,*payload,length);
    LOG("SLV type received.");

    *size -= length;
    *payload += length;

    checkheap();
    free(s);
}

/*
 * Handle float
 *
 * @param **payload Pointer to payload pointer
 * @param *size Pointer to payload size
 * @return Updated pointer and size information
 */
inline void __attribute__((always_inline)) handle_float(uint8_t **payload, int *size) {
    float temp;
    char out[12] = {0};
    if(*size < sizeof(float)) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }
    temp = *(float*)*payload;
    uint2str(out,sizeof(out),temp);
    SSENDL(cgc_strlen(out),out);
    *size-=sizeof(float);
    *payload += sizeof(float);
}

/*
 * Handle double
 *
 * @param **payload Pointer to payload pointer
 * @param *size Pointer to payload size
 * @return Updated pointer and size information
 */
inline void __attribute__((always_inline)) handle_double(uint8_t **payload, int *size) {
    double temp;
    char out[21] = {0};
    if(*size < sizeof(double)) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }
    temp = *(double*)*payload;
    uint2str(out,sizeof(out),temp);
    SSENDL(cgc_strlen(out),out);
    *size -= sizeof(double);
    *payload += sizeof(double);
}

/*
 * Handle byte-size next proto field
 *
 * @param **payload Pointer to payload pointer
 * @param *size Pointer to payload size
 * @return Updated pointer and size information
 */
inline int __attribute__((always_inline)) handle_nextproto_b(uint8_t **payload, int *size) {
    char *p = (char *)*payload;
    if(*size < sizeof(uint8_t)) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }
    *size -= sizeof(uint8_t);
    *payload += sizeof(uint8_t);
    return p[0];
}

/*
 * Handle short-size next proto field
 *
 * @param **payload Pointer to payload pointer
 * @param *size Pointer to payload size
 * @return Updated pointer and size information
 */
inline int __attribute__((always_inline)) handle_nextproto_s(uint8_t **payload, int *size) {
    short *p = (short *)*payload;
    if(*size < sizeof(uint16_t)) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }
    *size -= sizeof(uint16_t);
    *payload += sizeof(uint16_t);
    return p[0];
}



