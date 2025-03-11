/*******************************************************************************
 **+--------------------------------------------------------------------------+**
 **|                            ****                                          |**
 **|                            ****                                          |**
 **|                            ******o***                                    |**
 **|                      ********_///_****                                   |**
 **|                      ***** /_//_/ ****                                   |**
 **|                       ** ** (__/ ****                                    |**
 **|                           *********                                      |**
 **|                            ****                                          |**
 **|                            ***                                           |**
 **|                                                                          |**
 **|         Copyright (c) 2016 Texas Instruments Incorporated                |**
 **|                        ALL RIGHTS RESERVED                               |**
 **|                                                                          |**
 **| Permission to use, copy, modify, or distribute this software,            |**
 **| whether in part or in whole, for any purpose is forbidden without        |**
 **| a signed licensing agreement and NDA from Texas Instruments              |**
 **| Incorporated (TI).                                                       |**
 **|                                                                          |**
 **| TI makes no representation or warranties with respect to the             |**
 **| performance of this computer program, and specifically disclaims         |**
 **| any responsibility for any damages, special or consequential,            |**
 **| connected with the use of this program.                                  |**
 **|                                                                          |**
 **+--------------------------------------------------------------------------+**
 *******************************************************************************/

// include MMALIB
#include <mmalib.h>

// include test infrastructure provided by MMALIB
#include "../../test/MMALIB_test.h"

#if defined(MMALIB_LDRA_BUILD)

#include "../../test/c71/c7x_ipc/c7x_ldra_remap.h"

#endif

#include <sys/time.h>

#define CPU_FREQ 2e9;


// include test data for this kernel
#include "MMALIB_LINALG_matrixTranspose_ixX_oxX_idat.h"

int main(){

   int32_t row,col;
   // row=4;
   // col=4;
   printf("Enter the value of row:");
   scanf("%d",&row);
   printf("Enter the value of Column:");
   scanf("%d",&col);
   

   int32_t img[row][col];

   for(int i=0;i<row; i++){
      for(int j=0;j<col;j++){
         img[i][j]=i;
      }
   }

   int32_t out[col][row];
   
   for(int i=0;i<col; i++){
      for(int j=0;j<row;j++){
         out[i][j]=0;
      }
   }

   int32_t out_m[col][row];
   
   for(int i=0;i<col; i++){
      for(int j=0;j<row;j++){
         out[i][j]=0;
      }
   }
   struct timeval startttt, sttttop;
   gettimeofday(&startttt, NULL);

   for(int i=0; i<col; i++){
      for(int j=0; j<row; j++){
         out_m[i][j]=img[j][i];
      }
   }
   gettimeofday(&sttttop, NULL);
 
   double elapsed_time = (sttttop.tv_sec - startttt.tv_sec) + (sttttop.tv_usec - startttt.tv_usec) / 1e6;
   double estimated_cycles = elapsed_time * CPU_FREQ;
   printf("Execution time of Normal_Transpose: %f seconds\n", elapsed_time);
   printf("Estimated cycle count of Normal_Transpose: %.0f cycles\n", estimated_cycles);
   printf("________________________________________________________________________________________________________________");

   struct timeval start, stop;
   gettimeofday(&start, NULL);


   MMALIB_LINALG_matrixTranspose_ixX_oxX_InitArgs    kerInitArgs;
   int32_t handleSize = MMALIB_LINALG_matrixTranspose_ixX_oxX_getHandleSize(&kerInitArgs);
   MMALIB_kernelHandle handle = malloc(handleSize);
   MMALIB_STATUS   status_init = MMALIB_SUCCESS;
   MMALIB_STATUS   status_opt = MMALIB_SUCCESS;

   MMALIB_bufParams2D_t In, Out;

   In.dim_x = row;
   In.dim_y = col;
   In.stride_y = col * sizeof(int32_t);
   In.data_type = MMALIB_INT32;

   Out.dim_x = col;
   Out.dim_y = row;
   Out.stride_y = row * sizeof(int32_t);
   Out.data_type = MMALIB_INT32;

   status_init = MMALIB_LINALG_matrixTranspose_ixX_oxX_init_checkParams(handle,&In,&Out,&kerInitArgs);
   kerInitArgs.funcStyle = MMALIB_FUNCTION_OPTIMIZED;
   status_init = MMALIB_LINALG_matrixTranspose_ixX_oxX_init(handle,&In,&Out,&kerInitArgs);
   status_opt = MMALIB_LINALG_matrixTranspose_ixX_oxX_exec_checkParams(handle,img,out);
   status_opt = MMALIB_LINALG_matrixTranspose_ixX_oxX_exec(handle,img,out);

   gettimeofday(&stop, NULL);
 
   double elapsed_timee = (stop.tv_sec - start.tv_sec) + (stop.tv_usec - start.tv_usec) / 1e6;
    // cout<<stop.tv_sec<<" "<<start.tv_sec<<"\n"<<stop.tv_usec<<" "<<start.tv_usec;
   double estimated_cyclees = elapsed_timee * CPU_FREQ;
 
   printf("\n Execution time of MMA_Transpose: %f seconds\n", elapsed_timee);
   printf("Estimated cycle count of MMA_Transpose: %.0f cycles\n", estimated_cyclees);

   printf("-------------------------------------------------------------------------------------------------------------------\n");
   // printf("%d",status_init);

   // for(int i=0; i<row; i++){
   //    for(int j=0; j<col; j++){
   //       printf("%d | ",img[i][j]);
   //    }
   //    printf("\n");
   // }
   


   for(int i=0; i<col; i++){
      for(int j=0; j<row; j++){
         // printf("%d = %d | ",out[i][j],out_m[i][j]);
         if(out[i][j]!=out_m[i][j]){
            printf("Not Equal!!! \n");
            return -1;
         }
      }
      // printf("\n");
   }

   printf("EQUAL !!! \n");
   return 0;


}