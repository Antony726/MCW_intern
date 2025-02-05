# Vectorization
## code
## 1: ADD
```cpp
void add(int32_t a, int32_t b){
    int32_t c[a];
    int32_t d[b];
    for(int i=0; i<a; i++){
        c[i]=i;
    }
    for(int32_t j=0; j<b; j++){
        d[j]=j;
    }
    int32_t *va = &c[0];
    int32_t *vb = &d[0];
    int32_t m = 0;
    if(a>b){
        m=a;
    }
    else{
        m=b;
    }
    int32_t res[m];
    for(int i=0; i<m; i++){
        res[i]=0;
    }
    int32_t *vc = &res[0];
    const int vec_len = element_count_of<int_vec>::value;
    int32_t i=0;
    int32_t iter=0;
    for(i=0; i<m; i+=vec_len){
        if((i+vec_len)>m){
            break;
        }
        int_vec vina = *(int_vec *)(va+i);
        int_vec vinb = *(int_vec *)(vb+i);
        int_vec vinc = vina+vinb;
        *(int_vec *)(vc+i) = vinc;
        cout<<"Iteration : "<<iter++<<"\n";
        vinc.print();

    }
    for(int32_t j=i; j<m; j++){
        res[j]=c[j]+d[j];
    }
    cout<<"Output \n";
    for(int i=0;i<m;i++){
        cout<<res[i]<<" , ";
    }
}
```
### output:
![alt text](image.png)
