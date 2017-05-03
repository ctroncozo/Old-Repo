/**
 * \name opencl_init.h
 * \brief Initialization of OpenCL
 * \author Cristian Troncoso
 * \note Created by Cristian Troncoso on 8/16/15.
 * \copyright  (c) 2015 Cristian Troncoso. All rights reserved.
*/

#ifndef __gpu_info__opencl_init__
#define __gpu_info__opencl_init__

#include <stdio.h>
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#include <unistd.h>
#else
#include <CL/cl.h>
#endif

#define MAX_BINARY_SIZE (0x100000)
#define checkError(E, S) checkError_(E,S,__FILE__,__LINE__)

/**
 * \brief       According to the Platform model, in a typical scenario an OpneCl 
 *              implementation will execute on host x86 CPU, which uses a GPU 
 *              device as an accelerator. This function counts and initializes 
 *              available platforms
 * \param[out]  List of OpenCL platforms (cl_platforms_id*).
 * \return      Number of platforms. 
 */
cl_uint initPlatforms(cl_platform_id **platforms_list);
/**
 * \brief       Initialize devices available on a given platform.
 * \param[in]   Initialized platform (cl_platform_id).   
 * \param[out]  List of OpenCl devices (cl_devices_id*)
 * \return      Number of devices available (int*).
 */
cl_uint initDevices(cl_platform_id platform, cl_device_id **device_list);
/**
 * \brief       Display the information of a given Platform.
 * \params[in]  The platform to investigate (cl_platform_id).
 * \return      Number of devices.
 */
void getPlatformInformation(cl_platform_id platform);
/**
 * \brief       Display information of a given device.
 * \param[in]   The device to investigate (cl_device_id).
 */
void getDeviceInformation(cl_device_id device);
/**
 * \brief       Initialize the OpenCL kernel
 * \param[in]   Name of the kernel file.
 * \param[in]   An initialized context.
 * \parma[in]   Id of the device the kernel will run on.
 * \param[in]   Name of the kernel function
 * \return      The created cl_kernel.
 * */
cl_kernel createKernel(const char *filename, cl_context ctx, cl_device_id device, 
                       const char *kernelname);
/**
 * \brief       Look up and display OpenCL errors code.
 * \params[in]  Error code (cl_int).
 */      
const char *errCode (cl_int err);

void checkError_(cl_int err, const char *operation, char *file_name, int line);

#endif /* defined(__gpu_info__opencl_init__) */
