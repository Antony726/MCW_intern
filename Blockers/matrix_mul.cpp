#include<iostream>
#include<vector>
#include "c7x.h"
#include "c7x_scalable.h"

using namespace c7x;
using namespace std;

int main(){
    int32_t r1,r2,c1,c2;
    // cout<<"MATRIX MULTIPLICATION USING PREDICATION \n";
    // cout<<"Enter Row and Col for A: ";
    // cin>>r1>>c1;
    // cout<<"Enter Row and Col for B: ";
    // cin>>r2>>c2;
    r1=16;
    r2 = 16;
    c1 = 16;
    c2 = 16;

    if(c1!=r2){
        cout<<"Enter valid Dimensions!!!";
        return -1;
    }

    int32_t arr_a[r1][c1];
    int32_t arr_b[r2][c2];
    int32_t res[r1][c2];

    int32_t count=0;
    for(int32_t i=0; i<r1; i++){
        for(int32_t j=0; j<c1; j++){
            arr_a[i][j] = count++;
        }
    }

    count=0;
    for(int32_t i=0; i<r2; i++){
        for(int32_t j=0; j<c2; j++){
            arr_b[i][j] = count++;
        }
    }


    for(int32_t i=0; i<r1; i++){
        for(int32_t j=0; j<c2; j++){
            res[i][j] = count++;
        }
    }

    __SE_TEMPLATE_v1 seTemplate = __gen_SE_TEMPLATE_v1();
    seTemplate.ELETYPE = se_eletype<int_vec>::value;
    seTemplate.VECLEN = se_veclen<int_vec>::value;
    seTemplate.ELEDUP    = __SE_ELEDUP_16X;
    seTemplate.DIMFMT = __SE_DIMFMT_1D;
    seTemplate.ICNT0 = c1*r1;
    // seTemplate.ICNT1 = r1;
    // seTemplate.DIM1 = c1;

    __SE_TEMPLATE_v1 seTemplate1 = __gen_SE_TEMPLATE_v1();
    seTemplate1.ELETYPE = se_eletype<int_vec>::value;
    seTemplate1.VECLEN = se_veclen<int_vec>::value;
    // seTemplate1.ELEDUP    = __SE_ELEDUP_16X
    seTemplate1.DIMFMT = __SE_DIMFMT_2D;
    seTemplate1.ICNT0 = c1;
    seTemplate1.ICNT1 = r1;
    seTemplate1.DIM1 = c1;
    seTemplate1.CBK0 = 0;
    seTemplate1.AM1 = __SE_AM_CIRC_CBK0;

    __SE0_OPEN((void *)&arr_a[0], seTemplate);
    __SE1_OPEN((void *)&arr_b[0], seTemplate1);

    for(int i=0; i<r1*c2; i++){
        int_vec a = strm_eng<0, int_vec>::get_adv();
        int_vec b = strm_eng<1, int_vec>::get_adv();

        // a.print();
        b.print();

    }


}


