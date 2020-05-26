#include <inttypes.h>
#include <string.h>
#include <stdio.h>

const char g_utf8bytes[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* 00 - 0F */
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* 10 - 1F */
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* 20 - 2F */
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* 30 - 3F */
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* 40 - 4F */
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* 50 - 5F */
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* 60 - 6F */
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* 70 - 7F */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 80 - 8F */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 90 - 9F */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* A0 - AF */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* B0 - BF */
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, /* C0 - CF */
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, /* D0 - DF */
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, /* E0 - EF */
    4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, /* F0 - FF */
};

static inline const char *east_asian_width_code(int64_t c);

#define utf8_length(c) (utf8bytes[c & 0xff])
#define is_utf8_trail(c) (0x80 <= (c) && (c) <= 0xbf)

static inline unsigned int utf82codepoint(const unsigned char *str, unsigned int len, unsigned int *cur)
{
    unsigned int pos = cur ? *cur : 0;
    unsigned int slen = len - pos;
    unsigned char c = str[pos];
    unsigned int cp = 0xfffd;

    if (slen < 1) {
        ++pos;
    } else if (c < 0x80) {
        cp = str[pos++];
    } else if (c < 0xc2) {
        ++pos;
    } else if (c < 0xe0) {
        if (slen < 2 || !is_utf8_trail(str[pos + 1])) {
            ++pos;
        } else {
            cp = ((str[pos] & 0x1f) << 6) + (str[pos + 1] & 0x3f);
            pos += 2;
        }
    } else if (c < 0xf0) {
        unsigned char minv = (c == 0xe0) ? 0xa0 : 0x80;
        unsigned char maxv = (c == 0xed) ? 0x9f : 0xbf;
        if (slen < 2 || str[pos + 1] < minv || maxv < str[pos + 1]) {
            ++pos;
        } else if (slen < 3 || !is_utf8_trail(str[pos + 2])) {
            pos += 2;
        } else {
            cp = ((str[pos] & 0xf) << 12) | ((str[pos+1] & 0x3f) << 6) | (str[pos+2] & 0x3f);
            pos += 3;
        }
    } else if (c < 0xf5) {
        unsigned char minv = (c == 0xf0) ? 0x90 : 0x80;
        unsigned char maxv = (c == 0xf4) ? 0x8f : 0xbf;
        if (len < 2 || str[pos + 1] < minv || maxv < str[pos + 1]) {
            ++pos;
        } else if (len < 3 || !is_utf8_trail(str[pos+2])) {
            pos += 2;
        } else if (len < 4 || !is_utf8_trail(str[pos+3])) {
            pos += 3;
        } else {
            cp = ((str[pos] & 0x7) << 18) | ((str[pos+1] & 0x3f) << 12) | ((str[pos+2] & 0x3f) << 6) | (str[pos+3] & 0x3f);
            pos += 4;
        }
    } else {
        ++pos;
    }

    if (cur) {
        *cur = pos;
    }
    return cp;
}

static inline const char *east_asian_width(const char *str, int len, unsigned int *cp, unsigned int *cur)
{
    unsigned int codepoint = utf82codepoint((const unsigned char *)str, len, cur);
    if (cp) {
        *cp = codepoint;
    }
    return east_asian_width_code(codepoint);
}

static inline const char *east_asian_width_code(int64_t c)
{
    switch (c) {
    case 0x20A9:
    case 0xFF61:
    case 0xFF62:
    case 0xFF63:
    case 0xFF70:
    case 0xFFE8:
        return "H";
    case 0x00A1:
    case 0x00A4:
    case 0x00A7:
    case 0x00A8:
    case 0x00AA:
    case 0x00AD:
    case 0x00AE:
    case 0x00B0:
    case 0x00B1:
    case 0x00B4:
    case 0x00B8:
    case 0x00B9:
    case 0x00BA:
    case 0x00BF:
    case 0x00C6:
    case 0x00D0:
    case 0x00D7:
    case 0x00D8:
    case 0x00E6:
    case 0x00F0:
    case 0x00F7:
    case 0x00FC:
    case 0x00FE:
    case 0x0101:
    case 0x0111:
    case 0x0113:
    case 0x011B:
    case 0x012B:
    case 0x0138:
    case 0x0144:
    case 0x014D:
    case 0x016B:
    case 0x01CE:
    case 0x01D0:
    case 0x01D2:
    case 0x01D4:
    case 0x01D6:
    case 0x01D8:
    case 0x01DA:
    case 0x01DC:
    case 0x0251:
    case 0x0261:
    case 0x02C4:
    case 0x02C7:
    case 0x02CD:
    case 0x02D0:
    case 0x02DD:
    case 0x02DF:
    case 0x0401:
    case 0x0451:
    case 0x2010:
    case 0x2016:
    case 0x2018:
    case 0x2019:
    case 0x201C:
    case 0x201D:
    case 0x2030:
    case 0x2035:
    case 0x203B:
    case 0x203E:
    case 0x2074:
    case 0x207F:
    case 0x20AC:
    case 0x2103:
    case 0x2105:
    case 0x2109:
    case 0x2113:
    case 0x2116:
    case 0x2126:
    case 0x212B:
    case 0x2189:
    case 0x21D2:
    case 0x21D4:
    case 0x21E7:
    case 0x2200:
    case 0x220B:
    case 0x220F:
    case 0x2211:
    case 0x2215:
    case 0x221A:
    case 0x2223:
    case 0x2225:
    case 0x222E:
    case 0x2248:
    case 0x224C:
    case 0x2252:
    case 0x2295:
    case 0x2299:
    case 0x22A5:
    case 0x22BF:
    case 0x2312:
    case 0x25B6:
    case 0x25B7:
    case 0x25C0:
    case 0x25C1:
    case 0x25CB:
    case 0x25EF:
    case 0x2609:
    case 0x261C:
    case 0x261E:
    case 0x2640:
    case 0x2642:
    case 0x266F:
    case 0x26BF:
    case 0x26E3:
    case 0x26F4:
    case 0x273D:
    case 0xFFFD:
        return "A";
    case 0x0020:
    case 0x0024:
    case 0x0028:
    case 0x0029:
    case 0x002A:
    case 0x002B:
    case 0x002C:
    case 0x002D:
    case 0x005B:
    case 0x005C:
    case 0x005D:
    case 0x005E:
    case 0x005F:
    case 0x0060:
    case 0x007B:
    case 0x007C:
    case 0x007D:
    case 0x007E:
    case 0x00A5:
    case 0x00A6:
    case 0x00AC:
    case 0x00AF:
    case 0x27E6:
    case 0x27E7:
    case 0x27E8:
    case 0x27E9:
    case 0x27EA:
    case 0x27EB:
    case 0x27EC:
    case 0x27ED:
    case 0x2985:
    case 0x2986:
        return "Na";
    case 0x3000:
    case 0xFF04:
    case 0xFF08:
    case 0xFF09:
    case 0xFF0A:
    case 0xFF0B:
    case 0xFF0C:
    case 0xFF0D:
    case 0xFF3B:
    case 0xFF3C:
    case 0xFF3D:
    case 0xFF3E:
    case 0xFF3F:
    case 0xFF40:
    case 0xFF5B:
    case 0xFF5C:
    case 0xFF5D:
    case 0xFF5E:
    case 0xFF5F:
    case 0xFF60:
    case 0xFFE2:
    case 0xFFE3:
    case 0xFFE4:
        return "F";
    case 0x2329:
    case 0x232A:
    case 0x23F0:
    case 0x23F3:
    case 0x267F:
    case 0x2693:
    case 0x26A1:
    case 0x26CE:
    case 0x26D4:
    case 0x26EA:
    case 0x26F5:
    case 0x26FA:
    case 0x26FD:
    case 0x2705:
    case 0x2728:
    case 0x274C:
    case 0x274E:
    case 0x2757:
    case 0x27B0:
    case 0x27BF:
    case 0x2B50:
    case 0x2B55:
    case 0x3004:
    case 0x3005:
    case 0x3006:
    case 0x3007:
    case 0x3008:
    case 0x3009:
    case 0x300A:
    case 0x300B:
    case 0x300C:
    case 0x300D:
    case 0x300E:
    case 0x300F:
    case 0x3010:
    case 0x3011:
    case 0x3014:
    case 0x3015:
    case 0x3016:
    case 0x3017:
    case 0x3018:
    case 0x3019:
    case 0x301A:
    case 0x301B:
    case 0x301C:
    case 0x301D:
    case 0x3020:
    case 0x3030:
    case 0x303B:
    case 0x303C:
    case 0x303D:
    case 0x303E:
    case 0x309F:
    case 0x30A0:
    case 0x30FB:
    case 0x30FF:
    case 0x3250:
    case 0xA015:
    case 0xFE17:
    case 0xFE18:
    case 0xFE19:
    case 0xFE30:
    case 0xFE35:
    case 0xFE36:
    case 0xFE37:
    case 0xFE38:
    case 0xFE39:
    case 0xFE3A:
    case 0xFE3B:
    case 0xFE3C:
    case 0xFE3D:
    case 0xFE3E:
    case 0xFE3F:
    case 0xFE40:
    case 0xFE41:
    case 0xFE42:
    case 0xFE43:
    case 0xFE44:
    case 0xFE47:
    case 0xFE48:
    case 0xFE58:
    case 0xFE59:
    case 0xFE5A:
    case 0xFE5B:
    case 0xFE5C:
    case 0xFE5D:
    case 0xFE5E:
    case 0xFE62:
    case 0xFE63:
    case 0xFE68:
    case 0xFE69:
    case 0x16FE2:
    case 0x16FE3:
    case 0x16FE4:
    case 0x1F004:
    case 0x1F0CF:
    case 0x1F18E:
    case 0x1F3F4:
    case 0x1F440:
    case 0x1F57A:
    case 0x1F5A4:
    case 0x1F6CC:
        return "W";
    default:
        ;
    }
    if (0x0021 <= c && c <= 0x0023) return "Na";
    if (0x0025 <= c && c <= 0x0027) return "Na";
    if (0x002E <= c && c <= 0x002F) return "Na";
    if (0x0030 <= c && c <= 0x0039) return "Na";
    if (0x003A <= c && c <= 0x003B) return "Na";
    if (0x003C <= c && c <= 0x003E) return "Na";
    if (0x003F <= c && c <= 0x0040) return "Na";
    if (0x0041 <= c && c <= 0x005A) return "Na";
    if (0x0061 <= c && c <= 0x007A) return "Na";
    if (0x00A2 <= c && c <= 0x00A3) return "Na";
    if (0x00B2 <= c && c <= 0x00B3) return "A";
    if (0x00B6 <= c && c <= 0x00B7) return "A";
    if (0x00BC <= c && c <= 0x00BE) return "A";
    if (0x00DE <= c && c <= 0x00E1) return "A";
    if (0x00E8 <= c && c <= 0x00EA) return "A";
    if (0x00EC <= c && c <= 0x00ED) return "A";
    if (0x00F2 <= c && c <= 0x00F3) return "A";
    if (0x00F8 <= c && c <= 0x00FA) return "A";
    if (0x0126 <= c && c <= 0x0127) return "A";
    if (0x0131 <= c && c <= 0x0133) return "A";
    if (0x013F <= c && c <= 0x0142) return "A";
    if (0x0148 <= c && c <= 0x014B) return "A";
    if (0x0152 <= c && c <= 0x0153) return "A";
    if (0x0166 <= c && c <= 0x0167) return "A";
    if (0x02C9 <= c && c <= 0x02CB) return "A";
    if (0x02D8 <= c && c <= 0x02DB) return "A";
    if (0x0300 <= c && c <= 0x036F) return "A";
    if (0x0391 <= c && c <= 0x03A1) return "A";
    if (0x03A3 <= c && c <= 0x03A9) return "A";
    if (0x03B1 <= c && c <= 0x03C1) return "A";
    if (0x03C3 <= c && c <= 0x03C9) return "A";
    if (0x0410 <= c && c <= 0x044F) return "A";
    if (0x1100 <= c && c <= 0x115F) return "W";
    if (0x2013 <= c && c <= 0x2015) return "A";
    if (0x2020 <= c && c <= 0x2022) return "A";
    if (0x2024 <= c && c <= 0x2027) return "A";
    if (0x2032 <= c && c <= 0x2033) return "A";
    if (0x2081 <= c && c <= 0x2084) return "A";
    if (0x2121 <= c && c <= 0x2122) return "A";
    if (0x2153 <= c && c <= 0x2154) return "A";
    if (0x215B <= c && c <= 0x215E) return "A";
    if (0x2160 <= c && c <= 0x216B) return "A";
    if (0x2170 <= c && c <= 0x2179) return "A";
    if (0x2190 <= c && c <= 0x2194) return "A";
    if (0x2195 <= c && c <= 0x2199) return "A";
    if (0x21B8 <= c && c <= 0x21B9) return "A";
    if (0x2202 <= c && c <= 0x2203) return "A";
    if (0x2207 <= c && c <= 0x2208) return "A";
    if (0x221D <= c && c <= 0x2220) return "A";
    if (0x2227 <= c && c <= 0x222C) return "A";
    if (0x2234 <= c && c <= 0x2237) return "A";
    if (0x223C <= c && c <= 0x223D) return "A";
    if (0x2260 <= c && c <= 0x2261) return "A";
    if (0x2264 <= c && c <= 0x2267) return "A";
    if (0x226A <= c && c <= 0x226B) return "A";
    if (0x226E <= c && c <= 0x226F) return "A";
    if (0x2282 <= c && c <= 0x2283) return "A";
    if (0x2286 <= c && c <= 0x2287) return "A";
    if (0x231A <= c && c <= 0x231B) return "W";
    if (0x23E9 <= c && c <= 0x23EC) return "W";
    if (0x2460 <= c && c <= 0x249B) return "A";
    if (0x249C <= c && c <= 0x24E9) return "A";
    if (0x24EB <= c && c <= 0x24FF) return "A";
    if (0x2500 <= c && c <= 0x254B) return "A";
    if (0x2550 <= c && c <= 0x2573) return "A";
    if (0x2580 <= c && c <= 0x258F) return "A";
    if (0x2592 <= c && c <= 0x2595) return "A";
    if (0x25A0 <= c && c <= 0x25A1) return "A";
    if (0x25A3 <= c && c <= 0x25A9) return "A";
    if (0x25B2 <= c && c <= 0x25B3) return "A";
    if (0x25BC <= c && c <= 0x25BD) return "A";
    if (0x25C6 <= c && c <= 0x25C8) return "A";
    if (0x25CE <= c && c <= 0x25D1) return "A";
    if (0x25E2 <= c && c <= 0x25E5) return "A";
    if (0x25FD <= c && c <= 0x25FE) return "W";
    if (0x2605 <= c && c <= 0x2606) return "A";
    if (0x260E <= c && c <= 0x260F) return "A";
    if (0x2614 <= c && c <= 0x2615) return "W";
    if (0x2648 <= c && c <= 0x2653) return "W";
    if (0x2660 <= c && c <= 0x2661) return "A";
    if (0x2663 <= c && c <= 0x2665) return "A";
    if (0x2667 <= c && c <= 0x266A) return "A";
    if (0x266C <= c && c <= 0x266D) return "A";
    if (0x269E <= c && c <= 0x269F) return "A";
    if (0x26AA <= c && c <= 0x26AB) return "W";
    if (0x26BD <= c && c <= 0x26BE) return "W";
    if (0x26C4 <= c && c <= 0x26C5) return "W";
    if (0x26C6 <= c && c <= 0x26CD) return "A";
    if (0x26CF <= c && c <= 0x26D3) return "A";
    if (0x26D5 <= c && c <= 0x26E1) return "A";
    if (0x26E8 <= c && c <= 0x26E9) return "A";
    if (0x26EB <= c && c <= 0x26F1) return "A";
    if (0x26F2 <= c && c <= 0x26F3) return "W";
    if (0x26F6 <= c && c <= 0x26F9) return "A";
    if (0x26FB <= c && c <= 0x26FC) return "A";
    if (0x26FE <= c && c <= 0x26FF) return "A";
    if (0x270A <= c && c <= 0x270B) return "W";
    if (0x2753 <= c && c <= 0x2755) return "W";
    if (0x2776 <= c && c <= 0x277F) return "A";
    if (0x2795 <= c && c <= 0x2797) return "W";
    if (0x2B1B <= c && c <= 0x2B1C) return "W";
    if (0x2B56 <= c && c <= 0x2B59) return "A";
    if (0x2E80 <= c && c <= 0x2E99) return "W";
    if (0x2E9B <= c && c <= 0x2EF3) return "W";
    if (0x2F00 <= c && c <= 0x2FD5) return "W";
    if (0x2FF0 <= c && c <= 0x2FFB) return "W";
    if (0x3001 <= c && c <= 0x3003) return "W";
    if (0x3012 <= c && c <= 0x3013) return "W";
    if (0x301E <= c && c <= 0x301F) return "W";
    if (0x3021 <= c && c <= 0x3029) return "W";
    if (0x302A <= c && c <= 0x302D) return "W";
    if (0x302E <= c && c <= 0x302F) return "W";
    if (0x3031 <= c && c <= 0x3035) return "W";
    if (0x3036 <= c && c <= 0x3037) return "W";
    if (0x3038 <= c && c <= 0x303A) return "W";
    if (0x3041 <= c && c <= 0x3096) return "W";
    if (0x3099 <= c && c <= 0x309A) return "W";
    if (0x309B <= c && c <= 0x309C) return "W";
    if (0x309D <= c && c <= 0x309E) return "W";
    if (0x30A1 <= c && c <= 0x30FA) return "W";
    if (0x30FC <= c && c <= 0x30FE) return "W";
    if (0x3105 <= c && c <= 0x312F) return "W";
    if (0x3131 <= c && c <= 0x318E) return "W";
    if (0x3190 <= c && c <= 0x3191) return "W";
    if (0x3192 <= c && c <= 0x3195) return "W";
    if (0x3196 <= c && c <= 0x319F) return "W";
    if (0x31A0 <= c && c <= 0x31BF) return "W";
    if (0x31C0 <= c && c <= 0x31E3) return "W";
    if (0x31F0 <= c && c <= 0x31FF) return "W";
    if (0x3200 <= c && c <= 0x321E) return "W";
    if (0x3220 <= c && c <= 0x3229) return "W";
    if (0x322A <= c && c <= 0x3247) return "W";
    if (0x3248 <= c && c <= 0x324F) return "A";
    if (0x3251 <= c && c <= 0x325F) return "W";
    if (0x3260 <= c && c <= 0x327F) return "W";
    if (0x3280 <= c && c <= 0x3289) return "W";
    if (0x328A <= c && c <= 0x32B0) return "W";
    if (0x32B1 <= c && c <= 0x32BF) return "W";
    if (0x32C0 <= c && c <= 0x32FF) return "W";
    if (0x3300 <= c && c <= 0x33FF) return "W";
    if (0x3400 <= c && c <= 0x4DBF) return "W";
    if (0x4E00 <= c && c <= 0x9FFC) return "W";
    if (0x9FFD <= c && c <= 0x9FFF) return "W";
    if (0xA000 <= c && c <= 0xA014) return "W";
    if (0xA016 <= c && c <= 0xA48C) return "W";
    if (0xA490 <= c && c <= 0xA4C6) return "W";
    if (0xA960 <= c && c <= 0xA97C) return "W";
    if (0xAC00 <= c && c <= 0xD7A3) return "W";
    if (0xE000 <= c && c <= 0xF8FF) return "A";
    if (0xF900 <= c && c <= 0xFA6D) return "W";
    if (0xFA6E <= c && c <= 0xFA6F) return "W";
    if (0xFA70 <= c && c <= 0xFAD9) return "W";
    if (0xFADA <= c && c <= 0xFAFF) return "W";
    if (0xFE00 <= c && c <= 0xFE0F) return "A";
    if (0xFE10 <= c && c <= 0xFE16) return "W";
    if (0xFE31 <= c && c <= 0xFE32) return "W";
    if (0xFE33 <= c && c <= 0xFE34) return "W";
    if (0xFE45 <= c && c <= 0xFE46) return "W";
    if (0xFE49 <= c && c <= 0xFE4C) return "W";
    if (0xFE4D <= c && c <= 0xFE4F) return "W";
    if (0xFE50 <= c && c <= 0xFE52) return "W";
    if (0xFE54 <= c && c <= 0xFE57) return "W";
    if (0xFE5F <= c && c <= 0xFE61) return "W";
    if (0xFE64 <= c && c <= 0xFE66) return "W";
    if (0xFE6A <= c && c <= 0xFE6B) return "W";
    if (0xFF01 <= c && c <= 0xFF03) return "F";
    if (0xFF05 <= c && c <= 0xFF07) return "F";
    if (0xFF0E <= c && c <= 0xFF0F) return "F";
    if (0xFF10 <= c && c <= 0xFF19) return "F";
    if (0xFF1A <= c && c <= 0xFF1B) return "F";
    if (0xFF1C <= c && c <= 0xFF1E) return "F";
    if (0xFF1F <= c && c <= 0xFF20) return "F";
    if (0xFF21 <= c && c <= 0xFF3A) return "F";
    if (0xFF41 <= c && c <= 0xFF5A) return "F";
    if (0xFF64 <= c && c <= 0xFF65) return "H";
    if (0xFF66 <= c && c <= 0xFF6F) return "H";
    if (0xFF71 <= c && c <= 0xFF9D) return "H";
    if (0xFF9E <= c && c <= 0xFF9F) return "H";
    if (0xFFA0 <= c && c <= 0xFFBE) return "H";
    if (0xFFC2 <= c && c <= 0xFFC7) return "H";
    if (0xFFCA <= c && c <= 0xFFCF) return "H";
    if (0xFFD2 <= c && c <= 0xFFD7) return "H";
    if (0xFFDA <= c && c <= 0xFFDC) return "H";
    if (0xFFE0 <= c && c <= 0xFFE1) return "F";
    if (0xFFE5 <= c && c <= 0xFFE6) return "F";
    if (0xFFE9 <= c && c <= 0xFFEC) return "H";
    if (0xFFED <= c && c <= 0xFFEE) return "H";
    if (0x16FE0 <= c && c <= 0x16FE1) return "W";
    if (0x16FF0 <= c && c <= 0x16FF1) return "W";
    if (0x17000 <= c && c <= 0x187F7) return "W";
    if (0x18800 <= c && c <= 0x18AFF) return "W";
    if (0x18B00 <= c && c <= 0x18CD5) return "W";
    if (0x18D00 <= c && c <= 0x18D08) return "W";
    if (0x1B000 <= c && c <= 0x1B0FF) return "W";
    if (0x1B100 <= c && c <= 0x1B11E) return "W";
    if (0x1B150 <= c && c <= 0x1B152) return "W";
    if (0x1B164 <= c && c <= 0x1B167) return "W";
    if (0x1B170 <= c && c <= 0x1B2FB) return "W";
    if (0x1F100 <= c && c <= 0x1F10A) return "A";
    if (0x1F110 <= c && c <= 0x1F12D) return "A";
    if (0x1F130 <= c && c <= 0x1F169) return "A";
    if (0x1F170 <= c && c <= 0x1F18D) return "A";
    if (0x1F18F <= c && c <= 0x1F190) return "A";
    if (0x1F191 <= c && c <= 0x1F19A) return "W";
    if (0x1F19B <= c && c <= 0x1F1AC) return "A";
    if (0x1F200 <= c && c <= 0x1F202) return "W";
    if (0x1F210 <= c && c <= 0x1F23B) return "W";
    if (0x1F240 <= c && c <= 0x1F248) return "W";
    if (0x1F250 <= c && c <= 0x1F251) return "W";
    if (0x1F260 <= c && c <= 0x1F265) return "W";
    if (0x1F300 <= c && c <= 0x1F320) return "W";
    if (0x1F32D <= c && c <= 0x1F335) return "W";
    if (0x1F337 <= c && c <= 0x1F37C) return "W";
    if (0x1F37E <= c && c <= 0x1F393) return "W";
    if (0x1F3A0 <= c && c <= 0x1F3CA) return "W";
    if (0x1F3CF <= c && c <= 0x1F3D3) return "W";
    if (0x1F3E0 <= c && c <= 0x1F3F0) return "W";
    if (0x1F3F8 <= c && c <= 0x1F3FA) return "W";
    if (0x1F3FB <= c && c <= 0x1F3FF) return "W";
    if (0x1F400 <= c && c <= 0x1F43E) return "W";
    if (0x1F442 <= c && c <= 0x1F4FC) return "W";
    if (0x1F4FF <= c && c <= 0x1F53D) return "W";
    if (0x1F54B <= c && c <= 0x1F54E) return "W";
    if (0x1F550 <= c && c <= 0x1F567) return "W";
    if (0x1F595 <= c && c <= 0x1F596) return "W";
    if (0x1F5FB <= c && c <= 0x1F5FF) return "W";
    if (0x1F600 <= c && c <= 0x1F64F) return "W";
    if (0x1F680 <= c && c <= 0x1F6C5) return "W";
    if (0x1F6D0 <= c && c <= 0x1F6D2) return "W";
    if (0x1F6D5 <= c && c <= 0x1F6D7) return "W";
    if (0x1F6EB <= c && c <= 0x1F6EC) return "W";
    if (0x1F6F4 <= c && c <= 0x1F6FC) return "W";
    if (0x1F7E0 <= c && c <= 0x1F7EB) return "W";
    if (0x1F90C <= c && c <= 0x1F93A) return "W";
    if (0x1F93C <= c && c <= 0x1F945) return "W";
    if (0x1F947 <= c && c <= 0x1F978) return "W";
    if (0x1F97A <= c && c <= 0x1F9CB) return "W";
    if (0x1F9CD <= c && c <= 0x1F9FF) return "W";
    if (0x1FA70 <= c && c <= 0x1FA74) return "W";
    if (0x1FA78 <= c && c <= 0x1FA7A) return "W";
    if (0x1FA80 <= c && c <= 0x1FA86) return "W";
    if (0x1FA90 <= c && c <= 0x1FAA8) return "W";
    if (0x1FAB0 <= c && c <= 0x1FAB6) return "W";
    if (0x1FAC0 <= c && c <= 0x1FAC2) return "W";
    if (0x1FAD0 <= c && c <= 0x1FAD6) return "W";
    if (0x20000 <= c && c <= 0x2A6DD) return "W";
    if (0x2A6DE <= c && c <= 0x2A6FF) return "W";
    if (0x2A700 <= c && c <= 0x2B734) return "W";
    if (0x2B735 <= c && c <= 0x2B73F) return "W";
    if (0x2B740 <= c && c <= 0x2B81D) return "W";
    if (0x2B81E <= c && c <= 0x2B81F) return "W";
    if (0x2B820 <= c && c <= 0x2CEA1) return "W";
    if (0x2CEA2 <= c && c <= 0x2CEAF) return "W";
    if (0x2CEB0 <= c && c <= 0x2EBE0) return "W";
    if (0x2EBE1 <= c && c <= 0x2F7FF) return "W";
    if (0x2F800 <= c && c <= 0x2FA1D) return "W";
    if (0x2FA1E <= c && c <= 0x2FA1F) return "W";
    if (0x2FA20 <= c && c <= 0x2FFFD) return "W";
    if (0x30000 <= c && c <= 0x3134A) return "W";
    if (0x3134B <= c && c <= 0x3FFFD) return "W";
    if (0xE0100 <= c && c <= 0xE01EF) return "A";
    if (0xF0000 <= c && c <= 0xFFFFD) return "A";
    if (0x100000 <= c && c <= 0x10FFFD) return "A";
    return "N";
}
