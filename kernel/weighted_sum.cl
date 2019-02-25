__kernel void weighted_sum(__global float *W,
                           __global float *X,
                           __global float B,
                           __global float *O)
{
    //Get the index of the work item
    int index = get_global_id(0);
    O[index] = W[index] * X[index] + B;
}