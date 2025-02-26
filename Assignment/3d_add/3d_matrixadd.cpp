#include<iostream>
#include<vector>
#include "c7x.h"
#include "c7x_scalable.h"

using namespace c7x;
using namespace std;

int main(){
    int32_t r1,r2,c1,c2,ch1;
    cout<<"Enter ROW and Col and Channel for A & B :";
    cin>>r1>>c1>>ch1;
    // cout<<"Enter ROW and Col for B :";
    r2=r1;
    c2=c1;

    int32_t arr_a[ch1][r1][c1];
    int32_t arr_b[ch1][r2][c2];
    int32_t res[ch1][r1][c2];

    int32_t count =0;
    for(int32_t k=0; k<ch1; k++){
        for(int32_t i=0; i<r1; i++){
            for(int32_t j=0; j<c1; j++){
                arr_a[k][i][j] = count++;
            }
        }
    }

    
    count =0;
    for(int32_t k=0; k<ch1; k++){
        for(int32_t i=0; i<r1; i++){
            for(int32_t j=0; j<c1; j++){
                arr_b[k][i][j] = count++;
            }
        }
    }

    for(int32_t k=0; k<ch1; k++){
        for(int32_t i=0; i<r1; i++){
            for(int32_t j=0; j<c1; j++){
                res[k][i][j] = 0;
            }
        }
    }

    __SE_TEMPLATE_v1 seTemplate = __gen_SE_TEMPLATE_v1();
    seTemplate.ELETYPE = se_eletype<int_vec>::value;
    seTemplate.VECLEN = se_veclen<int_vec>::value;
    seTemplate.DIMFMT = __SE_DIMFMT_1D;
    seTemplate.ICNT0 = c1*r1*ch1;
    // seTemplate.ICNT1 = r1;
    // seTemplate.DIM1 = c1;


    __SA_TEMPLATE_v1 saTemplate = __gen_SA_TEMPLATE_v1();
    saTemplate.VECLEN = sa_veclen<int_vec>::value;
    saTemplate.DIMFMT = __SA_DIMFMT_1D;
    saTemplate.ICNT0 = c1*r1*ch1;
    // saTemplate.ICNT1 = r1;
    // saTemplate.DIM1 = c1;
    __SA0_OPEN(saTemplate);
    __SE0_OPEN((void *)&arr_a[0], seTemplate);
    __SE1_OPEN((void *)&arr_b[0], seTemplate);

    int vec_len = element_count_of<int_vec>::value;

    for(int32_t i=0; i<r1*c1*ch1; i+=vec_len){
        int_vec a = strm_eng<0, int_vec>::get_adv();
        int_vec b = strm_eng<1, int_vec>::get_adv();

        int_vec addd = __vaddw_vvv(a,b);

        __vpred pred = strm_agen<0, int_vec>::get_vpred();
        int_vec * addr = strm_agen<0, int_vec>::get_adv(&res[0][0][0]);
        // pred.print();
        __vstore_pred(pred,addr,addd);
        // addd.print();

    }

    int32_t res_m[ch1][r1][c1];
    for(int32_t k=0; k<ch1; k++){
        for(int32_t i=0; i<r1; i++){
            for(int32_t j=0; j<c1; j++){
                res_m[k][i][j]=0;
            }
        }
    }
    for(int32_t k=0; k<ch1; k++){
        for(int32_t i=0; i<r1; i++){
            for(int32_t j=0; j<c1; j++){
                res_m[k][i][j] = arr_a[k][i][j]+arr_b[k][i][j];
            }
        }
    }
    for(int32_t k=0; k<ch1; k++){
        for(int32_t i=0; i<r1; i++){
            for(int32_t j=0; j<c1; j++){
                if(res[k][i][j]!=res_m[k][i][j]){
                    cout<<"NOT Equal";
                    return -1;
                }
            }
            
        }
    }

    cout<<"EQUAL";
}