#include<iostream>
#include<vector>
#include "c7x.h"
#include "c7x_scalable.h"

using namespace c7x;
using namespace std;

int main(){
    int16_t r,c,d;
    cout<<"Enter ROw and column and depth";
    cin>>r>>c>>d;
    // cout<<r<<c<<d;
    int16_t arr_a[d][r][c];
    int16_t arr_b[d][r][c];
    int16_t arr_c[d][r][c];
    int16_t count=0;
    for(int i=0;i<d;i++){
        for(int j=0;j<r;j++){
            for(int k=0;k<c;k++){
                arr_a[i][j][k]=count++;
            }
        }
    }
    count=0;
    for(int i=0;i<d;i++){
        for(int j=0;j<r;j++){
            for(int k=0;k<c;k++){
                arr_b[i][j][k]=count++;
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
        int16_t *idxb = &arr_b[dim][0][0];
        int16_t *idxc = &arr_c[dim][0][0];
        for(int i=0;i<r;i++){
            int j=0;
            for(j=0; j<c; j+=vec_len){
                
                if(j+vec_len>c){
                    idx+=c-j;
                    idxb+=c-j;
                    idxc+=c-j;
                    break;
                }
                short_vec veca = *(short_vec *)(idx);
                short_vec vecb = *(short_vec *)(idxb);
                cout<<"Vec a";
                veca.print();
                cout<<"Vec b";
                vecb.print();
                cout<<"vec c";
                short_vec vecc = veca + vecb;
                *(short_vec *)(idxc) = vecc;
                vecc.print();
                idx+=vec_len;
                idxb+=vec_len;
                idxc+=vec_len;
                cout<<"\n";
            }
            for(int k=j; k<c; k++){
                arr_c[dim][i][k] = arr_a[dim][i][k]+arr_b[dim][i][k];
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