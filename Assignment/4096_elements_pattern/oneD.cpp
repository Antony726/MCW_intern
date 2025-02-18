#include<iostream>
#include<vector>
#include "c7x.h"
#include "c7x_scalable.h"

using namespace c7x;
using namespace std;

int main(){
    uint64_t arr[4096];
    uint64_t res[4096];

    for(int i=0; i<4096; i++){
        arr[i]=i+1;
    }
    for(int i=0; i<4096; i++){
        res[i]=0;
    }
    const int vec_len = element_count_of<ulong8>::value;

    __SE_TEMPLATE_v1 seTemplate = __gen_SE_TEMPLATE_v1();
    seTemplate.DIMFMT = __SE_DIMFMT_2D;
    seTemplate.ELETYPE = se_eletype<ulong8>::value;
    seTemplate.TRANSPOSE    = __SE_TRANSPOSE_64BIT;
    seTemplate.VECLEN = se_veclen<ulong8>::value;
    seTemplate.ICNT0 = 512;
    seTemplate.ICNT1 = 8;
    seTemplate.DIM1 = 512;
    __SE0_OPEN((void *)&arr[0], seTemplate);

    __SA_TEMPLATE_v1 saTemplate = __gen_SA_TEMPLATE_v1();
    saTemplate.VECLEN = sa_veclen<ulong8>::value;
    saTemplate.DIMFMT = __SA_DIMFMT_1D;
    saTemplate.ICNT0 = 4096;
    __SA0_OPEN(saTemplate);

    for(int i=0; i<4096/vec_len; i++){
        ulong8 data = strm_eng<0, ulong8>::get_adv();
        __vpred pred = strm_agen<0, ulong8>::get_vpred();
        ulong8 * idx = strm_agen<0, ulong8>::get_adv(&res[0]);
        __vstore_pred(pred,idx,data);
        data.print();
    }

    for(int i=0; i<4096;i++){
        if(i%8==0 && i!=0){
            cout<<"\n";
        }
        cout<<res[i]<<" | ";
        
    }

}