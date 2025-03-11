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
#include "MMALIB_LINALG_matrixMatrixMultiplyAccumulate_ixX_ixX_ixX_oxX_idat.h"


int main(){
	int32_t row, col, k;
	// row=4;
	// col=4;
	// k=4;

	printf("Enter the value of row:");
	scanf("%d",&row);
	printf("Enter the value of Column:");
	scanf("%d",&col);
	printf("Enter the value of K:");
	scanf("%d",&k);

	int32_t arr_A[row][k];
	int32_t arr_B[k][col];
	int32_t arr_C[row][col];
	int32_t out[row][col];

	int32_t count=1;

	for(int i=0; i<row; i++){
		for(int j=0; j<k; j++){
			arr_A[i][j]=count++;
		}
	}

	count = 1;
	for(int i=0; i<k; i++){
		for(int j=0; j<col; j++){
			arr_B[i][j]=count++;
		}
	}

	count = 1;
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			arr_C[i][j]=count++;
		}
	}

	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			out[i][j]=0;
		}
	}

	int32_t out_m[row][col];

	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			out_m[i][j]=0;
		}
	}
	struct timeval startttt, sttttop;
    gettimeofday(&startttt, NULL);

	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			for(int K=0; K<k; K++){
				out_m[i][j]+=arr_A[i][K]*arr_B[K][j];

			}
		}
	}
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			out_m[i][j]=out_m[i][j]+arr_C[i][j];
			
		}
	}

	gettimeofday(&sttttop, NULL);
 
	double elapsed_time = (sttttop.tv_sec - startttt.tv_sec) + (sttttop.tv_usec - startttt.tv_usec) / 1e6;
	double estimated_cycles = elapsed_time * CPU_FREQ;
	
	printf("Execution time of Normal_MULTIPLICATION_ACCU: %f seconds\n", elapsed_time);
	printf("Estimated cycle count of Normal_MULTIPLICATION_ACCU: %.0f cycles\n", estimated_cycles);
	printf("________________________________________________________________________________________________________________");


	struct timeval start, stop;
	gettimeofday(&start, NULL);

	


	MMALIB_LINALG_matrixMatrixMultiplyAccumulate_ixX_ixX_ixX_oxX_InitArgs    kerInitArgs;

	int32_t handleSize = MMALIB_LINALG_matrixMatrixMultiplyAccumulate_ixX_ixX_ixX_oxX_getHandleSize(&kerInitArgs);
	MMALIB_kernelHandle handle = malloc(handleSize);
   	kerInitArgs.shift = 0;
  

	MMALIB_bufParams2D_t    src0_addr, src1_addr, src2_addr, dst_addr;

	src0_addr.dim_x = row;
	src0_addr.dim_y = k;
	src0_addr.stride_y = k * sizeof(int32_t);
	src0_addr.data_type = MMALIB_INT32;

	src1_addr.dim_x = k;
	src1_addr.dim_y = col;
	src1_addr.stride_y = col * sizeof(int32_t);
	src1_addr.data_type = MMALIB_INT32;

	src2_addr.dim_x = row;
	src2_addr.dim_y = col;
	src2_addr.stride_y = col * sizeof(int32_t);
	src2_addr.data_type = MMALIB_INT32;

	dst_addr.dim_x = row;
	dst_addr.dim_y = col;
	dst_addr.stride_y = col * sizeof(int32_t);
	dst_addr.data_type = MMALIB_INT32;

	MMALIB_STATUS   status_init = MMALIB_SUCCESS;
	MMALIB_STATUS   status_opt = MMALIB_SUCCESS;
	// printf("OKAY");


	status_init = MMALIB_LINALG_matrixMatrixMultiplyAccumulate_ixX_ixX_ixX_oxX_init_checkParams(handle, &src0_addr, &src1_addr, &src2_addr, &dst_addr, &kerInitArgs);
	// printf(" \n %d", status_init);
	if(status_init == MMALIB_SUCCESS){
		// printf("INIT done");
		
		kerInitArgs.funcStyle = MMALIB_FUNCTION_OPTIMIZED;
		status_init = MMALIB_LINALG_matrixMatrixMultiplyAccumulate_ixX_ixX_ixX_oxX_init(handle,
			&src0_addr,
			&src1_addr,
			&src2_addr,
			&dst_addr,
			&kerInitArgs);
		
	}
	if (status_init == MMALIB_SUCCESS){
	
		// printf("EXC done");
		status_opt = MMALIB_LINALG_matrixMatrixMultiplyAccumulate_ixX_ixX_ixX_oxX_exec_checkParams(handle, arr_A, arr_B, arr_C, out);
		if(status_opt == MMALIB_SUCCESS){
			status_opt = MMALIB_LINALG_matrixMatrixMultiplyAccumulate_ixX_ixX_ixX_oxX_exec(handle, arr_A, arr_B, arr_C, out);
		
		}
	}
	gettimeofday(&stop, NULL);
 
	double elapsed_timee = (stop.tv_sec - start.tv_sec) + (stop.tv_usec - start.tv_usec) / 1e6;
		// cout<<stop.tv_sec<<" "<<start.tv_sec<<"\n"<<stop.tv_usec<<" "<<start.tv_usec;
	double estimated_cyclees = elapsed_timee * CPU_FREQ;
	
	printf("\n Execution time of MMA_MULTIPLICATION_ACCU: %f seconds\n", elapsed_timee);
	printf("Estimated cycle count of MMA_MULTIPLICATION_ACCU: %.0f cycles\n", estimated_cyclees);

	printf("-------------------------------------------------------------------------------------------------------------------\n");

	// for(int i=0; i<row; i++){
	// 	for(int j=0; j<col; j++){
	// 		printf("%d | ",out[i][j]);
	// 	}
	// 	printf("\n");
	// }
	// printf("_____________________________________________________________________________________\n");

	// for(int i=0; i<row; i++){
	// 	for(int j=0; j<col; j++){
	// 		printf("%d | ",out_m[i][j]);
	// 	}
	// 	printf("\n");
	// }

	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			if(out[i][j]!=out_m[i][j]){
				printf("NOT EQUAL!!!!!!!! \n");
				return -1;
			}
			// printf("%d = %d | ", out_m[i][j],out[i][j]);
		}
		
	}

	printf("EQUAL !!\n");
	return 0;







}