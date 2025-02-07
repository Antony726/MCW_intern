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

void filt(int32_t r, int32_t c, int32_t ch,int32_t*** filter){
    int32_t count =1;
    for(int i=0;i<ch;i++){
        for(int j=0; j<r; j++){
            for(int k=0; k<c; k++){
                filter[i][j][k] = count++;
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


void myconv(int32_t ch, int32_t r_s, int32_t c_s, int32_t k, int32_t st, int32_t p, int32_t r,int32_t co, int32_t*** padded, int32_t*** img, int32_t*** cnn, int32_t*** filter, int32_t k_c){
    for(int32_t c=0; c<k_c; c++){
        for(int32_t cc=0; cc<r_s; cc++){
            for(int32_t i=0; i<c_s; i++){
                for(int32_t j=0; j<ch; j++){
                    for(int32_t m=0; m<k; m++){
                        for(int32_t n=0; n<k; n++){
                            if((m+i*st) >= (r+2*p) || (n+j*st) >= (co+2*p)){
                                continue;
                            }
                            cnn[c][cc][i] += padded[j][m+cc*st][n+i*st]*filter[c][m][n];
                        }
                    }
                }
            }
        }
    }
}





int main(){

    int32_t row,column,channel,kernel,pad,stride,k_c;

    cout<<"Enter number of Rows:";
    cin>>row;
    cout<<"Enter Number of columns";
    cin>>column;
    cout<<"Enter Number of Channel";
    cin>>channel;
    cout<<"Enter Kernel size";
    cin>>kernel;
    cout<<"Enter channel for kernel";
    cin>>k_c;
    cout<<"Enter Padding size";
    cin>>pad;
    cout<<"Enter Stride";
    cin>>stride;


    int32_t*** img = new int32_t**[channel];
    for (int i = 0; i < channel; i++) {
        img[i] = new int32_t*[row];
        for (int j = 0; j < row; j++) {
            img[i][j] = new int32_t[column];
        }
    }

    int32_t*** filter = new int32_t**[k_c];
    for (int i = 0; i < k_c; i++) {
        filter[i] = new int32_t*[kernel];
        for (int j = 0; j < kernel; j++) {
            filter[i][j] = new int32_t[kernel];
        }
    }

    int32_t*** padded = new int32_t**[channel];
    for (int i = 0; i < channel; i++) {
        padded[i] = new int32_t*[row + 2 * pad];
        for (int j = 0; j < row + 2 * pad; j++) {
            padded[i][j] = new int32_t[column + 2 * pad];
        }
    }



    int32_t out_s = 0, out_cs=0;
    inp(row,column,channel,img);
    filt(kernel,kernel,k_c,filter);
    if(pad>=1){
        paddinpt(row,column,channel,img,padded,pad);
    }
    else{
  
        for(int i=0;i<channel;i++){
            for(int j=0;j<row;j++){
                for(int k=0; k<column; k++){
                    padded[i][j][k] = img[i][j][k];
                }
            }
        }
        
    }

    
    out_s = outsize(row,column,channel,pad,stride,kernel);
    cout<<"Output size:"<<out_s<<"\n";
    out_cs = outsizec(row,column,channel,pad,stride,kernel);
    cout<<"Output size:"<<out_cs<<"\n";

    
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


    myconv(channel,out_s,out_cs,kernel,stride,pad,row,column,padded,img,cnn,filter,k_c);


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
    
    
    
}
