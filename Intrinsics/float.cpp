#include<xmmintrin.h>
#include<iostream>

int main(){
    __m128i inp = _mm_set_epi32(1,2,3,4);
    __m128 fm = _mm_set1_ps(1.01f);
    __m128 res ;
    __m128 itof = _mm_cvtepi32_ps(inp);
    res = _mm_mul_ps(itof,fm);
    float *psum;
    psum = (float *) &res;

    for(int i=0;i<4;i++){
        std::cout<<psum[i]<<"\n";

    }

}