#include<iostream>
#include<vector>
#include "c7x.h"
#include "c7x_scalable.h"

using namespace c7x;
using namespace std;

int main(){
    cout<<"Enter Rows and col and channel for A :";
    int32_t r1,c1,ch1,ch2,r2,c2;
    cin>>r1>>c1>>ch1;

    cout<<"Enter Rows and col and channel for B :";
    cin>>r2>>c2>>ch2;

    int32_t mat1[ch1][r1][c1];
    int32_t mat2[ch2][r2][c2];
    if(c1!=r2 && ch1!=ch2){
        cout<<"Enter Valid dimensions ";
        return -1;
    }
    int32_t res[ch1][r1][c2];

    int32_t count=0;
    for(int32_t k=0; k<ch1; k++){
        for(int32_t i=0; i<r1; i++){
            for(int32_t j=0; j<c1; j++){
                mat1[k][i][j]=i+1;
            }
        }
    }
    count=0;
    for(int32_t k=0; k<ch2; k++){
        for(int32_t i=0; i<r2; i++){
            for(int32_t j=0; j<c2; j++){
                mat2[k][i][j]=i+1;
            }
        }
    }

    // for(int32_t k=0; k<ch2; k++){
    //     for(int32_t i=0; i<r2; i++){
    //         for(int32_t j=0; j<c2; j++){
    //             cout<<mat1[k][i][j]<<" | ";
    //         }
    //         cout<<"\n";
    //     }
    // }

    for(int32_t k=0; k<ch1; k++){
        for(int32_t i=0; i<r1; i++){
            for(int32_t j=0; j<c2; j++){
                res[k][i][j]=0;
            }
        }

    }
    
    __SE_TEMPLATE_v1 seTemplate = __gen_SE_TEMPLATE_v1();
    seTemplate.ELETYPE = se_eletype<int_vec>::value;
    seTemplate.VECLEN = se_veclen<int_vec>::value;
    // seTemplate.TRANSPOSE = __SE_TRANSPOSE_32BIT;
    seTemplate.DIMFMT = __SE_DIMFMT_3D;
    seTemplate.ELEDUP    = __SE_ELEDUP_16X;
    // const int vec_len = element_count_of<int_vec>::value;
    seTemplate.ICNT0 = c1;
    seTemplate.ICNT1 = r1;
    seTemplate.ICNT2 = ch1;
    seTemplate.DIM1 = c1;
    seTemplate.DIM2 = (c1*r1);
   

    __SE0_OPEN((void *)&mat1[0], seTemplate);

    __SE_TEMPLATE_v1 seTemplate1 = __gen_SE_TEMPLATE_v1();
    seTemplate1.ELETYPE = se_eletype<int_vec>::value;
    seTemplate1.VECLEN = se_veclen<int_vec>::value;
    // seTemplate1.TRANSPOSE = __SE_TRANSPOSE_32BIT;
    seTemplate1.DIMFMT = __SE_DIMFMT_3D;
    const int vec_len = element_count_of<int_vec>::value;
    seTemplate1.ICNT0 = c2;
    seTemplate1.ICNT1 = r2;
    seTemplate1.ICNT2 = ch2;
    // seTemplate1.ICNT3 = ch2;
    seTemplate1.DIM1 = c2;
    seTemplate1.DIM2 = (c2*r2);
    // seTemplate1.DIM3 = c2*r2;

    __SE1_OPEN((void *)&mat2[0], seTemplate1);

    __SA_TEMPLATE_v1 saTemplate = __gen_SA_TEMPLATE_v1();
    saTemplate.VECLEN = sa_veclen<int_vec>::value;

    saTemplate.DIMFMT = __SA_DIMFMT_3D;
    saTemplate.ICNT0 = c2;
    saTemplate.ICNT1 = r1;
    saTemplate.ICNT2 = ch1;
    saTemplate.DIM1 = c2;
    saTemplate.DIM2 = c2*r1;

    __SA0_OPEN(saTemplate);
    for(int i=0; i<r1; i++){
        __SE1_OPEN((void *)&mat2[0], seTemplate1);
        int_vec addd = (int_vec)(0);
        for(int i=0; i<(ch1*r1*(c2/vec_len)); i++){
            int_vec data1 = strm_eng<0, int_vec>::get_adv();
            int_vec data2 = strm_eng<1, int_vec>::get_adv();
            int_vec mul = __vmpyww_vvv(data1,data2);
            addd = __vaddw_vvv(addd,mul);
            data1.print();
            data2.print();
        }
        __vpred pred = strm_agen<0, int_vec>::get_vpred();
        int_vec * addr = strm_agen<0, int_vec>::get_adv(&res[0][0][0]);
        __vstore_pred(pred, addr, addd);

    }

    

    

    

    int32_t mres[ch1][r1][c2];

    for(int32_t k=0; k<ch1; k++){
        for(int32_t i=0; i<r1; i++){
            for(int32_t j=0; j<c2; j++){
                mres[k][i][j]=0;
            }
        }

    }

    for(int32_t c=0; c<ch1; c++){
        for(int32_t i=0; i<r1; i++){
            for(int32_t j=0; j<c2; j++){
                for(int32_t k=0; k<c1; k++){
                    mres[c][i][j]+=mat1[c][i][k]*mat2[c][k][j];
                }
            }
        }
    }
    // cout<<"\n"<<"-------------------------------------------------------";
    for(int32_t k=0; k<ch1; k++){
        for(int32_t i=0; i<r1; i++){
            for(int32_t j=0; j<c2; j++){
                if(mres[k][i][j]!=res[k][i][j]){
                    cout<<"Not equal";
                    return -1;
                }
                
            }
            
        }

    }
    cout<<"Equal"<<"\n";
    return 0;



   

}