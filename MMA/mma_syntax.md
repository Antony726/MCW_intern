# MMALIB_LINALG_matrixMatrixMultiply_ixX_ixX_oxX_InitArgs
![alt text](image-8.png)

# MMALIB_LINALG_matrixMatrixMultiply_ixX_ixX_oxX_getHandleSize()
![alt text](image-9.png)

![alt text](image-10.png)

# MMALIB_LINALG_matrixMatrixMultiply_ixX_ixX_oxX_init()
![alt text](image-11.png)

## bufparmas3D
![alt text](image-12.png)


# MMALIB_LINALG_matrixMatrixMultiply_ixX_ixX_oxX_init_checkParams()
- This function checks the parameters and should be called before kernel executuon. It can be called once.

# MMALIB_LINALG_matrixMatrixMultiply_ixX_ixX_oxX_exec()
- It performs Matrix Multiplication.
![alt text](image-13.png)

# cgeck params for exec
![alt text](image-14.png)

# Understanding the handle
- The handle is a pointer used to manage kernel execution and resources efficiently.
- It acts as a <mark>context object, storing information needed for the kernel function </mark>(like matrix dimensions, data addresses, and optimizations).