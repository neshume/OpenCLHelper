#include <iostream>
#include <cstdlib>
// using namespace std;

#include "gtest/gtest.h"

#include "OpenCLHelper.h"

#include "test/asserts.h"

using namespace std;

TEST( testfloatwrapperconst, main ) {
    if( !OpenCLHelper::isOpenCLAvailable() ) {
        cout << "opencl library not found" << endl;
        exit(-1);
    }
    cout << "found opencl library" << endl;

    OpenCLHelper *cl = OpenCLHelper::createForFirstGpuOtherwiseCpu();
    CLKernel *kernel = cl->buildKernel("testopenclhelper.cl", "test");
    float in[5];
    for( int i = 0; i < 5; i++ ) {
        in[i] = i * 3;
    }
    float out[5];
    CLWrapper *inwrapper = cl->wrap(5, (float const *)in);
    CLWrapper *outwrapper = cl->wrap(5, out);
    inwrapper->copyToDevice();
    kernel->input( inwrapper );
    kernel->output( outwrapper );
    kernel->run_1d( 5, 5 );
    outwrapper->copyToHost();
    assertEquals( out[0] , 7 );
    assertEquals( out[1] , 10 );
    assertEquals( out[2] , 13 );
    assertEquals( out[3] , 16 );
    assertEquals( out[4] , 19 );
    cout << "tests completed ok" << endl;

    delete inwrapper;
    delete outwrapper;
    delete kernel;
    delete cl;
}

