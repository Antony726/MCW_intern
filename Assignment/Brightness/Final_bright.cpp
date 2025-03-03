#include<iostream>
#include<vector>
#include "c7x.h"
#include "c7x_scalable.h"
#include <cstdlib>  // For rand() and srand()
#include <ctime>

using namespace c7x;
using namespace std;

int main(){
    int16_t r,c,d;
    cout<<"Enter ROw and column and depth";
    cin>>r>>c>>d;
    cout<<"Enter the alpha value: ";
    int16_t alpha;
    cin>>alpha;
    // cout<<r<<c<<d;
    int16_t arr_a[d][r][c];
    int16_t arr_c[d][r][c];
    int16_t count=0;
    srand(time(0));
    for(int i=0;i<d;i++){
        for(int j=0;j<r;j++){
            for(int k=0;k<c;k++){
                arr_a[i][j][k]=(rand() % 255) + 1;
            }
        }
    }
    
    for(int i=0;i<d;i++){
        for(int j=0;j<r;j++){
            for(int k=0;k<c;k++){
                arr_c[i][j][k]=255;
            }
        }
    }

    for(int i=0;i<d;i++){
        for(int j=0;j<r;j++){
            for(int k=0;k<c;k++){
                cout<<arr_a[i][j][k]<<" | ";
            }
            cout<<"\n";
        }
    }
    int vec_len = element_count_of<short_vec>::value;

    __SE_TEMPLATE_v1 seTemplate = __gen_SE_TEMPLATE_v1();
    seTemplate.ELETYPE = se_eletype<short_vec>::value;
    seTemplate.VECLEN = se_veclen<short_vec>::value;
    seTemplate.DIMFMT = __SE_DIMFMT_1D;
    seTemplate.ICNT0 = c*r*d;
    __SE0_OPEN((void *)&arr_a[0], seTemplate);

    __SA_TEMPLATE_v1 saTemplate = __gen_SA_TEMPLATE_v1();
    saTemplate.VECLEN = sa_veclen<short_vec>::value;
    saTemplate.DIMFMT = __SA_DIMFMT_1D;
    saTemplate.ICNT0 = c*r*d;
    __SA0_OPEN(saTemplate);


    for(int i=0; i<(d*r*(c));i+=vec_len){
        short_vec alph = (short_vec)(alpha);
        short_vec data = strm_eng<0, short_vec>::get_adv();
        short_vec addd = __add_sat(data,alph);
        __vpred pred = __vcmpgth_vvp((short_vec)(255),addd);
        pred.print();

        
        short_vec * addr = strm_agen<0, short_vec>::get_adv(&arr_c[0][0][0]);
        __vpred pr = strm_agen<0, short_vec>::get_vpred();
        __vpred prs = __and_ppp(pred,pr);
        cout<<"PRS";
        pr.print();
        prs.print();
        __vstore_pred(pred,addr,addd);

    }

    for(int i=0; i<d; i++){
        cout<<"Channel :"<<i+1<<"\n";
        for(int j=0; j<r; j++){
            for(int k=0; k<c; k++){
                cout<<arr_c[i][j][k]<<" | ";
            }
            cout<<"\n";
        }
    }


}
