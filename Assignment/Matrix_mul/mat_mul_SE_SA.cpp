#include<iostream>
#include<vector>
#include "c7x.h"
#include "c7x_scalable.h"

using namespace c7x;
using namespace std;

int main(){
    int32_t r1,r2,c1,c2;
    cout<<"MATRIX MULTIPLICATION USING PREDICATION \n";
    cout<<"Enter Row and Col for A: ";
    cin>>r1>>c1;
    cout<<"Enter Row and Col for B: ";
    cin>>r2>>c2;
    // r1=32;
    // r2 = 64;
    // c1 = 64;
    // c2 = 32;

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
            res[i][j] = 0;
        }
    }

    int vec_len = element_count_of<int_vec>::value;

    __SE_TEMPLATE_v1 seTemplate = __gen_SE_TEMPLATE_v1();
    seTemplate.ELETYPE = se_eletype<int_vec>::value;
    seTemplate.VECLEN = se_veclen<int_vec>::value;
    // seTemplate.ELEDUP    = __SE_ELEDUP_16X;
    seTemplate.DIMFMT = __SE_DIMFMT_2D;
    seTemplate.ICNT0 = c1;

    seTemplate.ICNT1 = r1;
    seTemplate.DIM1 = c1;
    // seTemplate.ICNT1 = r1;
    // seTemplate.DIM1 = c1;

    __SE_TEMPLATE_v1 seTemplate1 = __gen_SE_TEMPLATE_v1();
    seTemplate1.ELETYPE = se_eletype<int_vec>::value;
    seTemplate1.VECLEN = se_veclen<int_vec>::value;
    // seTemplate1.ELEDUP    = __SE_ELEDUP_16X
    seTemplate1.TRANSPOSE    = __SE_TRANSPOSE_32BIT;
    seTemplate1.DIMFMT = __SE_DIMFMT_4D;
    seTemplate1.ICNT0 = c1;
    seTemplate1.ICNT1 = vec_len;
    seTemplate1.ICNT2 = r1/vec_len;
    seTemplate1.ICNT3 = r1*ceil(c1/vec_len)*c1;
    // seTemplate1.ICNT3 = c1/vec_len;
    // seTemplate1.ICNT4 = r1;
    seTemplate1.DIM1 = c1;
    seTemplate1.DIM2 = c1*vec_len;
    seTemplate1.DIM3 = 0;
    // seTemplate1.DIM3 = c1*r1;
    // seTemplate1.CBK0 = 0;
    // seTemplate1.AM1 = __SE_AM_CIRC_CBK0;

    __SA_TEMPLATE_v1 saTemplate = __gen_SA_TEMPLATE_v1();
    saTemplate.VECLEN = sa_veclen<int_vec>::value;
    saTemplate.DIMFMT = __SA_DIMFMT_3D;
    saTemplate.ICNT0 = c1;
    saTemplate.ICNT1 = ceil(c1/vec_len);
    saTemplate.ICNT2 = r1;
    // saTemplate.ICNT2 = c1;
    // saTemplate.ICNT3 = 2;
    saTemplate.DIM1 = 0;
    saTemplate.DIM2 = c1;
    // saTemplate.DIM2 = c1*r1;
    // saTemplate.DIM3 = 16;

    __SE0_OPEN((void *)&arr_a[0], seTemplate);
    __SE1_OPEN((void *)&arr_b[0], seTemplate1);
    __SA0_OPEN(saTemplate);

    for(int i=0; i<r1*ceil(c1/vec_len); i++){
        int_vec a = strm_eng<0, int_vec>::get_adv();
        int32_t res_i[16];
        for(int k=0; k<16; k++){
            res_i[k]=0;
        }
        int32_t *idx = &res_i[0];
        for(int j=0; j<c1; j++){
            
            int_vec b = strm_eng<1, int_vec>::get_adv();

            int_vec mul= __vmpyww_vvv(a,b);
            // addd=__vaddw_vvv(addd,vec_c);
            int32_t accu = mul.s0()+mul.s1()+mul.s2()+mul.s3()+mul.s4()+mul.s5()+mul.s6()+mul.s7()+mul.s8()+mul.s9()+mul.sa()+mul.sb()+mul.sc()+mul.sd()+mul.se()+mul.sf();
            // mul.print();
            if(j%vec_len==0 && j!=0 && j!=1){
                int_vec arr_res = *(int_vec *)(idx);
                // arr_res.print();

                __vpred pred = strm_agen<0, int_vec>::get_vpred();
                // cout<<"\n I :"<<i<<"\n";
                int_vec vIn = *strm_agen<0, int_vec>::get(&res[0]);
                arr_res = __vaddw_vvv(arr_res,vIn);
                // vIn.print();
                int_vec * addr = strm_agen<0, int_vec>::get_adv(&res[0][0]);
                __vstore_pred(pred, addr, arr_res);
                


            }
            res_i[j%vec_len]=accu;

            // cout<<"\n I :"<<i<<": \n";
            // a.print();
            // b.print();



        }
        int_vec arr_res = *(int_vec *)(idx);
        // arr_res.print();
        __vpred pred = strm_agen<0, int_vec>::get_vpred();
        int_vec vIn = *strm_agen<0, int_vec>::get(&res[0]);
        arr_res = __vaddw_vvv(arr_res,vIn);
        int_vec * addr = strm_agen<0, int_vec>::get_adv(&res[0][0]);
        __vstore_pred(pred, addr, arr_res);
        // for(int j=0; j<c2/vec_len; j++){
        //     // int_vec a = strm_eng<0, int_vec>::get_adv();
        //     a.print();
        //     cout<<"Next";
            
            
        // }
        // int_vec vIn = *strm_agen<0, int_vec>::get(&res[0]);
        // vIn.print();
        // b.print();
    }
    

    // for(int i=0; i<r1; i++){
    //     for(int j=0; j<c1; j++){
    //         cout<<res[i][j]<<" | ";
    //     }
    //     cout<<"\n";
    // }

    int32_t mres[r1][c2];

    for(int i=0; i<r1; i++){
        for(int j=0; j<c2; j++){
            mres[i][j]=0;
        }
    }

    for(int i=0; i<r1; i++){
        for(int j=0; j<c2; j++){
            for(int k=0; k<c1; k++){
                mres[i][j]+=arr_a[i][k]*arr_b[k][j];
            }
        }
    }

    for(int i=0; i<r1; i++){
        for(int j=0; j<c2; j++){
            if(mres[i][j]!=res[i][j]){
                cout<<"Not Equal \n";
                return -1;
            }
        }
    }
    cout<<"Equal";


}




// __SE_TEMPLATE_v1 seTemplate1 = __gen_SE_TEMPLATE_v1();
// seTemplate1.ELETYPE = se_eletype<int_vec>::value;
// seTemplate1.VECLEN = se_veclen<int_vec>::value;
// // seTemplate1.ELEDUP    = __SE_ELEDUP_16X
// seTemplate1.DIMFMT = __SE_DIMFMT_3D;
// seTemplate1.ICNT0 = vec_len;
// seTemplate1.ICNT1 = r1;
// seTemplate1.ICNT2 = c1/vec_len;
// seTemplate1.DIM1 = (c1/vec_len)*vec_len;
// seTemplate1.DIM2 = vec_len


// __SE_TEMPLATE_v1 seTemplate1 = __gen_SE_TEMPLATE_v1();
//     seTemplate1.ELETYPE = se_eletype<int_vec>::value;
//     seTemplate1.VECLEN = se_veclen<int_vec>::value;
//     // seTemplate1.ELEDUP    = __SE_ELEDUP_16X
//     // seTemplate.TRANSPOSE    = __SE_TRANSPOSE_32BIT;
//     seTemplate1.DIMFMT = __SE_DIMFMT_4D;
//     seTemplate1.ICNT0 = vec_len;
//     seTemplate1.ICNT1 = r1;
//     seTemplate1.ICNT2 = c1/vec_len;
//     seTemplate1.ICNT3 = r1;
//     seTemplate1.DIM1 = (c1/vec_len)*vec_len;
//     seTemplate1.DIM2 = vec_len;
//     seTemplate1.DIM3 = 0;