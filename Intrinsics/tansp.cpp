#include <tmmintrin.h>
#include <iostream>
using namespace std;

int main(){
    float f[4][4] = {
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12},
        {13,14,15,16}
    }; 
    __m128 row0 = _mm_load_ps((float*)f[0]);
    __m128 row1 = _mm_load_ps((float*)f[1]);
    __m128 row2 = _mm_load_ps((float*)f[2]);
    __m128 row3 = _mm_load_ps((float*)f[3]);
    __m128 tmp0 = _mm_unpacklo_ps(row0, row1);
    __m128 tmp2 = _mm_unpacklo_ps(row2, row3);
    __m128 tmp1 = _mm_unpackhi_ps(row0, row1);
    __m128 tmp3 = _mm_unpackhi_ps(row2, row3);
    row0 = _mm_movelh_ps(tmp0, tmp2);
    row1 = _mm_movehl_ps(tmp2, tmp0);
    row2 = _mm_movelh_ps(tmp1, tmp3);
    row3 = _mm_movehl_ps(tmp3, tmp1);
    float a[4][4];
    _mm_storeu_ps((float*)&a[0],row0);
    _mm_storeu_ps((float*)&a[1],row1);
    _mm_storeu_ps((float*)&a[2],row2);
    _mm_storeu_ps((float*)&a[3],row3);

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            cout<<a[i][j]<<" | ";
        }
        cout<<"\n";
    }
    return 0;

}