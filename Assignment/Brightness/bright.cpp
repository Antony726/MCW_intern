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
                arr_c[i][j][k]=0;
            }
        }
    }
    int vec_len = element_count_of<short_vec>::value;
    for(int dim=0;dim<d;dim++){
        int16_t *idx = &arr_a[dim][0][0];
        int16_t *idxc = &arr_c[dim][0][0];
        for(int i=0;i<r;i++){
            int j=0;
            for(j=0; j<c; j+=vec_len){
                
                if(j+vec_len>c){
                    idx+=c-j;
                   
                    idxc+=c-j;
                    break;
                }
                __vpred mask;
                short_vec veca = *(short_vec *)(idx);
                short_vec vecb = (short_vec )(alpha); // alpha vector
                short_vec vef = (short_vec )(255);  //255 vector
                cout<<"Vec a";
                veca.print();
                cout<<"Vec b";
                vecb.print();
                cout<<"vec c";
                short_vec vecc = veca + vecb;  //Adding input to alpha
                short_vec res = __min(vecc, (short_vec)255);   //if anything above 255 then it will replace with 255
                res.print();
                *(short_vec *)(idxc) = res;
                
                idx+=vec_len;
                
                idxc+=vec_len;
                cout<<"\n";
            }
            for(int k=j; k<c; k++){
                int16_t ssum = arr_a[dim][i][k]+alpha;
                if(ssum>255){
                    arr_c[dim][i][k]=255;
                }
                else{
                    arr_c[dim][i][k]=ssum;
                }
            }
    
        }
    }
    cout<<"Output"<<"\n";
    for(int16_t i=0; i<d; i++){
        for(int16_t m=0; m<r; m++){
            for(int16_t n=0; n<c; n++){
                cout<<arr_c[i][m][n]<<" | ";
            }
            cout<<"\n";
        }
        cout<<"\n";
    }

}