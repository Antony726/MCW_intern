
#include <mmalib.h>

// include test infrastructure provided by MMALIB
#include "../../test/MMALIB_test.h"

#if defined(MMALIB_LDRA_BUILD)

#include "../../test/c71/c7x_ipc/c7x_ldra_remap.h"

#endif

#include <sys/time.h>

#define CPU_FREQ 2e9;

// include test data for this kernel
#include "MMALIB_LINALG_pointwiseMatrixMatrixMultiply_ixX_ixX_oxX_idat.h"

int main(){
	int32_t row, col;
	printf("Enter number of Rows :");
	scanf("%d",&row);
	printf("Enter number of columns :");
	scanf("%d",&col);
	// row=4;
	// col=4;
	int32_t arr_A[row][col];
	int32_t arr_B[row][col];
	int32_t out[row][col];
	int32_t out_m[row][col];


	int32_t count = 1;
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			arr_A[i][j] = count;
			arr_B[i][j] = count++;
			out[i][j] = 0;
		}
	}

	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			out_m[i][j]=0;
		}
	}

	struct timeval startttt, sttttop;
    gettimeofday(&startttt, NULL);

	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			out_m[i][j] = arr_A[i][j] * arr_B[i][j];
		}
	}

	gettimeofday(&sttttop, NULL);
 
	double elapsed_time = (sttttop.tv_sec - startttt.tv_sec) + (sttttop.tv_usec - startttt.tv_usec) / 1e6;
	double estimated_cycles = elapsed_time * CPU_FREQ;
	
	printf("Execution time of Normal_MULTIPLICATION_ACCU: %f seconds\n", elapsed_time);
	printf("Estimated cycle count of Normal_MULTIPLICATION_ACCU: %.0f cycles\n", estimated_cycles);
	printf("________________________________________________________________________________________________");

	MMALIB_LINALG_pointwiseMatrixMatrixMultiply_ixX_ixX_oxX_InitArgs    kerInitArgs;
	int32_t handleSize = MMALIB_LINALG_pointwiseMatrixMatrixMultiply_ixX_ixX_oxX_getHandleSize(&kerInitArgs);
	MMALIB_kernelHandle handle = malloc(handleSize);
	kerInitArgs.shift = 0;

	MMALIB_bufParams2D_t    src0_addr, src1_addr, dst_addr;

	src0_addr.dim_x = row;
	src0_addr.dim_y = col;
	src0_addr.stride_y = col * sizeof(int32_t);
	src0_addr.data_type = MMALIB_INT32;

	src1_addr.dim_x = row;
	src1_addr.dim_y = col;
	src1_addr.stride_y = col * sizeof(int32_t);
	src1_addr.data_type = MMALIB_INT32;

	dst_addr.dim_x = row;
	dst_addr.dim_y = col;
	dst_addr.stride_y = col * sizeof(int32_t);
	dst_addr.data_type = MMALIB_INT32;

	MMALIB_STATUS   status_init = MMALIB_SUCCESS;
	MMALIB_STATUS   status_opt = MMALIB_SUCCESS;

	status_init = MMALIB_LINALG_pointwiseMatrixMatrixMultiply_ixX_ixX_oxX_init_checkParams(handle, &src0_addr, &src1_addr, &dst_addr, &kerInitArgs);
	if(status_init == MMALIB_SUCCESS){
		
		kerInitArgs.funcStyle = MMALIB_FUNCTION_OPTIMIZED;
		status_init = MMALIB_LINALG_pointwiseMatrixMatrixMultiply_ixX_ixX_oxX_init(handle,
										&src0_addr,
										&src1_addr,
										&dst_addr,
										&kerInitArgs);    
	} else {
		printf("Failed wit code : %d", status_init);
	}
	if(status_init == MMALIB_SUCCESS){
		status_opt = MMALIB_LINALG_pointwiseMatrixMatrixMultiply_ixX_ixX_oxX_exec_checkParams(handle, arr_A, arr_B, out);
		if(status_opt == MMALIB_SUCCESS){
			struct timeval start, stop;
			gettimeofday(&start, NULL);	
			status_opt = MMALIB_LINALG_pointwiseMatrixMatrixMultiply_ixX_ixX_oxX_exec(handle, arr_A, arr_B, out);
			gettimeofday(&stop, NULL);
 
			double elapsed_timee = (stop.tv_sec - start.tv_sec) + (stop.tv_usec - start.tv_usec) / 1e6;
				// cout<<stop.tv_sec<<" "<<start.tv_sec<<"\n"<<stop.tv_usec<<" "<<start.tv_usec;
			double estimated_cyclees = elapsed_timee * CPU_FREQ;
			
			printf("\n Execution time of MMA_MULTIPLICATION_ACCU: %f seconds\n", elapsed_timee);
			printf("Estimated cycle count of MMA_MULTIPLICATION_ACCU: %.0f cycles\n", estimated_cyclees);

			printf("-------------------------------------------------------------------------------------------------------------------\n");
		}
	}

	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			// printf("%d | ",out[i][j]);
			if(out_m[i][j]!=out[i][j]){
				printf("Not Equal");
				return -1;
			}
		}
		// printf("\n");
	}
	printf("Equal !!");
	return 0;

	

	
}