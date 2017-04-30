# Project   : OpenCl Histogram
# Author    : Cristian Troncoso 


CC=gcc
CFLAGS= -g3 -std=c99 -Wall
INCLUDE=-I/Users/Camel/Desktop/Portfolio/GPU_PORTFOLIO/COMMON/include/ \
				-I/Users/Camel/Desktop/Portfolio/GPU_PORTFOLIO/GPU_INFO/include/ 

# Linux (default)
if [[ "$OSTYPE" == "linux-gnu" ]]
   LIBS = -lGL -lGLU -lglut

# Windows (cygwin)
elif [[ "$OSTYPE" == "win32" ]]
   LIBS = -lopengl32 -lglu32 -lglut32

# OS X
elif [[ "$OSTYPE" == "darwin"* ]]
   LIBS=-framework Carbon  -framework OpenGL -framework GLUT -framework OpenCL

GPUEXE = HistGpu
CPUEXE = HistCpu

gpu: $(GPUEXE)
cpu: $(CPUEXE)

$(GPUEXE):./histogram_gpu.c ./bitmap.c ./opencl_init.c
	$(CC) $^ $(CCFLAGS) $(LIBS) -I $(INCLUDE) -o $@

$(CPUEXE):./histogram_cpu.c ./bitmap.c
	$(CC) $^ $(CCFLAGS) $(LIBS) -I $(INCLUDE) -o $@

clean:
	rm -f HistGpu HistCpu 

