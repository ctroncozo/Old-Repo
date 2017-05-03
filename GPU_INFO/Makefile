# @author: Cristian Troncoso

ifndef CC
	CC = gcc
endif

CCFLAGS=-std=c99 -g -Wall

LIBS = -lOpenCL

INCLUDE = ./include

LDFLAGS= -shared

# Check our platform and make sure we define the APPLE variable
# and set up the right compiler flags and libraries
PLATFORM = $(shell uname -s)
ifeq ($(PLATFORM), Darwin)
	LIBS = -framework OpenCL
endif

EXE=DeviceInfo
LIB=libdeviceinfo.so
TEST=test

all: $(EXE)
lib: $(LIB)
test:$(TEST)

$(TEST): ./src/opencl_test.c
	$(CC) $^ $(CCFLAGS) -L./ libdeviceinfo.so $(LIBS) -I $(INCLUDE) -o $(TEST)

$(EXE) : ./src/opencl_test.c ./src/opencl_init.c
	$(CC) $^ $(CCFLAGS) $(LIBS) -I $(INCLUDE) -o $@

$(LIB) : ./src/opencl_init.c
	$(CC) $^ $(CCFLAGS) $(LIBS) -I $(INCLUDE) -o $@ $(LDFLAGS)

clean:
	rm -f DeviceInfo test
