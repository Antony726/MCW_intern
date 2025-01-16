#include <iostream>
#include <vector>
#include <immintrin.h>
#include <cstdlib> 
#include <ctime>
#include<chrono>

using namespace std;

//To print matrix
void print(vector<vector<int>> matrix , int row,int col,string str){
    cout<<"\n"<<str<<"\n";
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            cout<<matrix[i][j]<<" | ";
        }
    cout<<"\n";
    }
    cout<<"-------------------------------------------------------------------";
    
}

void check(vector<vector<int>> matrix_A, vector<vector<int>> matrix_b,int row,int col){
    int f=0;
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            if(matrix_A[i][j]==matrix_b[i][j]){
                f=0;
            }
            else{
                f=1;
                break;
            }
        }
    }
    if(f==0){
        cout<<"Respect+++ \n";
    }
    else{
        cout<<"Wasted \n";
    }

}

//ADD

void addmat(vector<vector<int>> matrix_a, vector<vector<int>> matrix_b,int row, int col, vector<vector<int>> matrix_c){
    auto start = chrono::high_resolution_clock::now();
    
    for(int i=0;i<row;i++){
        for(int j=0; j<col; j++){
            matrix_c[i][j] = matrix_a[i][j] + matrix_b[i][j];
        }
    }
   // print(matrix_c,row,col,"Matrix C");


    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout <<"\n"<< "Time taken by Add matrix normal function: " << duration.count() << " microseconds" << endl;
    
}

//intrinstic add
void addi(vector<vector<int>> matrix_a, vector<vector<int>> matrix_b,int row, int col, vector<vector<int>> matrix_c){
    auto start = chrono::high_resolution_clock::now();
    int fcol = col;
    int rem = col%8;
    col=col-rem;

    for(int i=0; i<row ; i++){
        for(int j=0; j+7<col ; j+=8){
            __m256i rowa = _mm256_loadu_si256((__m256i*)&matrix_a[i][j]);
            __m256i rowb = _mm256_loadu_si256((__m256i*)&matrix_b[i][j]);
            __m256i res = _mm256_add_epi32(rowa,rowb);
            _mm256_storeu_si256((__m256i*)&matrix_c[i][j],res);
        }
        for(int j=col; j<fcol; j++){
            matrix_c[i][j] = matrix_a[i][j]+matrix_b[i][j];
        }
    }

    //print(matrix_c,row,fcol,"Matrix C with intrinsic function");

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout <<"\n"<< "Time taken by Add matrix Intrinsic function: " << duration.count() << " microseconds" << endl;
}


//sub

void submat(vector<vector<int>> matrix_a, vector<vector<int>> matrix_b,int row, int col, vector<vector<int>> matrix_c){
    auto start = chrono::high_resolution_clock::now();
    
    for(int i=0;i<row;i++){
        for(int j=0; j<col; j++){
            matrix_c[i][j] = matrix_a[i][j] - matrix_b[i][j];
        }
    }
   // print(matrix_c,row,col,"Matrix C");


    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout <<"\n"<< "Time taken by SUB matrix normal function: " << duration.count() << " microseconds" << endl;
    
}

//intrinstic sub
void subi(vector<vector<int>> matrix_a, vector<vector<int>> matrix_b,int row, int col, vector<vector<int>> matrix_c){
    auto start = chrono::high_resolution_clock::now();
    int fcol = col;
    int rem = col%8;
    col=col-rem;

    for(int i=0; i<row ; i++){
        for(int j=0; j+7<col ; j+=8){
            __m256i rowa = _mm256_loadu_si256((__m256i*)&matrix_a[i][j]);
            __m256i rowb = _mm256_loadu_si256((__m256i*)&matrix_b[i][j]);
            __m256i res = _mm256_sub_epi32(rowa,rowb);
            _mm256_storeu_si256((__m256i*)&matrix_c[i][j],res);
        }
        for(int j=col; j<fcol; j++){
            matrix_c[i][j] = matrix_a[i][j]+matrix_b[i][j];
        }
    }

    //print(matrix_c,row,fcol,"Matrix C with intrinsic function");

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout <<"\n"<< "Time taken by Sub matrix Intrinsic function: " << duration.count() << " microseconds" << endl;
}

//multiplication

int muli(vector<vector<int>> matrix_c){
    int row_a,col_a,row_b,col_b;
    cout<<"Enter Row and column for Matrix A: ";
    cin>>row_a;
    cin>>col_a;

    cout<<"Enter Row and column for Matrix b: ";
    cin>>row_b;
    cin>>col_b;

    if(col_a != row_b){
        cout<<"not valid";
        return 0;
    }

    vector<vector<int>> mat_a(row_a, vector<int>(col_a)) ;
    srand(time(0));
    for(int i=0;i<row_a;i++){
        for(int j=0;j<col_a;j++){
            mat_a[i][j]=rand()%100;
        }
    }

    //mat_b
    vector<vector<int>> mat_b(row_b, vector<int>(col_b)) ;
    srand(time(0));
    for(int i=0;i<row_b;i++){
        for(int j=0;j<col_b;j++){
            mat_b[i][j]=rand()%100;
        }
    }

    vector<vector<int>> mat_c(row_a,vector<int>(col_b));
    auto startt = chrono::high_resolution_clock::now();
    for(int i=0;i<row_a;i++){
        for(int j=0;j<col_b;j++){
            for(int k=0;k<col_b;k++){
                mat_c[i][j]+=mat_a[i][k]*mat_b[k][j];
            }
        }
    }

    print(mat_c,row_a,row_b,"Normal Multi");

    auto stopp = chrono::high_resolution_clock::now();
    auto durationn = chrono::duration_cast<chrono::microseconds>(stopp - startt);
    cout <<"\n"<< "Time taken by Mul matrix : " << durationn.count() << " microseconds" << endl;


    
    auto start = chrono::high_resolution_clock::now();
    // int fcol = col;
    // int rem = col%8;
    // col=col-rem;
    int ffcol =col_b;
    for(int i=0;i<row_a;i++){
        for(int j=0;j<col_b;j++){
            __m256i res = _mm256_setzero_si256();
            int fcol = col_b;
            int rem = col_b%8;
            col_b=col_b-rem;
            int k=0;
            for(k=0;k<col_b;k++){
                __m256i rowa = _mm256_loadu_si256((__m256i*)&mat_a[i][k]);
                __m256i colb = _mm256_loadu_si256((__m256i*)&mat_b[k][j]);
                __m256i mul = _mm256_mullo_epi32(rowa,colb);

                res = _mm256_add_epi32(mul,res);
                
            }
            _mm256_storeu_si256((__m256i*)&matrix_c[i][j],res);
            for(int l=k;l<fcol;l++){
                matrix_c[i][j]+=mat_a[i][k]*mat_b[k][j];
            }
        }
    }
    print(matrix_c,row_b,ffcol,"Intrinsic Multi");
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout <<"\n"<< "Time taken by Mul matrix Intrinsic function: " << duration.count() << " microseconds" << endl;
    check(mat_c,matrix_c,row_a,col_b);
    return 0;
}










int main(){
    int r=100,c=100;
    //matrix A
    vector<vector<int>> mat_a(r, vector<int>(c)) ;
    srand(time(0));
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            mat_a[i][j]=rand()%100;
        }
    }

    //mat_b
    vector<vector<int>> mat_b(r, vector<int>(c)) ;
    srand(time(0));
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            mat_b[i][j]=rand()%100;
        }
    }

    vector<vector<int>> result(r, vector<int>(c)) ;
    vector<vector<int>> resulti(r, vector<int>(c)) ;
    



    

    //Print
    // print(mat_a,r,c,"Matrix A");
    // print(mat_b,r,c,"Matrix B");

    //function calls

    //add normal
    

    // check(result,resulti,r,c);

    char ch = 'y';


    while(ch!='n'){
        cout<<"1.Show Inputs \n 2.Add Normal \n 3.Add Intrinsic \n 4.Sub Normal \n 5.Sub Intrinsic \n 6.Multiply \n 7.Exit Enter your option:";
        int opt;
        cin>>opt;
        switch(opt){
            case 1:
                print(mat_a,r,c,"Matrix A");
                print(mat_b,r,c,"Matrix B");
                break;
            case 2:
                addmat(mat_a,mat_b,r,c,result);
                break;
            case 3:
                addi(mat_a,mat_b,r,c,resulti);
                break;
            case 4:
                submat(mat_a,mat_b,r,c,result);
                break;
            case 5:
                subi(mat_a,mat_b,r,c,resulti);
                break;
            case 6:
                muli(resulti);
                break;
            case 7:
                break;
            case 10:
                check(result,resulti,r,c);
                break;




        }
        cout<<"\n Do you want to continue (y/n) :";
        cin>>ch;
        cout<<"\n";

    }



    return 0;



}