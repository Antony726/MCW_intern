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

    srand(time(0));
    for(int i=0;i<d;i++){
        for(int j=0;j<r;j++){
            for(int k=0;k<c;k++){
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
    
    float red=0.29891;
    float green=0.58661;
    float blue=0.11448;

    int vec_len = element_count_of<float_vec>::value;
    
        float *idxr = &img[0][0][0];
        float *idxg = &img[1][0][0];
        float *idxb = &img[2][0][0];


        float *idxc = &grey[0][0];
        for(int i=0;i<r;i++){
            int j=0;
            for(j=0; j<c; j+=vec_len){
                
                if(j+vec_len>c){
                    idxr+=c-j;
                    idxg+=c-j;
                    idxb+=c-j;

                   
                    idxc+=c-j;
                    break;
                }
                // Takes each dimension from input as red,green ,blue
                float_vec vecr = *(float_vec *)(idxr);
                float_vec vecg = *(float_vec *)(idxg);
                float_vec vecb = *(float_vec *)(idxb);
                // Constant vector for the multiplication
                float_vec conr = (float_vec )(red);
                float_vec cong = (float_vec )(green);
                float_vec conb = (float_vec )(blue);
                // multiplying with each constant
                float_vec mulr = vecr*conr;
                float_vec mulg = vecg*cong;
                float_vec mulb = vecb*conb;
                // Adding the red,green,blue
                float_vec y = mulr+mulg;
                y=y+mulb;
                cout<<"Y"<<"\n";
                y.print();

                
                
                
                float_vec res = __min(y, (float_vec)255);
                res.print();
                *(float_vec *)(idxc) = res;
                
                idxr+=vec_len;
                idxg+=vec_len;
                idxb+=vec_len;

                
                idxc+=vec_len;
                cout<<"\n";
            }
            for(int k=j; k<c; k++){
                float y = (img[0][i][k]*red)+(img[1][i][k]*green)+(img[2][i][k]*blue);
                if(y>255){
                    grey[i][k]=255;
                }
                else{
                    grey[i][k]=y;
                }
            }
    
        
    }


    cout<<"Output"<<"\n";
    
        for(int16_t m=0; m<r; m++){
            for(int16_t n=0; n<c; n++){
                cout<<grey[m][n]<<" | ";
            }
            cout<<"\n";
        }
        cout<<"\n";
    

}