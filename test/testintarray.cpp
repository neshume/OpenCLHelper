#include <iostream>
#include <cstdlib>
using namespace std;

#include "gtest/gtest.h"

#include "OpenCLHelper.h"
#include "CLKernel.h"

#include "test/asserts.h"

TEST( testintarray, main ) {
    if( !OpenCLHelper::isOpenCLAvailable() ) {
        cout << "opencl library not found" << endl;
        exit(-1);
    }
    cout << "found opencl library" << endl;

    OpenCLHelper *cl = OpenCLHelper::createForFirstGpuOtherwiseCpu();
    CLKernel *kernel = cl->buildKernel("testintarray.cl", "test");
    int in[5];
    int inout[5];
    int out[5];
    for( int i = 0; i < 5; i++ ) {
        in[i] = i * 3;
        inout[i] = i * 3;
    }
    kernel->input( 5, in );
    kernel->output( 5, out );
    kernel->inout( 5, inout );
    size_t global = 5;
    size_t local = 5;
    kernel->run( 1, &global, &local );

    for( int i = 0; i < 5; i++ ) {
        cout << out[i] << " ";
    }
    cout << endl;
    for( int i = 0; i < 5; i++ ) {
        cout << inout[i] << " ";
    }
    cout << endl;

    assertEquals( inout[0], 7 );
    assertEquals( inout[1] , 10 );
    assertEquals( inout[2] , 34 );
    assertEquals( inout[3] , 16 );
    assertEquals( inout[4], 19 );
    assertEquals( out[0] , 5 );
    assertEquals( out[1] , 8 );
    assertEquals( out[2] , 26 );
    assertEquals( out[3] , 14 );
    assertEquals( out[4] , 17 );
    cout << "tests completed ok" << endl;

    delete kernel;
    delete cl;
}

