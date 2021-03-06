// Copyright Hugh Perkins 2013, 2014 hughperkins at gmail
//
// This Source Code Form is subject to the terms of the Mozilla Public License, 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include <cstdlib>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdexcept>

#include "clew.h"
#include "deviceinfo_helper.h"
#include "platforminfo_helper.h"

#include "deprecated.h"

#include "OpenCLHelper_export.h"

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

class CLKernel;
class CLArrayFloat;
class CLArrayInt;
class CLIntWrapper;
class CLFloatWrapper;
class CLFloatWrapperConst;

class OpenCLHelper_EXPORT OpenCLHelper {
public:
     cl_int error;  // easier than constantly declaring it in each method...

//    cl_device_id *device_ids;

//    cl_uint num_platforms;
//    cl_uint num_devices;

    cl_platform_id platform_id;
    cl_device_id device;

    cl_context *context;
    cl_command_queue *queue;
//    cl_program *program;

//    int gpuIndex;

    template<typename T>
    static std::string toString(T val ) {
       std::ostringstream myostringstream;
       myostringstream << val;
       return myostringstream.str();
    }

    OpenCLHelper(int gpu );
    OpenCLHelper();
    OpenCLHelper( cl_platform_id platformId, cl_device_id deviceId );
    ~OpenCLHelper();

    static bool isOpenCLAvailable();
    static int roundUp( int quantization, int minimum );
    // accidentally created 2 funcftions that do the same thing :-P  but wont remove either,
    // in case someone's using that one
    static int getNextPower2( int value ); // eg pass in 320, it will return: 512
    static int getPower2Upperbound( int value );
    static OpenCLHelper *createForFirstGpu();
    static OpenCLHelper *createForFirstGpuOtherwiseCpu();
    static OpenCLHelper *createForIndexedGpu( int gpu );
    static OpenCLHelper *createForPlatformDeviceIndexes(int platformIndex, int deviceIndex);
    static OpenCLHelper *createForPlatformDeviceIds(cl_platform_id platformId, cl_device_id deviceId);
    static std::string errorMessage(cl_int error );
    static void checkError( cl_int error );

    void gpu( int gpuIndex );
    void init(int gpuIndex );
    void finish();

    int getComputeUnits();
    int getLocalMemorySize();
    int getMaxWorkgroupSize();

    CLArrayFloat *arrayFloat(int N );
    CLArrayInt *arrayInt(int N );
    CLIntWrapper *wrap(int N, int *source );
    CLFloatWrapper *wrap(int N, float *source );
    CLFloatWrapperConst *wrap(int N, float const*source );
    CLKernel *buildKernel( std::string kernelfilepath, std::string kernelname );
    CLKernel *buildKernel( std::string kernelfilepath, std::string kernelname, std::string options );
    CLKernel *buildKernelFromString( std::string source, std::string kernelname, std::string options, std::string sourcefilename = "" );

private:
    static std::string getFileContents( std::string filename );
    long getDeviceInfoInt( cl_device_info name );
};

#include "CLIntWrapper.h"
#include "CLFloatWrapper.h"
#include "CLFloatWrapperConst.h"
#include "CLWrapper.h"
#include "CLKernel.h"


