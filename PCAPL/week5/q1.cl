__kernel void octal_convert(__global int *A, __global int *B){
    int i = get_global_id(0);
    int dec = A[i];
    int oct = 0, r , p = 1;
    while(dec){
        r = dec % 8; 
        oct += p*r;
        dec /= 8;
        p *= 10; 
    }
    B[i] = oct; 
}