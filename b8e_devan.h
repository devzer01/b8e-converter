static const unsigned short b8e_devan_wc[128] = {
        0xa484, 0x0000, 0xa487, 0xa489, 0xa48b, 0xa48c, 0xa48e, 0xa492, 0xa486,
        0x0000, 0xa488, 0xa48a, 0xa5a0, 0xa5a1, 0xa490, 0xa494, 0x0000, 0x0000,
        0xa4bf, 0xa581, 0xa583, 0xa5a2, 0xa586, 0xa58a, 0xa4be, 0x0000, 0xa580,
        0xa582, 0xa584, 0xa5a3, 0xa588, 0xa58c, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0xa48d, 0xa491, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0xa585, 0xa589, 0xa495, 0xa497, 0xa49a, 0xa49c, 0xa49f, 0xa4a1,
        0xa4a8, 0xa4a4, 0xa4a6, 0xa4aa, 0xa4ac, 0xa4b2, 0xa4b8, 0xa499, 0xa4b0,
        0xa4af, 0xa496, 0xa498, 0xa49b, 0xa49d, 0xa4a0, 0xa4a2, 0x0000, 0xa4a5,
        0xa4a7, 0xa4ab, 0xa4ad, 0xa4b3, 0xa4b6, 0xa49e, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0xa59c, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0xa4b7, 0x0000, 0xa4b1, 0xa59f, 0xa4b5, 0xa4b9, 0xa4ae,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0xa480, 0xa481, 0xa482, 0xa483, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000};

static const unsigned char b8e_devan_b[128] = {
        0xf0, 0xf1, 0xf2, 0xf3, 0x80, 0x80, 0x88, 0x82, 0x8a, 0x83, 0x8b, 0x84,
        0x85, 0xa6, 0x86, 0x86, 0x8e, 0xa7, 0x87, 0xa7, 0x8f, 0xb0, 0xc0, 0xb1,
        0xc1, 0xbd, 0xb2, 0xc2, 0xb3, 0xc3, 0xcd, 0xb4, 0xc4, 0xb5, 0xc5, 0x00,
        0xb7, 0xc7, 0xb8, 0xc8, 0xb6, 0x00, 0xb9, 0xc9, 0xba, 0xca, 0xe2, 0xbf,
        0xbe, 0xde, 0xbb, 0xcb, 0x00, 0xe0, 0xcc, 0xdc, 0xbc, 0xe1, 0x00, 0x00,
        0x00, 0x00, 0x98, 0x92, 0x9a, 0x93, 0x9b, 0x94, 0x9c, 0xae, 0x96, 0x96,
        0x9e, 0xaf, 0x97, 0x97, 0x9f, 0x00, 0x96, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0xae, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd5, 0x00, 0x00, 0xdf,
        0x8c, 0x8d, 0x95, 0x9d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static int b8edevan_mbtowc(conv_t conv, ucs4_t *pwc, const unsigned char *s, size_t n) {
    unsigned char c = *s;
    if (c < 0x80) {
        *pwc = (ucs4_t) c;
        return 1;
    } else {
        unsigned short wc = b8e_devan_wc[c - 0x80];
        *pwc = (ucs4_t) wc;
        return 1;
    }
    return RET_ILSEQ;
}

static int b8edevan_wctomb(conv_t conv, unsigned char *r, ucs4_t wc, size_t n) {
    if (wc < 0x0080) {
        *r = wc;
        return 1;
    } else if (wc >= (ucs4_t) 0x0900 && wc <= (ucs4_t) 0x09ff) {
        int index = wc - (ucs4_t) 0x0900;
        *r = (char) b8e_devan_b[index];
        return 1;
    } else if (wc == 0xFFFD) {
        *r = 0xff;
        return 1;
    }
    return RET_ILUNI;
}

//static int  b8edevan_reset (conv_t conv, unsigned char *r, size_t n)
//{
//    state_t state = conv->ostate;
//    if (state) {
//        if (n < 2)
//            return RET_TOOSMALL;
//        r[0] = '~';
//        r[1] = '}';
//        /* conv->ostate = 0; will be done by the caller */
//        return 2;
//    } else
//        return 0;
//}