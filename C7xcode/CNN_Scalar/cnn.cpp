#include<iostream>
#include<vector>
#include "c7x.h"
#include "c7x_scalable.h"
using namespace c7x;
using namespace std;

//Generate Input Image

void inp(int32_t r, int32_t c, int32_t ch,int32_t*** img){
    int32_t count =0;
    for(int i=0;i<ch;i++){
        for(int j=0; j<r; j++){
            for(int k=0; k<c; k++){
                img[i][j][k] = count++;
            }
        }
    }

}

//Generate Filter 

void filt(int32_t r, int32_t c, int32_t ch,int32_t chann,int32_t**** filter){
    int32_t count =1;
    for(int p=0;p<ch;p++){
        for(int i=0;i<chann;i++){
            for(int j=0; j<r; j++){
                for(int k=0; k<c; k++){
                    filter[p][i][j][k] = count++;
                }
            }
        }
    }
    

}

void paddinpt(int32_t r, int32_t c, int32_t ch, int32_t*** img, int32_t*** padded,int32_t pad){
    for(int i=0;i<ch;i++){
        for(int j=0;j<(r+2*pad);j++){
            for(int k=0; k<(c+2*pad); k++){
                padded[i][j][k]=0;
            }
        }
    }

    for(int i=0; i<ch; i++){
        for(int j=0; j<r; j++){
            for(int k=0; k<c; k++){
                padded[i][j+pad][k+pad] = img[i][j][k];
            }
        }
    }
}

int32_t outsize(int32_t r, int32_t c, int32_t ch, int32_t p, int32_t st, int32_t ks){
    int32_t size =0;
    size = ((r-ks+(2*p))/st)+1;
    return size;
}
int32_t outsizec(int32_t r, int32_t c, int32_t ch, int32_t p, int32_t st, int32_t ks){
    int32_t sizec =0;
    sizec = ((c-ks+(2*p))/st)+1;
    return sizec;
}
int32_t outsizedc(int32_t r, int32_t c, int32_t depth, int32_t p, int32_t st, int32_t ks){
    int32_t sizec =0;
    sizec = ((depth-ks+(2*p))/st)+1;
    return sizec;
}

// myconv(channel,out_s,out_cs,kernel,stride,pad,row,column,padded,img,cnn,filter,k_c,depth);
void myconv(int32_t ch, int32_t r_s, int32_t c_s, int32_t k, int32_t st, int32_t p, int32_t r,int32_t co, int32_t*** padded, int32_t*** img, int32_t*** cnn, int32_t**** filter, int32_t k_c,int32_t depth){
    for(int32_t c=0; c<k_c; c++){
        for(int32_t cc=0; cc<r_s; cc++){
            for(int32_t i=0; i<c_s; i++){
                for(int32_t j=0; j<depth; j++){
                    // for(int32_t d=0; d<ch; d++){
                        for(int32_t m=0; m<k; m++){
                            for(int32_t n=0; n<k; n++){
                                if((m+i*st) >= (r+2*p) || (n+j*st) >= (co+2*p)){
                                    continue;
                                }
                                cnn[c][cc][i] += padded[j][m+cc*st][n+i*st]*filter[c][j][m][n];
                            }
                        }
                    
                }
            }
        }
    }
}





int main(){

    int32_t row,column,channel,kernel,pad,stride,k_c,depth,out_ds;

    cout<<"Enter number of Rows:";
    cin>>row;
    cout<<"Enter Number of columns";
    cin>>column;
    cout<<"Enter Number of Depth";
    cin>>depth;
    cout<<"Enter in channel";
    cin>>channel;
    cout<<"Enter Kernel size";
    cin>>kernel;
    cout<<"Enter out channel";
    cin>>k_c;
    cout<<"Enter Padding size";
    cin>>pad;
    cout<<"Enter Stride";
    cin>>stride;


    int32_t*** img = new int32_t**[depth];
    for (int i = 0; i < depth; i++) {
        img[i] = new int32_t*[row];
        for (int j = 0; j < row; j++) {
            img[i][j] = new int32_t[column];
        }
    }

    // int32_t*** filter = new int32_t**[channel];
    // for (int i = 0; i < channel; i++) {
    //     filter[i] = new int32_t*[kernel];
    //     for (int j = 0; j < kernel; j++) {
    //         filter[i][j] = new int32_t[kernel];
    //     }
    // }
    int32_t**** filter = new int32_t***[k_c];
    for (int k = 0; k < k_c; k++) {
        filter[k] = new int32_t**[channel];
        for (int i = 0; i < channel; i++) {
            filter[k][i] = new int32_t*[kernel];
            for (int j = 0; j < kernel; j++) {
                filter[k][i][j] = new int32_t[kernel];
            }
        }
    }



    int32_t*** padded = new int32_t**[depth];
    for (int i = 0; i < depth; i++) {
        padded[i] = new int32_t*[row + 2 * pad];
        for (int j = 0; j < row + 2 * pad; j++) {
            padded[i][j] = new int32_t[column + 2 * pad];
        }
    }



    int32_t out_s = 0, out_cs=0;
    inp(row,column,depth,img);
    
    filt(kernel,kernel,k_c,channel,filter);
    
    if(pad>=1){
        paddinpt(row,column,depth,img,padded,pad);
    }
    else{
        for(int i=0;i<depth;i++){
            for(int j=0;j<row;j++){
                for(int k=0; k<column; k++){
                    padded[i][j][k] = img[i][j][k];
                }
            }
        }
        
    }

    
    out_s = outsize(row,column,depth,pad,stride,kernel);
    
    out_cs = outsizec(row,column,depth,pad,stride,kernel);
    
    out_ds = outsizedc(row,column,depth,pad,stride,kernel);
    


    
    
    int32_t*** cnn = new int32_t**[k_c];
    for (int i = 0; i < k_c; i++) {
        cnn[i] = new int32_t*[out_s];
        for (int j = 0; j < out_s; j++) {
            cnn[i][j] = new int32_t[out_cs];
        }
    }

    for(int i=0;i<k_c;i++){
        for(int j=0;j<out_s;j++){
            for(int k=0; k<out_cs; k++){
                cnn[i][j][k]=0;
            }
        }
    }
    cout<<"Working"<<"\n";


    myconv(channel,out_s,out_cs,kernel,stride,pad,row,column,padded,img,cnn,filter,k_c,depth);


    // for(int i=0;i<channel;i++){
    //     for(int j=0;j<row;j++){
    //         for(int k=0; k<column; k++){
    //             cout<<img[i][j][k]<<" | ";
    //         }
    //         cout<<"\n";
    //     }
    //     cout<<"\n";
    // }

    // for(int i=0;i<k_c;i++){
    //     for(int j=0;j<kernel;j++){
    //         for(int k=0; k<kernel; k++){
    //             cout<<filter[i][j][k]<<" | ";
    //         }
    //         cout<<"\n";
    //     }
    //     cout<<"\n";
    // }
    // cout<<"Padded";
    // cout<<"\n";
    // for(int i=0;i<channel;i++){
    //     for(int j=0;j<(row+2*pad);j++){
    //         for(int k=0; k<(column+2*pad); k++){
    //             cout<<padded[i][j][k]<<" | ";
    //         }
    //         cout<<"\n";
    //     }
    //     cout<<"\n";
    // }

    for(int i=0;i<k_c;i++){
        for(int j=0;j<out_s;j++){
            for(int k=0; k<out_cs; k++){
                cout<<cnn[i][j][k]<<" | ";
            }
            cout<<"\n";
        }
        cout<<"\n";
    }

    cout<<"Output height size:"<<out_s<<"\n";
    cout<<"Output width size:"<<out_cs<<"\n";
    cout<<"Output out_channel:"<<k_c<<"\n";
    
    
}
