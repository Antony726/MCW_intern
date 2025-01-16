#include<xmmintrin.h>
#include<iostream>
#include<immintrin.h>

int main(){
    __m128i inp = _mm_set_epi32(1,-89,69,-10);
    __m128 neg = _mm_set1_ps(-1.0f);
    __m128 zer = _mm_set1_ps(0.0f);
    __m128 impf = _mm_cvtepi32_ps(inp);
    __m128 mask = _mm_cmpgt_ps(neg,impf);
    __m128 mu = _mm_mul_ps(impf,neg);
    __m128 bb = _mm_blendv_ps(impf,mu,mask);
    float *res;
    res = (float *) &bb;

    for(int i=0;i<4;i++){ 
        std::cout<<res[i]<<"\n";

    }
    


}
