#include<iostream>
#include<vector>
#include "c7x.h"
#include "c7x_scalable.h"
#include <cstdlib> 
#include <ctime>
#include<chrono>

#include <sys/time.h>

using namespace c7x;
using namespace std;
#define CPU_FREQ 2e9;

int main(){
    int32_t r1,c1;
    cout<<"Enter Row and Column :";
    cin>>r1>>c1;
    int32_t arr[r1][c1];

    int64_t res[r1/2][c1/2];
    int32_t res_m[r1][c1];
    int32_t count =1;
    for(int i=0; i<r1; i++){
        for(int j=0; j<c1; j++){
            arr[i][j]=count++;
        }
    }

    // count =1;
    for(int i=0; i<ceil(r1/2.0); i++){
        for(int j=0; j<ceil(c1/2.0); j++){
            res[i][j]=0;
        }
    }

    for(int i=0; i<r1; i++){
        for(int j=0; j<c1; j++){
            res_m[i][j]=0;
        }
    }
    struct timeval startttt, sttttop;
    gettimeofday(&startttt, NULL);

    __SE_TEMPLATE_v1 seTemplate = __gen_SE_TEMPLATE_v1();
    seTemplate.ELETYPE = se_eletype<int_vec>::value;
    seTemplate.VECLEN = se_veclen<long_vec>::value;
    seTemplate.DECIM = __SE_DECIM_2;
    seTemplate.PROMOTE = __SE_PROMOTE_2X_SIGNEXT;
    seTemplate.DIMFMT = __SE_DIMFMT_1D;
    seTemplate.ICNT0 = r1*c1;
    __SE0_OPEN((void *)&arr[0], seTemplate);

    __SA_TEMPLATE_v1 saTemplate = __gen_SA_TEMPLATE_v1();
    saTemplate.VECLEN = sa_veclen<long_vec>::value;
    saTemplate.DIMFMT = __SA_DIMFMT_1D;
    saTemplate.ICNT0 = (r1/2)*(c1/2);
    __SA0_OPEN(saTemplate);



    for(int i=0; i<ceil(r1*c1 / (16.0 * 2)); i++){
        long_vec data = strm_eng<0, long_vec>::get_adv();
        long_vec two = (long_vec)(2);
        long_vec mul = __vmpydd_vvv(data,two);


        __vpred pred = strm_agen<0, long_vec>::get_vpred();
        long_vec * addr = strm_agen<0, long_vec>::get_adv(&res[0][0]);
        __vstore_pred(pred, addr, mul);

    }
    gettimeofday(&sttttop, NULL);
 
    double elapsed_time = (sttttop.tv_sec - startttt.tv_sec) + (sttttop.tv_usec - startttt.tv_usec) / 1e6;
    double estimated_cycles = elapsed_time * CPU_FREQ;
 
    printf("Execution time of Decimation: %f seconds\n", elapsed_time);
    printf("Estimated cycle count of Decimation: %.0f cycles\n", estimated_cycles);
    cout<<"________________________________________________________________________________________________________________";

    struct timeval start, stop;
    gettimeofday(&start, NULL);

    __SE_TEMPLATE_v1 seTemplate1 = __gen_SE_TEMPLATE_v1();
    seTemplate1.ELETYPE = se_eletype<int_vec>::value;
    seTemplate1.VECLEN = se_veclen<int_vec>::value;
    seTemplate1.DIMFMT = __SE_DIMFMT_1D;
    seTemplate1.ICNT0 = r1*c1;
    __SE1_OPEN((void *)&arr[0], seTemplate1);

    __SA_TEMPLATE_v1 saTemplate1 = __gen_SA_TEMPLATE_v1();
    saTemplate1.VECLEN = sa_veclen<int_vec>::value;
    saTemplate1.DIMFMT = __SA_DIMFMT_1D;
    saTemplate1.ICNT0 = (r1)*(c1);
    __SA1_OPEN(saTemplate1);

    const int vec_len = element_count_of<int_vec>::value;
    for(int i=0; i<r1*c1 ; i+=vec_len){
        int_vec d = strm_eng<1,int_vec>::get_adv();
        int_vec two = (int_vec)(2);
        int_vec mul = __vmpyww_vvv(d,two);
        __vpred Vp = __vpred{0x0F0F0F0F0F0F0F0FULL};
        
        int_vec * addr = strm_agen<1, int_vec>::get_adv(&res_m[0][0]);
        
        __vstore_pred(Vp,addr,mul);

    }
    gettimeofday(&stop, NULL);
 
    double elapsed_timee = (stop.tv_sec - start.tv_sec) + (stop.tv_usec - start.tv_usec) / 1e6;
    // cout<<stop.tv_sec<<" "<<start.tv_sec<<"\n"<<stop.tv_usec<<" "<<start.tv_usec;
    double estimated_cyclees = elapsed_timee * CPU_FREQ;
 
    printf("\n Execution time of Predication: %f seconds\n", elapsed_timee);
    printf("Estimated cycle count of Predication: %.0f cycles\n", estimated_cyclees);

//     for(int i=0; i<ceil(r1/2.0); i++){
//         for(int j=0; j<ceil(c1/2.0); j++){
//             cout<<res[i][j]<<" | ";
//         }
//         cout<<"\n";
//     }
// cout<<"-----------------------------------------------------------"<<"\n";
//     for(int i=0; i<r1; i++){
//         for(int j=0; j<c1; j++){
//             cout<<res_m[i][j]<<" | ";
//         }
//         cout<<"\n";
//     }

}