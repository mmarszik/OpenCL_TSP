#include <unistd.h>
#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>

//#define CL_USE_DEPRECATED_OPENCL_2_0_APIS
#include <CL/cl.hpp>

using utyp32 = unsigned int;
using ityp32 = int;
using utyp64 = unsigned long long;

using cutyp32 = const utyp32;
using cityp32 = const ityp32;
using cutyp64 = const utyp64;

static cl::Program createClProgram(const std::string &pathToSrc, const char *const verbosity) {
    std::vector< cl::Platform > platforms;
    cl_int success = cl::Platform::get( &platforms );
    assert( CL_SUCCESS ==  success );
    assert( platforms.size() > 0 );
    if( strcasecmp(verbosity,"verbosity") == 0 ) {
        for( size_t i=0 ; i<platforms.size() ; i++ ) {
            std::string buf;
            std::cout << "Platform " << (i+1) << "] " << std::endl;
            platforms[i].getInfo( CL_PLATFORM_PROFILE , &buf );
            std::cout << "  --profile: " << buf << std::endl;
            platforms[i].getInfo(  CL_PLATFORM_VERSION , &buf );
            std::cout << "  --version: " << buf << std::endl;
            platforms[i].getInfo(  CL_PLATFORM_NAME , &buf );
            std::cout << "  --name: " << buf << std::endl;
            platforms[i].getInfo(  CL_PLATFORM_VENDOR , &buf );
            std::cout << "  --vendor: " << buf << std::endl;
            platforms[i].getInfo(  CL_PLATFORM_EXTENSIONS , &buf );
            std::cout << "  --extensions: " << buf << std::endl;
        }
    }
    auto platform = platforms.front();

    std::vector<cl::Device> devices;
    success = platform.getDevices(CL_DEVICE_TYPE_ALL,&devices);
    assert( CL_SUCCESS ==  success );
    assert( devices.size() > 0 );

    if( strcasecmp(verbosity,"verbosity") == 0 ) {
        for( size_t i=0 ; i<devices.size() ; i++ ) {
            std::string sBuf;
            int iBuf;

            std::cout << "Device " << (i+1) << "] " << std::endl;
            devices[i].getInfo( CL_DEVICE_ADDRESS_BITS , &iBuf );
            std::cout << "  --address bits: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_AVAILABLE , &iBuf );
            std::cout << "  --available: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_COMPILER_AVAILABLE , &iBuf );
            std::cout << "  --compiler available: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_ENDIAN_LITTLE , &iBuf );
            std::cout << "  --endian little: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_ERROR_CORRECTION_SUPPORT , &iBuf );
            std::cout << "  --error correcton support: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_EXECUTION_CAPABILITIES , &iBuf );
            std::cout << "  --execution capabilities: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_EXTENSIONS , &sBuf );
            std::cout << "  --extensions: " << sBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_GLOBAL_MEM_CACHE_SIZE , &iBuf );
            std::cout << "  --global mem cache size: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_GLOBAL_MEM_CACHE_TYPE , &iBuf );
            std::cout << "  --global mem cache type: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE , &iBuf );
            std::cout << "  --global mem cacheline size: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_GLOBAL_MEM_SIZE , &iBuf );
            std::cout << "  --global mem size: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_IMAGE_SUPPORT , &iBuf );
            std::cout << "  --image support: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_IMAGE2D_MAX_HEIGHT , &iBuf );
            std::cout << "  --image2d max height: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_IMAGE2D_MAX_WIDTH , &iBuf );
            std::cout << "  --image2d max width: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_IMAGE3D_MAX_DEPTH , &iBuf );
            std::cout << "  --image3d max depth: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_IMAGE3D_MAX_HEIGHT , &iBuf );
            std::cout << "  --image3d max height: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_IMAGE3D_MAX_WIDTH , &iBuf );
            std::cout << "  --image3d max width: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_LOCAL_MEM_SIZE , &iBuf );
            std::cout << "  --local mem size: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_LOCAL_MEM_TYPE , &iBuf );
            std::cout << "  --local mem type: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_MAX_CLOCK_FREQUENCY , &iBuf );
            std::cout << "  --max clock frequency: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_MAX_COMPUTE_UNITS , &iBuf );
            std::cout << "  --max compute units: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_MAX_CONSTANT_ARGS , &iBuf );
            std::cout << "  --max constant args: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE , &iBuf );
            std::cout << "  --max constant buffer size: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_MAX_MEM_ALLOC_SIZE , &iBuf );
            std::cout << "  --max mem alloc size: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_MAX_PARAMETER_SIZE , &iBuf );
            std::cout << "  --max parameter size: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_MAX_READ_IMAGE_ARGS , &iBuf );
            std::cout << "  --max read image args: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_MAX_SAMPLERS , &iBuf );
            std::cout << "  --max samplers: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_MAX_WORK_GROUP_SIZE , &iBuf );
            std::cout << "  --CL_DEVICE_MAX_WORK_GROUP_SIZE: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS , &iBuf );
            std::cout << "  --CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_MAX_WORK_ITEM_SIZES , &iBuf );
            std::cout << "  --CL_DEVICE_MAX_WORK_ITEM_SIZES: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_MAX_WRITE_IMAGE_ARGS , &iBuf );
            std::cout << "  --CL_DEVICE_MAX_WRITE_IMAGE_ARGS: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_MEM_BASE_ADDR_ALIGN , &iBuf );
            std::cout << "  --CL_DEVICE_MEM_BASE_ADDR_ALIGN: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE , &iBuf );
            std::cout << "  --CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_NAME , &iBuf );
            std::cout << "  --CL_DEVICE_NAME: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_PLATFORM , &iBuf );
            std::cout << "  --CL_DEVICE_PLATFORM: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR , &iBuf );
            std::cout << "  --CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE , &iBuf );
            std::cout << "  --CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT , &iBuf );
            std::cout << "  --CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT , &iBuf );
            std::cout << "  --CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG , &iBuf );
            std::cout << "  --CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT , &iBuf );
            std::cout << "  --CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_PROFILE , &iBuf );
            std::cout << "  --CL_DEVICE_PROFILE: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_PROFILING_TIMER_RESOLUTION , &iBuf );
            std::cout << "  --CL_DEVICE_PROFILING_TIMER_RESOLUTION: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_QUEUE_PROPERTIES , &iBuf );
            std::cout << "  --CL_DEVICE_QUEUE_PROPERTIES: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_SINGLE_FP_CONFIG , &iBuf );
            std::cout << "  --CL_DEVICE_SINGLE_FP_CONFIG: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_TYPE , &iBuf );
            std::cout << "  --CL_DEVICE_TYPE: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_VENDOR_ID , &iBuf );
            std::cout << "  --CL_DEVICE_VENDOR_ID: " << iBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_VENDOR , &sBuf );
            std::cout << "  --CL_DEVICE_VENDOR: " << sBuf << std::endl;
            devices[i].getInfo( CL_DEVICE_VERSION , &sBuf );
            std::cout << "  --CL_DEVICE_VERSION: " << sBuf << std::endl;
            devices[i].getInfo( CL_DRIVER_VERSION , &sBuf );
            std::cout << "  --CL_DRIVER_VERSION: " << sBuf << std::endl;
        }
    }

    auto device = devices.front();

    std::ifstream file(pathToSrc);
    std::string src( std::istreambuf_iterator<char>(file) , (std::istreambuf_iterator<char>()) );
    cl::Program::Sources sources = { std::pair<const char*, ::size_t>(src.c_str(), src.length()+1 ) };
    cl::Context context(device);
    cl::Program program(context,sources);
    success = program.build("-cl-std=CL2.0");
    assert( CL_SUCCESS ==  success );
    return program;
}

class Rnd4Lin {
private:
    utyp64 a,b,c,d,e;
    utyp32 s1,s2,s3,s4,s5;
private:
    static utyp32 perm( cutyp64 a, cutyp64 b, cutyp64 c) {
        return (utyp32) ( (a >> (64-11)) | ((b >> (64-11)) << 11) | ((c >> (64-10))<<22) );
    }
    static bool test( utyp32 &s , cutyp32 max) {
        if( s++ < max ) {
            return false;
        }
        s = 0;
        return true;
    }
    static void next( utyp64 &v, cutyp64 A, cutyp64 B ) {
        v = v * A + B;
    }
    static void next( utyp64 &v, utyp32 &s, cutyp32 max, cutyp64 A, cutyp64 B ) {
        next( v , A , B );
        if( test( s , max ) ) {
            next( v , A , B );
        }
    }
public:
    Rnd4Lin( cutyp64 __sd=1) {
        seed( __sd );
    }
    void seed( cutyp64 __sd ) {
        a = __sd ^ 0x140CA25429E95B21ull;
        b = __sd ^ 0x4A37D2E9E5D5C6A3ull;
        c = __sd ^ 0xD76C0A509DACE77Dull;
        d = __sd ^ 0x2C5A00D35721B705ull;
        e = __sd ^ 0x944AC881D66E20A3ull;
        s1 = s2 = s3 = s4 = s5 = 0;
    }
    utyp32 operator ()() {
        next( a , s1 ,  6 , 195366727ull,  3788059271ull );
        next( b , s2 , 10 , 201733549ull,  6004841807ull );
        next( c , s3 , 12 ,  87604849ull, 11409409549ull );
        next( d , s4 , 16 , 219699203ull, 16379749871ull );
        next( e , s5 , 18 , 186217943ull, 36457959557ull );
        switch( a >> 61 ) {
            case 0:  return perm(b,c,d) ^ (e>>31);
            case 1:  return perm(b,c,d) ^ (e>>32);
            case 2:  return perm(b,d,c) ^ (e>>31);
            case 3:  return perm(b,d,c) ^ (e>>32);
            case 4:  return perm(c,b,d) ^ (e>>32);
            case 5:  return perm(c,d,b) ^ (e>>32);
            case 6:  return perm(d,b,c) ^ (e>>32);
            default: return perm(d,c,b) ^ (e>>32);
        }
    }
};



struct Worker {
    utyp64 seed;
    utyp64 count;
};

int main(int argc, char *argv[]) {
    if( argc != 6 ) {
        std::cout << "Using OpenCL_PI verbosity|not OpenCL|OpenMP|rndTest seed workers loops" << std::endl;
        abort();
    }

    cutyp64 seed = atoi(argv[3]);
    Rnd4Lin rnd( seed );
    cutyp32 n_workers = atoi(argv[4]);
    cutyp64 n_loops = atoi(argv[5]);

    std::vector<Worker> workers(n_workers);
    cutyp32 MEMSIZE = n_workers * sizeof(Worker);

    for( utyp32 i=0 ; i<workers.size() ; i++ ) {
        rnd();rnd();rnd();rnd();rnd();
        workers[i].seed = rnd();
        workers[i].seed <<= 32;
        rnd();rnd();rnd();rnd();
        workers[i].seed |= rnd();
    }

    if( strcasecmp( argv[2] , "opencl") == 0 ) {
        cl_int success;

        cl::Program program = createClProgram("OpenCLPi.cl",argv[1]);
        auto context = program.getInfo<CL_PROGRAM_CONTEXT>();
        auto devices = program.getInfo<CL_PROGRAM_DEVICES>();
        auto device = devices.front();

        cl::Buffer memBuf(context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR , MEMSIZE , workers.data() , &success );
        assert( success == CL_SUCCESS );

        cl::Kernel kernel( program , "OpenCLPi");
        success = kernel.setArg(0,memBuf);
        assert( success == CL_SUCCESS );
        success = kernel.setArg(1,n_loops);
        assert( success == CL_SUCCESS );

        cl::CommandQueue queue( context , device );
        success = queue.enqueueNDRangeKernel( kernel, cl::NullRange, cl::NDRange(workers.size()) );
        assert( success == CL_SUCCESS );
        success = queue.enqueueReadBuffer( memBuf, CL_TRUE, 0 , MEMSIZE, workers.data() );
        assert( success == CL_SUCCESS );

        cl::finish();

    } else if( strcasecmp( argv[2] , "openmp") == 0 ) {
        #pragma omp parallel for
        for( utyp32 i=0 ; i<workers.size() ; i++ ) {
            Rnd4Lin rnd( workers[i].seed );
            workers[i].count = 0;
            for( utyp64 j=0 ; j<n_loops ; j++ ) {
                workers[i].count += rnd() & 0xFF;
            }
        }
    } else if( strcasecmp( argv[2] , "rndtest") == 0 ) {
        constexpr utyp32 BUFFSIZE = 4096;
        utyp32 buff[BUFFSIZE];
        while( true ) {
            for( utyp32 i=0 ; i<BUFFSIZE ; i++ ) {
                buff[i] = rnd();
            }
            fwrite( buff , sizeof(buff) , 1 , stdout );
        }
    } else {
        std::cout << "Invalid compute model" << std::endl;
        abort();
    }

    utyp64 sum = 0;
    for( utyp32 i=0 ; i<workers.size() ; i++ ) {
        sum += workers[i].count;
    }

    std::cout << "sum: " << sum << std::endl;
    std::cout << "pi: " << (long double)sum / workers.size() / n_loops << std::endl;

    return 0;
}
