#include<iostream>
#include<vector>
#include "c7x.h"
#include "c7x_scalable.h"
#include <cstdlib> 
#include <ctime>
#include<chrono>

using namespace c7x;
using namespace std;

int main()
    auto startt = chrono::high_resolution_clock::now();
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
   

    __SE_TEMPLATE_v1 seTemplate1 = __gen_SE_TEMPLATE_v1();
    seTemplate1.ELETYPE = se_eletype<int_vec>::value;
    seTemplate1.VECLEN = se_veclen<int_vec>::value;
    seTemplate1.TRANSPOSE    = __SE_TRANSPOSE_32BIT;
    seTemplate1.DIMFMT = __SE_DIMFMT_4D;
    seTemplate1.ICNT0 = c2;
    seTemplate1.ICNT1 = r2>16?vec_len:r2;
    seTemplate1.ICNT2 = ceil(r2/16.0);
    seTemplate1.ICNT3 = r2*ceil(c2/16.0)*c1;
    seTemplate1.DIM1 = c2;
    seTemplate1.DIM2 = r2>16?c2*vec_len:c2*r2;
    seTemplate1.DIM3 = 0;
    // seTemplate1.CBK0 = 0;
    // seTemplate1.AM1 = __SE_AM_CIRC_CBK0;

    __SA_TEMPLATE_v1 saTemplate = __gen_SA_TEMPLATE_v1();
    saTemplate.VECLEN = sa_veclen<int_vec>::value;
    saTemplate.DIMFMT = __SA_DIMFMT_3D;
    saTemplate.ICNT0 = c2;
    saTemplate.ICNT1 = ceil(c1/16.0);
    saTemplate.ICNT2 = r1;
    saTemplate.DIM1 = 0;
    saTemplate.DIM2 = c2;

    __SE0_OPEN((void *)&arr_a[0], seTemplate);
    __SE1_OPEN((void *)&arr_b[0], seTemplate1);
    __SA0_OPEN(saTemplate);
    int iteration2 = 0;
    auto start = chrono::high_resolution_clock::now();
    for(int i=0; i<r1*ceil(c1/16.0); i++){
        int_vec a = strm_eng<0, int_vec>::get_adv();
        int32_t res_i[16];
        for(int k=0; k<16; k++){
            res_i[k]=0;
            iteration2++;
        }
        int32_t *idx = &res_i[0];
        for(int j=0; j<c2; j++){
            
            int_vec b = strm_eng<1, int_vec>::get_adv();
            
            // cout<<"\n I :"<<i<<"\n";
            // a.print();
            // b.print();


            int_vec mul= __vmpyww_vvv(a,b);

            int32_t accu = mul.s0()+mul.s1()+mul.s2()+mul.s3()+mul.s4()+mul.s5()+mul.s6()+mul.s7()+mul.s8()+mul.s9()+mul.sa()+mul.sb()+mul.sc()+mul.sd()+mul.se()+mul.sf();
            // mul.print();
            iteration2++;
            if(j%vec_len==0 && j!=0 && j!=1){
                int_vec arr_res = *(int_vec *)(idx);

                __vpred pred = strm_agen<0, int_vec>::get_vpred();
                int_vec vIn = *strm_agen<0, int_vec>::get(&res[0]);
                arr_res = __vaddw_vvv(arr_res,vIn);
                int_vec * addr = strm_agen<0, int_vec>::get_adv(&res[0][0]);
                __vstore_pred(pred, addr, arr_res);
                


            }
            res_i[j%vec_len]=accu;

           



        }
        
        int_vec arr_res = *(int_vec *)(idx);
        __vpred pred = strm_agen<0, int_vec>::get_vpred();
        int_vec vIn = *strm_agen<0, int_vec>::get(&res[0]);
        arr_res = __vaddw_vvv(arr_res,vIn);
        int_vec * addr = strm_agen<0, int_vec>::get_adv(&res[0][0]);
        __vstore_pred(pred, addr, arr_res);

        
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout <<"\n"<< "Time taken by Add matrix SE SA Intrinsic function: " << duration.count() << " microseconds" << endl;
    
    cout<<"\n";
    for(int i=0; i<r1; i++){
        for(int j=0; j<c2; j++){
            cout<<res[i][j]<<" | ";
        }
        cout<<"\n";
    }
    
    
    int32_t mres[r1][c2];

    for(int i=0; i<r1; i++){
        for(int j=0; j<c2; j++){
            mres[i][j]=0;
        }
    }
    int iteration1 = 0;
    for(int i=0; i<r1; i++){
        for(int j=0; j<c2; j++){
            for(int k=0; k<c1; k++){
                mres[i][j]+=arr_a[i][k]*arr_b[k][j];
                iteration1++;
            }
        }
    }
    cout<<"\n";
    for(int i=0; i<r1; i++){
        for(int j=0; j<c2; j++){
            cout<<mres[i][j]<<" | ";
        }
        cout<<"\n";
    }

    for(int i=0; i<r1; i++){
        for(int j=0; j<c2; j++){
            if(mres[i][j]!=res[i][j]){
                cout<<"Not Equal \n";
                return -1;
            }
        }
    }
    cout<<"Equal \n";
    cout<<"Iteration 1 : "<<iteration1<<endl;
    cout<<"Iteration 2 : "<<iteration2<<endl;
    float resx = iteration1/(float)iteration2;
    cout<<"Your code is "<<resx<<"Times faster than normal MUL"<<endl;
    auto stopp = chrono::high_resolution_clock::now();
    auto durationn = chrono::duration_cast<chrono::microseconds>(stopp - startt);
    cout <<"\n"<< "Time taken by Add matrix normal function: " << durationn.count() << " microseconds" << endl;


