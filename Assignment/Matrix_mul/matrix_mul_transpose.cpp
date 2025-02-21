#include<iostream>
#include<vector>
#include "c7x.h"
#include "c7x_scalable.h"

using namespace c7x;
using namespace std;



int main(){
    int32_t r1=16, c1=16, ch1=1;
    int32_t arr1[ch1][r1][c1];
    int32_t arr2[ch1][r1][c1];
    int32_t res[ch1][r1][c1];

    int32_t count = 0;
    for(int i=0;i<ch1;i++){
        for(int j=0; j<r1; j++){
            for(int k=0; k<c1; k++){
                arr1[i][j][k]=count++;
            }
        }
    }
    count = 0;
    for(int i=0;i<ch1;i++){
        for(int j=0; j<r1; j++){
            for(int k=0; k<c1; k++){
                arr2[i][j][k]=count++;
            }
        }
    }

    for(int i=0;i<ch1;i++){
        for(int j=0; j<r1; j++){
            for(int k=0; k<c1; k++){
                res[i][j][k]=0;
            }
        }
    }
    const int vec_len = element_count_of<int_vec>::value;

    __SE_TEMPLATE_v1 seTemplate = __gen_SE_TEMPLATE_v1();
    seTemplate.ELETYPE = se_eletype<int_vec>::value;
    seTemplate.VECLEN = se_veclen<int_vec>::value;
    seTemplate.DIMFMT = __SE_DIMFMT_3D;
    seTemplate.ICNT0 = c1;
    seTemplate.ICNT1 = r1;
    seTemplate.ICNT2 = ch1;
    seTemplate.DIM1 = c1;
    seTemplate.DIM2 = c1*r1;
    __SE0_OPEN((void *)&arr1[0], seTemplate);

    __SE_TEMPLATE_v1 seTemplate1 = __gen_SE_TEMPLATE_v1();
    seTemplate1.ELETYPE = se_eletype<int_vec>::value;
    seTemplate1.VECLEN = se_veclen<int_vec>::value;
    seTemplate1.TRANSPOSE    = __SE_TRANSPOSE_32BIT;
    seTemplate1.DIMFMT = __SE_DIMFMT_4D;
    seTemplate1.ICNT0 = c1;
    seTemplate1.ICNT1 = vec_len;
    seTemplate1.ICNT2 = r1/vec_len;
    seTemplate1.ICNT3 = ch1;

    seTemplate1.DIM1 = c1;
    seTemplate1.DIM2 = c1*vec_len;
    seTemplate1.DIM2 = c1*r1;

    __SA_TEMPLATE_v1 saTemplate = __gen_SA_TEMPLATE_v1();
    saTemplate.VECLEN = sa_veclen<int_vec>::value;
    saTemplate.DIMFMT = __SA_DIMFMT_2D;
    saTemplate.ICNT0 = 1;
    saTemplate.ICNT1 = 256;
    // saTemplate.ICNT2 = 1;
    saTemplate.DIM1 = 1;
    __SA0_OPEN(saTemplate);



    
    
    for(int32_t ctr = 0; ctr < (ch1 * r1 * (c1/vec_len)); ctr++) {
        int_vec data1 = strm_eng<0, int_vec>::get_adv();
        __SE1_OPEN((void *)&arr2[0], seTemplate1);
        int_vec addd = (int_vec)(0);
        for(int32_t i=0; i<16; i++){
            int_vec data2 = strm_eng<1, int_vec>::get_adv();
            int_vec mul= __vmpyww_vvv(data1,data2);
            // addd=__vaddw_vvv(addd,vec_c);
            int32_t accu = mul.s0()+mul.s1()+mul.s2()+mul.s3()+mul.s4()+mul.s5()+mul.s6()+mul.s7()+mul.s8()+mul.s9()+mul.sa()+mul.sb()+mul.sc()+mul.sd()+mul.se()+mul.sf();
            mul.print();
            cout<<accu;
            int_vec accu_v = (int_vec)(accu);
            __vpred pred = strm_agen<0, int_vec>::get_vpred();
            int_vec * addr = strm_agen<0, int_vec>::get_adv(&res[0][0][0]);
            __vstore_pred(pred, addr, accu_v);

            data1.print();
            data2.print();





        }
        
    

    }

    for(int i=0; i<ch1; i++){
        for(int j=0; j<r1; j++){
            for(int k=0; k<c1; k++){
                cout<<res[i][j][k]<<" | ";
            }
            cout<<"\n";
        }
    }
    int32_t mres[ch1][r1][c1];

    for(int32_t k=0; k<ch1; k++){
        for(int32_t i=0; i<r1; i++){
            for(int32_t j=0; j<c1; j++){
                mres[k][i][j]=0;
            }
        }

    }

    for(int32_t c=0; c<ch1; c++){
        for(int32_t i=0; i<r1; i++){
            for(int32_t j=0; j<c1; j++){
                for(int32_t k=0; k<c1; k++){
                    mres[c][i][j]+=arr1[c][i][k]*arr2[c][k][j];
                }
            }
        }
    }

    for(int32_t k=0; k<ch1; k++){
            for(int32_t i=0; i<r1; i++){
                for(int32_t j=0; j<c1; j++){
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