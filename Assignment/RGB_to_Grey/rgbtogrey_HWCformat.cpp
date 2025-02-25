#include<iostream>
#include<vector>
#include "c7x.h"
#include "c7x_scalable.h"
#include <cstdlib>
#include <ctime>

using namespace c7x;
using namespace std;

int main(){
    int16_t r;
    cout<<"Enter Size :";
    cin>>r;
    float img[r] ;
    float count=0;
    srand(time(0));
    
    for(int j=0;j<r;j++){
            img[j]=(rand() % 255) + 1;
            // img[j] = j+1;
    }
    float grey[r/3];
    
    int vec_len = element_count_of<float_vec>::value;

    __SE_TEMPLATE_v1 seTemplate = __gen_SE_TEMPLATE_v1();
    seTemplate.ELETYPE = se_eletype<float_vec>::value;
    seTemplate.VECLEN = se_veclen<float_vec>::value;
    seTemplate.DIMFMT = __SE_DIMFMT_3D;
    seTemplate.TRANSPOSE = __SE_TRANSPOSE_32BIT;
    seTemplate.ICNT0 = 3;
    seTemplate.ICNT1 = vec_len;
    seTemplate.ICNT2 = r/3;
    seTemplate.DIM1 = 3;
    seTemplate.DIM2 = 3*vec_len;

    __SE0_OPEN((void *)&img[0],seTemplate);

    __SA_TEMPLATE_v1 saTemplate1 = __gen_SA_TEMPLATE_v1();
    saTemplate1.VECLEN = sa_veclen<float_vec>::value;
    saTemplate1.DIMFMT = __SA_DIMFMT_1D;
    saTemplate1.ICNT0 = r/3;
    __SA0_OPEN(saTemplate1);


    
    float red=0.29891;
    float green=0.58661;
    float blue=0.11448;


    for(int i=0; i<(r/3);i+=vec_len){
        
        float_vec red_v = strm_eng<0, float_vec>::get_adv();
        float_vec green_v = strm_eng<0, float_vec>::get_adv();
        float_vec blue_v = strm_eng<0, float_vec>::get_adv();

        __vpred pred = strm_agen<0, float_vec>::get_vpred();
        float_vec * addr = strm_agen<0, float_vec>::get_adv(&grey[0]);

        float_vec rc = (float_vec)(red);
        float_vec gc = (float_vec)(green);
        float_vec bc = (float_vec)(blue);

        float_vec mulr = __vmpysp_vvv(red_v,rc);
        float_vec mulg = __vmpysp_vvv(green_v,gc);
        float_vec mulb = __vmpysp_vvv(blue_v,bc);

        float_vec y = __vaddsp_vvv(mulr,mulg);
        y=__vaddsp_vvv(y,mulb);

        float_vec res = __min(y, (float_vec)255);
        __vstore_pred(pred,addr,res);
        
    }

    for(int i=0;i<r/3;i++){
        
            cout<<grey[i]<<" | ";
        
        
    }
    cout<<"\n";


}
