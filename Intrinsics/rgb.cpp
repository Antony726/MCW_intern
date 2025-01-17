
#include<iostream>
#include<immintrin.h>

int main(){
    __m128 rconst = _mm_set1_ps(0.29891f);
    __m128 gconst = _mm_set1_ps(0.58661f);
    __m128 bconst = _mm_set1_ps(0.11448f);
    __m128 max = _mm_set1_ps(255.0f);
    __m128 r, g, b;
    int num = 2;
    int src[] = {255, 0, 0, 0, 255, 255, 255, 0};
    int result[8] = {0};
    __m128 zer = _mm_setzero_ps();

    for (int i = 0; i < num; i++) {
        r = _mm_set1_ps((float)src[i * 4]);
        g = _mm_set1_ps((float)src[i * 4 + 1]);
        b = _mm_set1_ps((float)src[i * 4 + 2]);
        __m128 temp = _mm_mul_ps(r, rconst); 
        __m128 y = _mm_add_ps(temp, zer);
        temp = _mm_mul_ps(g, gconst); 
        y = _mm_add_ps(temp, y);
        temp = _mm_mul_ps(b, bconst); 
        y = _mm_add_ps(temp, y);
        int res = _mm_cvttss_si32(y);
        if (res > 255) {
            res = 255;
        }
        result[i * 4] = result[i * 4 + 1] = result[i * 4 + 2] = res;
    }
    for (int i = 0; i < num * 4; i++) {
        std::cout << result[i] << "\n";
    }

    return 0;
}
