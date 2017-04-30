/**
 * \name opencl_init.c
 * \brief Test OpenCL implementation
 * \author Cristian Troncoso
 * \date June 23, 2016
*/

#include "opencl_init.h"
cl_uint initPlatform(cl_platform_id **platforms_list)
{
  cl_int err;
  cl_uint num_platforms;
  cl_platform_id * platforms;
  ///
  // clGetPlatformIDs() is used to discover the set of available platforms 
  // for a given system. It will be often called twice by an application. 
  // The first call passes an unsigned int pointer as the num_platforms 
  // argument and NULL is passed as the platform's argument.
  // The programmer can then allocate space to hold the platform information.
  // The second call creates and populate a list of platforms IDs.
  //
  err = clGetPlatformIDs(0, NULL, &num_platforms);
  checkError(err,"clGetPlatformIDs - Discovering set of available platforms");
  if(num_platforms == 0)
  {
    printf("Found 0 platforms!\n");
    return -1 ;//return EXIT_FAILURE;
  }
  /// Allocate space to hold the platform information
  platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id) * num_platforms);
  ///
  //For the second call, a cl_platform_id pointer is passed to create a list of 
  //platforms IDs.
  err = clGetPlatformIDs(num_platforms, platforms,NULL);
  checkError(err,"clGetPlatformIDs - Creating list of platforms IDs");
  *platforms_list = platforms;
  return num_platforms;
}

cl_uint initDevices(cl_platform_id platform, cl_device_id **devices_list)
{
  cl_int err;
  cl_device_id *devices;
  cl_uint num_devices;
  /// Count number of devices in platform
  err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices);
  checkError(err, "clGetDeviceIDs - Discovering available devices");
  /// Allocate memory for devices
  devices = (cl_device_id*)malloc(sizeof(cl_platform_id) * num_devices);
  /// Get Devices Id
  err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, num_devices, devices, NULL);
  checkError(err, "clGetDeviceIDs - Creating list of devices IDs");
  *devices_list = devices;
  return num_devices;
}

void getPlatformInformation(cl_platform_id platform)
{
  printf("-----------------------------------------\n");
  printf("Platform Info\n"); 
  printf("-----------------------------------------\n");
  cl_int err;
  cl_char buff[10240] = {0};
  cl_int buff_size = sizeof(buff);
  /// Print platform's name.
  err = clGetPlatformInfo(platform, CL_PLATFORM_NAME, buff_size, &buff, NULL);
  checkError(err, "Getting Platform's Name");
  printf("CL_PLATFORM_NAME \t: %s\n",buff);
  /// Print platform's vendor.
  err = clGetPlatformInfo(platform, CL_PLATFORM_VENDOR, buff_size, &buff, NULL);
  checkError(err, "Getting Platform's Vendor");
  printf("CL_PLATFORM_VENDOR \t: %s\n",buff);
  /// Print Platforms OpenCl version
  err = clGetPlatformInfo(platform, CL_PLATFORM_VERSION, buff_size, &buff, NULL);
  checkError(err, "Getting Platform's Version");
  printf("CL_PLATFORM_VERSION \t: %s\n",buff);
  /// End
 
}

void getDeviceInformation(cl_device_id device)
{
  // For documentation on clGetDeviceInfo() go to :
  // https://www.khronos.org/registry/cl/sdk/1.0/docs/man/xhtml/clGetDeviceInfo.html
  cl_int err;
  cl_char buff[10240];
  cl_int buff_size = sizeof(buff);
  cl_uint num;
  cl_ulong mem_size;
  size_t size;
  //size_t *dims;
  // Get device name
  err = clGetDeviceInfo(device, CL_DEVICE_NAME, buff_size, &buff, NULL);
  checkError(err, "Getting device name");

  printf("\t\t--------------------------------------------------------------\n");
  printf("\t\tName: %s\n", buff);
  printf("\t\t--------------------------------------------------------------\n");
 
  // cl_device_vendor
  err = clGetDeviceInfo(device, CL_DEVICE_VENDOR, buff_size, &buff, NULL);
  checkError(err, "Getting CL_DEVICE_VENDOR c version"); 
  printf("\t\tCL_DEVICE_VENDOR \t\t  : %s\n", buff);

  // Get device OpenCL version
  err = clGetDeviceInfo(device, CL_DEVICE_OPENCL_C_VERSION, buff_size, &buff, NULL);
  checkError(err, "Getting device OpenCL C version");
  printf("\t\tCL_DRIVER_VERSION \t\t  : %s\n", buff);
  
  // cl_device_info
  cl_device_type type;
  err = clGetDeviceInfo(device, CL_DEVICE_TYPE, sizeof(type), &type, NULL);
  checkError(err, "Getting CL_DEVICE_TYPE c version");
  if(type & CL_DEVICE_TYPE_CPU)
    printf("\t\tCL_DEVICE_TYPE \t\t\t  : %s\n", "CL_DEVICE_TYPE_CPU");
  if(type & CL_DEVICE_TYPE_GPU)
    printf("\t\tCL_DEVICE_TYPE \t\t\t  : %s\n", "CL_DEVICE_TYPE_GPU");
  if(type & CL_DEVICE_TYPE_ACCELERATOR)
    printf("\t\nCL_DEVICE_TYPE \t\t\t  : %s\n", "CL_DEVICE_TYPE_ACCELERATOR");
  if(type & CL_DEVICE_TYPE_DEFAULT)
    printf("\t\tCL_DEVICE_TYPE \t\t\t  : %s\n", "CL_DEVICE_TYPE_DEFAULT");


  // cl_device_max_compute_units
  err = clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &num, NULL);
  checkError(err, "Getting device max compute units");
  printf("\t\tCL_DEVICE_MAX_COMPUTE_UNITS \t  : %d\n", num);

  // cl_device_max_work_time_dimensions
  size_t workitem_dim;
  err = clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(workitem_dim), 
                        &workitem_dim, NULL);
  checkError(err, "Getting device max work-item dims");
  printf("\t\tCL_DEVICE_MAX_WORK_ITEM_DIMENSIONS: %u\n", workitem_dim);
  
  /* Showing erro  Error code : (-59), Error name : 'CL_INVALID_OPERATION'
  // cl_kernel_work_group_size
  if(type & CL_DEVICE_TYPE_GPU || type & CL_DEVICE_TYPE_ACCELERATOR)
  {
    size_t dim_kernel[3];
    err = clGetDeviceInfo(device, CL_KERNEL_WORK_GROUP_SIZE, sizeof(dim_kernel),
                          &dim_kernel, NULL);
    checkError(err, "cl_kernel_work_group_size");
    printf("\t\tCL_KERNEL_WORK_GROUP_SIZE \t  : ( ");
    for(size_t k = 0; k < 3; k++) printf("%ld ", dim_kernel[k]);
    printf(")\n");
  }
  */

  // cl_device_max_work_item_size 
  size_t dims[3];
  err = clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(dims), &dims, NULL);
  checkError(err, "Getting device max work-item sizes");
  printf("\t\tCL_DEVICE_MAX_WORK_ITEM_SIZE \t  : ( ");
  for (size_t k = 0; k < 3; k++) printf("%ld ", dims[k]);
  printf(")\n");
  
  // cl_device_max_work_group_size
  err = clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), &size, NULL);
  checkError(err, "Getting device max work-group size");
  printf("\t\tCL_DEVICE_MAX_WORK_GROUP_SIZE \t  : %ld\n", size);

  // cl_device_max_clock_frequency
  cl_uint clock_freq;
  err = clGetDeviceInfo(device, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(clock_freq), &clock_freq, NULL);
  checkError(err, "Getting device max clock frequency");
  printf("\t\tCL_DEVICE_MAX_CLOCK_FREQUENCY \t  : %u MHz\n", clock_freq);
  
  // cl_device_address_bits
  cl_uint addr_bits;
  err = clGetDeviceInfo(device, CL_DEVICE_ADDRESS_BITS, sizeof(addr_bits), &addr_bits, NULL);
  checkError(err, "Getting device address bits");
  printf("\t\tCL_DEVICE_ADDRESS_BITS \t\t  : %u\n", addr_bits); 

  // cl_device_max_mem_alloc_size
  err = clGetDeviceInfo(device, CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(cl_ulong), &mem_size, NULL);
  checkError(err, "Getting device max allocation size");
  printf("\t\tCL_DEVICE_MAX_MEM_ALLOC_SIZE \t  : %llu MB\n", mem_size/(1024*1024));

  // cl_device_global_mem_size
  err = clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cl_ulong), &mem_size, NULL);
  checkError(err, "Getting device global memory size");
  printf("\t\tCL_DEVICE_GLOBAL_MEM_SIZE \t  : %llu MB\n", mem_size/(1024*1024));

  // cl_device_local_mem_type
  cl_device_local_mem_type mem_type;
  err = clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_TYPE, sizeof(cl_device_local_mem_type), 
                        &mem_type, NULL);
  checkError(err, "Getting device local memory type");
  printf("\t\tCL_DEVICE_LOCAL_MEM_TYPE \t  : %s\n", mem_type == 1 ? "local":"global");

  // cl_device_local_mem_size
  err = clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(cl_ulong), &mem_size, NULL);
  checkError(err, "Getting device local memory size");
  printf("\t\tCL_DEVICE_LOCAL_MEM_SIZE \t  : %llu KB\n", mem_size/1024);

  // cl_device_max_const_buffer_size
  err = clGetDeviceInfo(device, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, sizeof(mem_size), &mem_size, NULL); 
  checkError(err, "Getting cl_device_max_const_buffer_size");
  printf("\t\tCL_DEVICE_MAX_CONSTANT_BUFFER_SIZE: %llu KB\n", mem_size/1024);

  // cl_device_queue_properties
  cl_command_queue_properties queue_properties;
  err = clGetDeviceInfo(device, CL_DEVICE_QUEUE_PROPERTIES, sizeof(queue_properties), 
                       &queue_properties, NULL);
  checkError(err, "Getting command queue properties");
  if(queue_properties & CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE)
    printf("\t\tCL_DEVICE_QUEUE_PROPERTIES \t  : %s\n", "CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE");
  if(queue_properties & CL_QUEUE_PROFILING_ENABLE)
    printf("\t\tCL_DEVICE_QUEUE_PROPERTIES \t  : %s\n", "CL_QUEUE_PROFILING_ENABLE");

  // cl_device_image_support
  cl_bool img_support;
  err = clGetDeviceInfo(device, CL_DEVICE_IMAGE_SUPPORT, sizeof(img_support), &img_support, NULL);
  checkError(err, "Getting cl image support");
  printf("\t\tCL_DEVICE_IMAGE_SUPPPORT \t  : %u\n", img_support);

  // cl_device_max_read_image_args
  cl_uint max_read_img_args;
  err = clGetDeviceInfo(device, CL_DEVICE_MAX_READ_IMAGE_ARGS, sizeof(max_read_img_args),
                        &max_read_img_args, NULL);
  checkError(err, "Getting cl_device_max_read_image_args");
  printf("\t\tCL_DEVICE_MAX_READ_IMAGE_ARGS \t  : %u\n", max_read_img_args);
  
  // cl_device_max_write_image_args
  cl_uint max_write_img_args;
  err = clGetDeviceInfo(device, CL_DEVICE_MAX_WRITE_IMAGE_ARGS, sizeof(max_write_img_args), 
                        &max_write_img_args, NULL);
  checkError(err, "Getting cl_device_max_write_image_args");
  printf("\t\tCL_DEVICE_MAX_WRITE_IMAGE_ARGS \t  : %u\n", max_write_img_args);

  size_t szMaxDim[5];
  printf("\t\tCL_DEVICE_IMAGE <dim> \t\t  : ");
  
  err = clGetDeviceInfo(device, CL_DEVICE_IMAGE2D_MAX_WIDTH, sizeof(size_t), &szMaxDim[0], NULL);
  checkError(err, "Getting cl_device_image2d_max_width");
  printf("2D_MAX_WIDTH \t %zu\n", szMaxDim[0]); 
  
  err = clGetDeviceInfo(device, CL_DEVICE_IMAGE2D_MAX_HEIGHT, sizeof(size_t), &szMaxDim[1], NULL);
  checkError(err, "Getting cl_device_image2d_max_height");
  printf("\t\t\t\t\t\t    2D_MAX_HEIGHT \t %zu\n", szMaxDim[1]); 
  
  err = clGetDeviceInfo(device, CL_DEVICE_IMAGE3D_MAX_WIDTH, sizeof(size_t), &szMaxDim[2], NULL);
  checkError(err, "Getting cl_device_image3d_max_width");
  printf("\t\t\t\t\t\t    3D_MAX_WIDTH \t %zu\n", szMaxDim[2]); 
  
  err = clGetDeviceInfo(device, CL_DEVICE_IMAGE3D_MAX_HEIGHT, sizeof(size_t), &szMaxDim[3], NULL);
  checkError(err, "Getting cl_device_image2d_max_height");
  printf("\t\t\t\t\t\t    3D_MAX_height \t %zu\n", szMaxDim[3]); 
  
  err = clGetDeviceInfo(device, CL_DEVICE_IMAGE3D_MAX_DEPTH, sizeof(size_t), &szMaxDim[4], NULL);
  checkError(err, "Getting cl_device_image3d_max_depth");
  printf("\t\t\t\t\t\t    3D_MAX_DEPTH \t %zu\n", szMaxDim[4]); 

}

cl_kernel createKernel(const char *filename, cl_context ctx, cl_device_id device, 
                       const char *kernelname)
{
  ///
  //The process of creating a kernel from source code is a follow:
  //1. The OpenCL source is stored in a character array.
  //2. The source code is turned into a program object (cl_program) 
  //by calling clCreateProgramWithSource()
  //3. The program object is then compiled, for one or more devices, with clBuildProgram()
  //4. A kernel object (cl_kernel) is then created with clCreateKernel and specifying the 
  //program object and kernel name.
  //
  //An additional feature of the build process is the ability of generate both the final
  //binary format and various intermediate representations and serialize them (e.g. write
  //them to disk)
  //OpenCL provide a function to return information about the program object
  //(clGetProgramInfo). One of the flags to this function is CL_PROGRAM_BINARIES,
  //which returns a vendor-specific set of binary objects generated by clBuildProgram().
  //In addition to clCreateProgramWithSource, OpenCL provides clCreateProgramWithBinary(),
  //which take a list of binaries that matches its device list. The binaries are
  //previously creates using clGetProgramInfo(). Using binary representation of OpenCL 
  //kernels allows OpenCL programs to be distributed without exposing source code.
  FILE *fp;
  size_t binary_size;
  char *source;
  cl_int err;
  size_t log_size;
  char *log;
  cl_kernel kernel;

  // load binary kernel
  fp = fopen(filename, "r");
  if(!fp){} // TODO: need to fix this
  source = (char*)malloc(MAX_BINARY_SIZE);
  binary_size = fread(source, 1, MAX_BINARY_SIZE, fp);
  fclose(fp);

  cl_program program = clCreateProgramWithSource(ctx, 1, (const char**)&source, NULL,&err); 
  checkError(err, "Loading binary kernel");
  
  // compile program
  err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
  if (err == CL_BUILD_PROGRAM_FAILURE) 
  {
    //Determine the size of the log
    size_t log_size;
    clGetProgramBuildInfo(program, device,
        CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

    // Allocate memory for the log
    char *log = (char *) malloc(log_size);

    // Get the log
    clGetProgramBuildInfo(program,
        device,
        CL_PROGRAM_BUILD_LOG, log_size,
        log, NULL);

    // Print the log
    printf("%s\n", log);
  }
  checkError(err, "Building kernel");
  
  err = clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
  checkError(err, "Getting log size");

  log = (char*)malloc(log_size);
  
  err = clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
  checkError(err, "Retrieving log");

  printf("%s\n", log);

  // create kernel
  kernel = clCreateKernel(program, kernelname, &err);
  checkError(err, "Creating kernel");
  
  if(err == CL_SUCCESS)
    printf(" Create Kernel SUCCESS\n");
  return kernel;
}

void checkError_(cl_int err, const char *operation, char *file_name, int line)
{
  if(err != CL_SUCCESS)
  {
     printf("Error while calling '%s\n',",operation);
     printf("File : '%s', Line: '%d'\n", file_name, line);
     printf("Error code : (%d), Error name : '%s'\n",err, errCode(err));
     exit (-1);//exit(EXIT_FAILURE);
  }
}

const char *errCode (cl_int err)
{
    switch (err) {
        case CL_SUCCESS:
            return (char*)"CL_SUCCESS";
        case CL_DEVICE_NOT_FOUND:
            return (char*)"CL_DEVICE_NOT_FOUND";
        case CL_DEVICE_NOT_AVAILABLE:
            return (char*)"CL_DEVICE_NOT_AVAILABLE";
        case CL_COMPILER_NOT_AVAILABLE:
            return (char*)"CL_COMPILER_NOT_AVAILABLE";
        case CL_MEM_OBJECT_ALLOCATION_FAILURE:
            return (char*)"CL_MEM_OBJECT_ALLOCATION_FAILURE";
        case CL_OUT_OF_RESOURCES:
            return (char*)"CL_OUT_OF_RESOURCES";
        case CL_OUT_OF_HOST_MEMORY:
            return (char*)"CL_OUT_OF_HOST_MEMORY";
        case CL_PROFILING_INFO_NOT_AVAILABLE:
            return (char*)"CL_PROFILING_INFO_NOT_AVAILABLE";
        case CL_MEM_COPY_OVERLAP:
            return (char*)"CL_MEM_COPY_OVERLAP";
        case CL_IMAGE_FORMAT_MISMATCH:
            return (char*)"CL_IMAGE_FORMAT_MISMATCH";
        case CL_IMAGE_FORMAT_NOT_SUPPORTED:
            return (char*)"CL_IMAGE_FORMAT_NOT_SUPPORTED";
        case CL_BUILD_PROGRAM_FAILURE:
            return (char*)"CL_BUILD_PROGRAM_FAILURE";
        case CL_MAP_FAILURE:
            return (char*)"CL_MAP_FAILURE";
        case CL_MISALIGNED_SUB_BUFFER_OFFSET:
            return (char*)"CL_MISALIGNED_SUB_BUFFER_OFFSET";
        case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:
            return (char*)"CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
        case CL_INVALID_VALUE:
            return (char*)"CL_INVALID_VALUE";
        case CL_INVALID_DEVICE_TYPE:
            return (char*)"CL_INVALID_DEVICE_TYPE";
        case CL_INVALID_PLATFORM:
            return (char*)"CL_INVALID_PLATFORM";
        case CL_INVALID_DEVICE:
            return (char*)"CL_INVALID_DEVICE";
        case CL_INVALID_CONTEXT:
            return (char*)"CL_INVALID_CONTEXT";
        case CL_INVALID_QUEUE_PROPERTIES:
            return (char*)"CL_INVALID_QUEUE_PROPERTIES";
        case CL_INVALID_COMMAND_QUEUE:
            return (char*)"CL_INVALID_COMMAND_QUEUE";
        case CL_INVALID_HOST_PTR:
            return (char*)"CL_INVALID_HOST_PTR";
        case CL_INVALID_MEM_OBJECT:
            return (char*)"CL_INVALID_MEM_OBJECT";
        case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
            return (char*)"CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
        case CL_INVALID_IMAGE_SIZE:
            return (char*)"CL_INVALID_IMAGE_SIZE";
        case CL_INVALID_SAMPLER:
            return (char*)"CL_INVALID_SAMPLER";
        case CL_INVALID_BINARY:
            return (char*)"CL_INVALID_BINARY";
        case CL_INVALID_BUILD_OPTIONS:
            return (char*)"CL_INVALID_BUILD_OPTIONS";
        case CL_INVALID_PROGRAM:
            return (char*)"CL_INVALID_PROGRAM";
        case CL_INVALID_PROGRAM_EXECUTABLE:
            return (char*)"CL_INVALID_PROGRAM_EXECUTABLE";
        case CL_INVALID_KERNEL_NAME:
            return (char*)"CL_INVALID_KERNEL_NAME";
        case CL_INVALID_KERNEL_DEFINITION:
            return (char*)"CL_INVALID_KERNEL_DEFINITION";
        case CL_INVALID_KERNEL:
            return (char*)"CL_INVALID_KERNEL";
        case CL_INVALID_ARG_INDEX:
            return (char*)"CL_INVALID_ARG_INDEX";
        case CL_INVALID_ARG_VALUE:
            return (char*)"CL_INVALID_ARG_VALUE";
        case CL_INVALID_ARG_SIZE:
            return (char*)"CL_INVALID_ARG_SIZE";
        case CL_INVALID_KERNEL_ARGS:
            return (char*)"CL_INVALID_KERNEL_ARGS";
        case CL_INVALID_WORK_DIMENSION:
            return (char*)"CL_INVALID_WORK_DIMENSION";
        case CL_INVALID_WORK_GROUP_SIZE:
            return (char*)"CL_INVALID_WORK_GROUP_SIZE";
        case CL_INVALID_WORK_ITEM_SIZE:
            return (char*)"CL_INVALID_WORK_ITEM_SIZE";
        case CL_INVALID_GLOBAL_OFFSET:
            return (char*)"CL_INVALID_GLOBAL_OFFSET";
        case CL_INVALID_EVENT_WAIT_LIST:
            return (char*)"CL_INVALID_EVENT_WAIT_LIST";
        case CL_INVALID_EVENT:
            return (char*)"CL_INVALID_EVENT";
        case CL_INVALID_OPERATION:
            return (char*)"CL_INVALID_OPERATION";
        case CL_INVALID_GL_OBJECT:
            return (char*)"CL_INVALID_GL_OBJECT";
        case CL_INVALID_BUFFER_SIZE:
            return (char*)"CL_INVALID_BUFFER_SIZE";
        case CL_INVALID_MIP_LEVEL:
            return (char*)"CL_INVALID_MIP_LEVEL";
        case CL_INVALID_GLOBAL_WORK_SIZE:
            return (char*)"CL_INVALID_GLOBAL_WORK_SIZE";
        case CL_INVALID_PROPERTY:
            return (char*)"CL_INVALID_PROPERTY";

        default:
            return (char*)"UNKNOWN ERROR";
    }
}


