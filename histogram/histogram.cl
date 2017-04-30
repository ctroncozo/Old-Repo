__kernel void histogram(__global char *data, int numData, __global int *histogram)
{
  __local int localHist[256];
  int lid = get_local_id(0);
  int gid = get_global_id(0) * 3;
  
  /* initialize local historgram to zero */
  for(int i = lid; i < 256; i+= get_local_size(0))
  {
    localHist[i] = 0;
  }

  barrier(CLK_LOCAL_MEM_FENCE);

  for(int i = gid; i < numData * 3; i += get_global_size(0))
  {
    unsigned char r = data[i];
    unsigned char g = data[i + 1];
    unsigned char b = data[i + 2];
    unsigned char gray = (r + b + g) / 3;
       
    atomic_add(&localHist[gray], 1);
  }

  barrier(CLK_LOCAL_MEM_FENCE);

  for(int i = lid; i < 256; i += get_local_size(0))
  {
    atomic_add(&histogram[i], localHist[i]);
  }

}
        
