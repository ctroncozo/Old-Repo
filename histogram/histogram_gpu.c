/**
 * \name histogram_gpu.c
 * \brief generate a histogram on GPU
 * \author Cristian Troncoso
 * \date December 29th, 2016
 * */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include "opencl_init.h"
#include "bitmap.h"
#include "plotHis.h"

#ifdef __APPLE__
  #include <OpenCL/opencl.h>
#else
  #include <CL/cl.h>
#endif

cl_mem device_img_buff;   
cl_mem device_hist_buff;

char *loadBitMap(ME_ImageBMP *bmp, const char *image_name, int *rows, int *cols)
{
  char *src_image = NULL;
  meImageBMP_Init(bmp, image_name);
  src_image = (char*)bmp->imgData;
  *rows = bmp->imgHeight;
  *cols = bmp->imgWidth;
  return src_image;
}

void opencl_init(cl_context *ctx,cl_kernel *kernel, cl_command_queue *queue, const char *kernelpath, const char *kernelname)
{
  cl_platform_id    *platforms;
  cl_device_id      *devices;
  cl_uint           num_of_devices;
  cl_uint           num_of_platforms;
  cl_int            err;
  num_of_platforms = initPlatform(&platforms);

  for(int i = 0; i < num_of_platforms; i++)
  {
    getPlatformInformation(platforms[i]);
    num_of_devices = initDevices(platforms[i], &devices);
    for(int j = 0; j < num_of_devices; j++)
    {
      getDeviceInformation(devices[j]);
    }
  }

  // create context properties
  cl_context_properties cps[3] = {CL_CONTEXT_PLATFORM, (cl_context_properties)platforms[0], 0};
  *ctx = clCreateContext(cps, 1, &devices[2], NULL, NULL, &err);
  checkError(err, "Creating Context");

  
  *kernel = createKernel(kernelpath, *ctx, devices[2], kernelname);
  
  *queue = clCreateCommandQueue(*ctx, devices[2], 0, &err);
  checkError(err, "Creating command_queue");
}

void creatBuffers(cl_context *ctx, cl_command_queue *queue, const cl_event *event_wait_list, 
                  cl_event *event, cl_uint num_events_in_wait_list, const size_t global_work_offset, 
                  const char *host_image, const size_t img_size, const int hist_size)
{
  cl_int err = 0;
  int zero = 0;
  device_img_buff = clCreateBuffer(*ctx, CL_MEM_READ_ONLY, img_size, NULL, &err);
  checkError(err, "Creating device_img_buff");
 
  device_hist_buff= clCreateBuffer(*ctx, CL_MEM_WRITE_ONLY, hist_size, NULL, &err);
  checkError(err, "Creating device_hist_buffer");
  
  err = clEnqueueWriteBuffer( *queue,
                              device_img_buff,
                              CL_TRUE,            //blocking write
                              global_work_offset,          
                              img_size,
                              (void*)host_image,
                              num_events_in_wait_list,
                              event_wait_list,
                              event);
  checkError(err, "Enqueueing image buffer");
  
  err = clEnqueueFillBuffer(  *queue,
                              device_hist_buff,
                              &zero,
                              sizeof(int),
                              global_work_offset,
                              hist_size,
                              num_events_in_wait_list,
                              event_wait_list,
                              event);
  checkError(err, "Enqueuing histogram buffer");

}

void runKernel(cl_kernel *kernel, cl_command_queue *queue, const cl_event *event_wait_list, 
               cl_event *event,cl_uint num_events_in_wait_list, const size_t global_work_offset, 
               int *host_hist, int hist_size, const int num_of_elements)
{
  size_t global_work_size[1]  = {1200};
  size_t local_work_size[1]   = {75};
  cl_uint work_dim            = 1;
  cl_int err                  = 0;
  clSetKernelArg(*kernel, 0, sizeof(cl_mem), &device_img_buff);
  clSetKernelArg(*kernel, 1, sizeof(int),&num_of_elements);
  clSetKernelArg(*kernel, 2, sizeof(cl_mem), (void*)&device_hist_buff);

  err = clEnqueueNDRangeKernel( *queue,
                                *kernel,
                                work_dim,           // 2
                                global_work_offset, // 0
                                global_work_size,   // 1200
                                local_work_size,    // 75
                                num_events_in_wait_list, // 0
                                event_wait_list,    // NULL
                                event);              // NULL;

  checkError(err, "Executing Kernel"); 
  // clEnqueueREadBuffer request that the device send data to the host.
  err = clEnqueueReadBuffer(  *queue,
                              device_hist_buff,
                              CL_TRUE,
                              global_work_offset,
                              hist_size,
                              (void*)host_hist,
                              num_events_in_wait_list,
                              event_wait_list,
                              event);
  checkError(err, "Dequeuing host_hist");
}

int main(int argc, char **argv)
{

  ME_ImageBMP *bmp; 
  cl_context ctx = NULL;
  cl_kernel kernel = NULL;
  cl_command_queue queue = NULL;
  const cl_event *event_wait_list = NULL;
  cl_event *event                 = NULL;
  cl_uint num_events_in_wait_list = 0;
  const size_t global_work_offset = 0;
   
   
  struct timeval t1, t2;
  double elapsedTime;

  int img_rows = 0;
  int img_cols = 0;
  bmp = (ME_ImageBMP*)malloc(sizeof(ME_ImageBMP));

  const char *img_name = "image_4k.bmp";
  const char *host_image = loadBitMap(bmp, img_name, &img_rows, &img_cols);
  const int hist_size = 256 * sizeof(int);
  int   *host_hist = (int*)malloc(hist_size); 
  const char *kernelpath = "./histogram.cl";
  const char *kernelname = "histogram";
  const int num_of_elements = img_rows * img_cols;
  const size_t img_size = 3 * num_of_elements * sizeof(char);
  
  opencl_init(&ctx,&kernel,&queue, kernelpath, kernelname);
  
  // start timer
  gettimeofday(&t1, NULL);

  creatBuffers(&ctx,
               &queue,
               event_wait_list,
               event,
               num_events_in_wait_list,
               global_work_offset,
               host_image,
               img_size, 
               hist_size);
  runKernel(&kernel,
            &queue,event_wait_list, 
            event,
            num_events_in_wait_list,
            global_work_offset,
            host_hist,
            hist_size,
            num_of_elements);

  // stop timer
  gettimeofday(&t2, NULL);
  
  // compute and print the elapsed time in millisec
  elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
  elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
  printf("%f ms.\n", elapsedTime);

  plot(host_hist);
 
  return 0;
}
