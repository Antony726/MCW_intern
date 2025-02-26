# RGB to GREYscale Using SE and SA

### Here I have used 2 Streaming Engine and 1 Streaming Address Generator to Load and used 1 Streaming Engine to Store

```cpp
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
```
## Function
```cpp
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
```


# I Also Implemented RGB to Greyscale with other form of input :
[Click here to see the code](rgbtogrey_HWCformat.cpp)

## In this program i used only One Streaming Engine and One Streaming Address Generator
- The input is 1D and Output is also 1D
- In streaming Engine the input is Assumed as 3D of size: 
- column: 3 (since there are 3 colors (Red, Green, Blue))
- Row: vec_len
- Channel : Array_size/3

- And iam transposing this matrix with the help of streaming engine
- By doing this now I get Red separatley as a vector, Green as a vector, Blue as a vector

- In Streaming Address I store it as a 1D Array
### Streaming Engine Template :
```cpp
 __SE_TEMPLATE_v1 seTemplate = __gen_SE_TEMPLATE_v1();
    seTemplate.ELETYPE = se_eletype<float_vec>::value;
    seTemplate.VECLEN = se_veclen<float_vec>::value;
    seTemplate.DIMFMT = __SE_DIMFMT_3D;
    seTemplate.TRANSPOSE = __SE_TRANSPOSE_32BIT;
    seTemplate.ICNT0 = 3;
    seTemplate.ICNT1 = vec_len;
    seTemplate.ICNT2 = r/3;
    seTemplate.DIM1 = 3;
    seTemplate.DIM2 = 3*vec_len;

    __SE0_OPEN((void *)&img[0],seTemplate);
```

### Streaming Address Template :

```cpp
__SA_TEMPLATE_v1 saTemplate1 = __gen_SA_TEMPLATE_v1();
    saTemplate1.VECLEN = sa_veclen<float_vec>::value;
    saTemplate1.DIMFMT = __SA_DIMFMT_1D;
    saTemplate1.ICNT0 = r/3;
    __SA0_OPEN(saTemplate1);
```
## Main Function
```cpp
float red=0.29891;
    float green=0.58661;
    float blue=0.11448;


    for(int i=0; i<(r/3);i+=vec_len){
        
        float_vec red_v = strm_eng<0, float_vec>::get_adv();
        float_vec green_v = strm_eng<0, float_vec>::get_adv();
        float_vec blue_v = strm_eng<0, float_vec>::get_adv();

        __vpred pred = strm_agen<0, float_vec>::get_vpred();
        float_vec * addr = strm_agen<0, float_vec>::get_adv(&grey[0]);

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

```