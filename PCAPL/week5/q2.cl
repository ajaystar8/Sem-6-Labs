__kernel void ones_complement(__global int *A, __global int *B){
    int i = get_global_id(0); 
    int bin = A[i];
}