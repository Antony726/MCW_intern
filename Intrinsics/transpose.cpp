#include<immintrin.h>
#include<iostream>
#include<chrono>
#include<vector>

using namespace std;

int main(){
    int r=1000,c=1000;
    //matrix A
    vector<vector<int>> mat_a(r, vector<int>(c));

    // {
    //     {1,2,3,4,5,6,7,8},
    //     {9,10,11,12,13,14,15,16},
    //     {17,18,19,20,21,22,23,24},
    //     {25,26,27,28,29,30,31,32},
    //     {33,34,35,36,37,38,39,40},
    //     {41,42,43,44,45,46,47,48},
    //     {49,50,51,52,53,54,55,56},
    //     {57,58,59,60,61,62,63,64}
    //     };
    
    vector<vector<int>> mat_c(r, vector<int>(c)) ;
    vector<vector<int>> res(r, vector<int>(c)) ;
    srand(time(0));
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            mat_a[i][j]=rand()%100;
        }
    }
    auto start = chrono::high_resolution_clock::now();
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            res[i][j]=mat_a[j][i];
        }
    }
     auto stop = chrono::high_resolution_clock::now();

  
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Time taken: " << duration.count() << " microseconds" << endl;
    // for(int i=0;i<c;i++){
    //     for(int j=0;j<r;j++){
    //         cout<<mat_a[i][j]<<" | ";

    //     }
    //     cout<<endl;
    // }
    int rem = r%8;
    int remc = r%8;
    int fr = r-rem;
    int fc = c-remc;
    start = chrono::high_resolution_clock::now();
    

    for(int i=0;i<fr;i+=8){
        for(int j=0;j<fc;j+=8){
            __m256i row0 = _mm256_loadu_si256((__m256i*)&mat_a[i][j]);
            __m256i row1 = _mm256_loadu_si256((__m256i*)&mat_a[i+1][j]);
            __m256i row2 = _mm256_loadu_si256((__m256i*)&mat_a[i+2][j]);
            __m256i row3 = _mm256_loadu_si256((__m256i*)&mat_a[i+3][j]);
            __m256i row4 = _mm256_loadu_si256((__m256i*)&mat_a[i+4][j]);
            __m256i row5 = _mm256_loadu_si256((__m256i*)&mat_a[i+5][j]);
            __m256i row6 = _mm256_loadu_si256((__m256i*)&mat_a[i+6][j]);
            __m256i row7 = _mm256_loadu_si256((__m256i*)&mat_a[i+7][j]);

            __m256i temp0 = _mm256_unpacklo_epi32(row0,row2);
            __m256i temp1 = _mm256_unpacklo_epi32(row1,row3);
            __m256i temp2 = _mm256_unpacklo_epi32(row4,row6);
            __m256i temp3 = _mm256_unpacklo_epi32(row5,row7);
            __m256i temp4 = _mm256_unpackhi_epi32(row0,row2);
            __m256i temp5 = _mm256_unpackhi_epi32(row1,row3);
            __m256i temp6 = _mm256_unpackhi_epi32(row4,row6);
            __m256i temp7 = _mm256_unpackhi_epi32(row5,row7);

            __m256i tem0 = _mm256_unpacklo_epi32(temp0,temp1);
            __m256i tem1 = _mm256_unpacklo_epi32(temp2,temp3);
            __m256i tem2 = _mm256_unpacklo_epi32(temp4,temp5);
            __m256i tem3 = _mm256_unpacklo_epi32(temp6,temp7);
            __m256i tem4 = _mm256_unpackhi_epi32(temp0,temp1);
            __m256i tem5 = _mm256_unpackhi_epi32(temp2,temp3);
            __m256i tem6 = _mm256_unpackhi_epi32(temp4,temp5);
            __m256i tem7 = _mm256_unpackhi_epi32(temp6,temp7);

            __m256i p0 = _mm256_permute2f128_si256(tem0,tem1,0x20);
            __m256i p1 = _mm256_permute2f128_si256(tem4,tem5,0x20);
            __m256i p2 = _mm256_permute2f128_si256(tem2,tem3,0x20);
            __m256i p3 = _mm256_permute2f128_si256(tem6,tem7,0x20);
            __m256i p4 = _mm256_permute2f128_si256(tem0,tem1,0x31);
            __m256i p5 = _mm256_permute2f128_si256(tem4,tem5,0x31);
            __m256i p6 = _mm256_permute2f128_si256(tem2,tem3,0x31);
            __m256i p7 = _mm256_permute2f128_si256(tem6,tem7,0x31);
            


            _mm256_storeu_si256((__m256i*)&mat_c[j][i],p0);
            _mm256_storeu_si256((__m256i*)&mat_c[j+1][i],p1);
            _mm256_storeu_si256((__m256i*)&mat_c[j+2][i],p2);
            _mm256_storeu_si256((__m256i*)&mat_c[j+3][i],p3);
            _mm256_storeu_si256((__m256i*)&mat_c[j+4][i],p4);
            _mm256_storeu_si256((__m256i*)&mat_c[j+5][i],p5);
            _mm256_storeu_si256((__m256i*)&mat_c[j+6][i],p6);
            _mm256_storeu_si256((__m256i*)&mat_c[j+7][i],p7);

        }
    }
    for(int i=0;i<r;i++){
        if(i>=fr){
            fc=0;
        }
        for(int j=fc;j<c;j++){
            mat_c[i][j]=mat_a[j][i];
        }
    }
    stop = chrono::high_resolution_clock::now();

    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Time taken: " << duration.count() << " microseconds" << endl;
    
    cout<<"Result"<<endl;
    // for(int i=0;i<c;i++){
    //     for(int j=0; j<r;j++){
    //         cout<<mat_c[i][j]<<" | ";

    //     }
    //     cout<<endl;
    // }


for(int i=0;i<c;i++){
        for(int j=0; j<r;j++){
            if(mat_c[i][j]!=res[i][j]){
                cout<<"Wasted";
                exit(0);
            }

        }
        
    }
    cout<<"Respect++";
    return 0;
}