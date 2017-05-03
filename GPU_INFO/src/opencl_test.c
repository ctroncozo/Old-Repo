/**
 * \name opencl_test.c
 * \brief Test OpenCL implementation
 * \author Cristian Troncoso
 * \date June 23th, 2016
*/

#include <stdio.h>
#include <stdlib.h>

#include <OpenCL/opencl.h>
#include "opencl_init.h"

/**
 * \brief   Test all functions from opencl_init.c
 * void initPlatforms(cl_platform_id *platforms, cl_int &num_of_platforms) - Tested
 * void initDevices(cl_platform_id platform, cl_device_id *devices, cl_int &num_of_devices)- Tested
 * void getPlatformInformation(cl_platform_id platform) - Tested
 * void getDeviceInformation(cl_device_id device) - Tested
 */
cl_platform_id *platforms;
cl_uint num_of_platforms;
cl_device_id *devices;
cl_uint num_of_devices;

void test_opencl_init()
{
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
}

int main(void)
{
  test_opencl_init(); 
  cl_int err;
  cl_context_properties cps[3] = { CL_CONTEXT_PLATFORM, (cl_context_properties)platforms[0],0};
  ///
  //Context is an abstract environment within which coordination and memory management for 
  //kernel execution is valid and well defined. It coordinated mechanisms for hos-device
  //interaction, manages the memory objects available to the device, and keeps track of 
  //the program and kernels that created for each device
  cl_context ctx;
  ctx = clCreateContext(cps, 1, &devices[1], NULL, NULL, &err);
  checkError(err, "Creating context");

  const char *path = "./src/kernel.cl";
  const char *name = "matrixMultiply";
  cl_kernel k =  createKernel(path, ctx, devices[1], name);
}
