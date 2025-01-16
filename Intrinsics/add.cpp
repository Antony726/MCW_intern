#include <stdio.h>
#include <xmmintrin.h>
#include <iostream>

int main(){
    __m128i va = _mm_set_epi32(1,2,3,4);
    __m128i vasum = _mm_set1_epi32(4);
    __m128i res = _mm_setzero_si128();
    for(int i=0; i<128; i+=4){
        res = _mm_add_epi32(res, va);
        va = _mm_add_epi32(va, vasum);
        if(i+4>128){
            break;
        }
    }
    
    int *psum,sum;
    psum = (int *) &res;
    

    sum  = psum[0] + psum[1] + psum[2] + psum[3];

    int b=0;
    for(int i=1;i<=128;i++){
        b+=i;
    }


    
    std::cout<<"Sum of intrinsic :"<<sum<<"\n";
    std::cout<<"Sum of normal fum :"<<b<<"\n";



    return 0;
}