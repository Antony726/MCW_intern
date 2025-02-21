#include<iostream>
#include<vector>
#include "c7x.h"
#include "c7x_scalable.h"
#include <cstdlib>  // For rand() and srand()
#include <ctime>

using namespace c7x;
using namespace std;

int main(){
    int16_t r,c,d=3;
    cout<<"Enter ROw and column ";
    cin>>r>>c;
    float img[d][r][c] ;
    float count=0;
    srand(time(0));
    for(int i=0;i<d;i++){
        for(int j=0;j<r;j++){
            for(int k=0;k<c;k++){
                // img[i][j][k]=count++;
                img[i][j][k]=(rand() % 255) + 1;

            }
        }
    }
    float grey[r][c];
    for(int j=0;j<r;j++){
        for(int k=0;k<c;k++){
            grey[j][k]=0;
        }
    }

    __SE_TEMPLATE_v1 seTemplate = __gen_SE_TEMPLATE_v1();
    seTemplate.ELETYPE = se_eletype<float_vec>::value;
    seTemplate.VECLEN = se_veclen<float_vec>::value;
    seTemplate.DIMFMT = __SE_DIMFMT_3D;
    seTemplate.ICNT0 = c;
    seTemplate.ICNT1 = r;
    seTemplate.ICNT2 = d;
    seTemplate.DIM1 = c;
    seTemplate.DIM2 = c*r;

    __SE0_OPEN((void *)&img[1],seTemplate);
    __SE1_OPEN((void *)&img[2],seTemplate);

    __SA_TEMPLATE_v1 saTemplate = __gen_SA_TEMPLATE_v1();
    saTemplate.VECLEN = sa_veclen<float_vec>::value;
    saTemplate.DIMFMT = __SA_DIMFMT_3D;
    saTemplate.ICNT0 = c;
    saTemplate.ICNT1 = r;
    saTemplate.ICNT2 = d;
    saTemplate.DIM1 = c;
    saTemplate.DIM2 = c*r;
    __SA0_OPEN(saTemplate);

    __SA_TEMPLATE_v1 saTemplate1 = __gen_SA_TEMPLATE_v1();
    saTemplate1.VECLEN = sa_veclen<float_vec>::value;
    saTemplate1.DIMFMT = __SA_DIMFMT_2D;
    saTemplate1.ICNT0 = c;
    saTemplate1.ICNT1 = r;
    saTemplate1.DIM1 = c;
    __SA1_OPEN(saTemplate1);


    
    float red=0.29891;
    float green=0.58661;
    float blue=0.11448;

    int vec_len = element_count_of<float_vec>::value;

    for(int i=0; i<(r*c);i+=vec_len){
        float_vec red_v = *strm_agen<0, float_vec>::get_adv(&img[0]);
        float_vec green_v = strm_eng<0, float_vec>::get_adv();
        float_vec blue_v = strm_eng<1, float_vec>::get_adv();
        

        __vpred pred = strm_agen<1, float_vec>::get_vpred();
        float_vec * addr = strm_agen<1, float_vec>::get_adv(&grey[0][0]);

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

    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            cout<<grey[i][j]<<" | ";
        }
        cout<<"\n";
    }


}
