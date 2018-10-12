#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x)  begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;
typedef uint32_t u32;
typedef uint8_t u8;



vector<u32> buf;
vector<u8> arr;

u8 consume() {
    if (arr.empty()) throw 0;
    u8 ret = arr.back();
    arr.pop_back();
    return ret;
}

void end_subseq() {
    _debug("%d", buf.size());
    if (buf.size() >= 3) {
        for (u32 v : buf) printf("%X ", v);
        puts("");
    }
    buf.clear();
}

void concat(u32 prefix, int num) {
    while (num--) {
        u32 val = consume();
        if ((val >> 6) != 0b10) {
            arr.push_back(val);
            throw 0;
        }
        prefix = (prefix << 6) | (val & 0b0011'1111);
    }
    buf.push_back(prefix);

}

int is_decodable(u8 ch) {
    if ((ch >> 7) == 0) return 1;
    else if ((ch >> 5) == 0b110) return 2;
    else if ((ch >> 4) == 0b1110) return 3;
    else if ((ch >> 3) == 0b11110) return 4;
    else if ((ch >> 2) == 0b111110) return 5;
    else if ((ch >> 1) == 0b1111110) return 6;
    else return 0;
}

int main() {
    u32 ch;
    while (scanf("%X", &ch) == 1) arr.push_back(ch);
    reverse(range(arr));
    _debug("%lu", arr.size());
    while (arr.size()) {
        int type = is_decodable(arr.back());
        _debug("type = %d", type);
        try {
            switch (type) {
                case 0:
                    consume();
                    throw 0;
                case 1:
                    concat(consume() & 0b0111'1111, 0);
                    break;
                case 2:
                    concat(consume() & 0b0001'1111, 1);
                    break;
                case 3:
                    concat(consume() & 0b0000'1111, 2);
                    break;
                case 4:
                    concat(consume() & 0b0000'0111, 3);
                    break;
                case 5:
                    concat(consume() & 0b0000'0011, 4);
                    break;
                case 6:
                    concat(consume() & 0b0000'0001, 5);
                    break;
                default:
                    assert(0);
            }
        } catch(...) { // illegal
            end_subseq();
        }
    }
    end_subseq();
    return 0;
}
