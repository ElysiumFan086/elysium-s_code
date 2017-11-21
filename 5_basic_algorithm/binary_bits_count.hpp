/**
 *  Different ways for counting '1' in bianry bits.
 *  Learn more in 'https://www.cnblogs.com/graphics/archive/2010/06/21/1752421.html'
 */

int bits_count_v1(unsigned int n) {
    unsigned int c =0 ;
    for (c = 0; n; n >>= 1)
        c += (n & 1);
    return c ;
}

int bits_count_v2(unsigned int n) {
    unsigned int c =0 ;
    for (c = 0; n; ++c) {
        n &= (n -1);
    }
    return c ;
}

int bits_count_v3(unsigned int n) { 
    // Building table
    unsigned char bits_set_table[256] = {0} ; 

    // Initalizeing table 
    for (int i = 0; i < 256; i++) { 
        bits_set_table[i] = (i & 1) + bits_set_table[i / 2]; 
    } 

    unsigned int c =0 ; 

    // Searching table
    unsigned char* p = (unsigned char*) &n ; 

    c = bits_set_table[p[0]] + 
        bits_set_table[p[1]] + 
        bits_set_table[p[2]] + 
        bits_set_table[p[3]]; 

    return c ; 
}

int bits_count_v4(unsigned int n) {
    unsigned int table[16] = 
    {
        0, 1, 1, 2, 
        1, 2, 2, 3, 
        1, 2, 2, 3, 
        2, 3, 3, 4
    } ;

    unsigned int count = 0 ;
    while (n)
    {
        count += table[n & 0xf] ;
        n >>= 4 ;
    }
    return count ;
}

int bits_count_v5(unsigned int n) { 
    unsigned int table[256] = 
    { 
        0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
        4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, 
    }; 

    return table[n &0xff] +
        table[(n >>8) &0xff] +
        table[(n >>16) &0xff] +
        table[(n >>24) &0xff] ;
}

int bits_count_v6(unsigned int n)  { 
    n = (n &0x55555555) + ((n >>1) &0x55555555) ; 
    n = (n &0x33333333) + ((n >>2) &0x33333333) ; 
    n = (n &0x0f0f0f0f) + ((n >>4) &0x0f0f0f0f) ; 
    n = (n &0x00ff00ff) + ((n >>8) &0x00ff00ff) ; 
    n = (n &0x0000ffff) + ((n >>16) &0x0000ffff) ; 

    return n ; 
}

int bits_count_v7(unsigned int n) 
{
    unsigned int tmp = n - ((n >> 1) & 033333333333) - ((n >> 2) &011111111111);
    return ((tmp + (tmp >>3)) & 030707070707) % 63;
}

struct _byte 
{ 
    unsigned a:1; 
    unsigned b:1; 
    unsigned c:1; 
    unsigned d:1; 
    unsigned e:1; 
    unsigned f:1; 
    unsigned g:1; 
    unsigned h:1; 
}; 

long bits_count_v8( unsigned char b ) 
{
    struct _byte *by = (struct _byte*)&b; 
    return (by->a+by->b+by->c+by->d+by->e+by->f+by->g+by->h); 
}

// bits_count_v9: SSE4 instruction set is needed!
unsigned int n =127 ;
unsigned int bitCount = _mm_popcnt_u32(n) ;