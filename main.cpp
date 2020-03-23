#include <unistd.h>
#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <string>

//#define CL_USE_DEPRECATED_OPENCL_2_0_APIS
#include <CL/cl.hpp>


using utyp32 = unsigned int;
using ityp32 = int;
using utyp64 = unsigned long long;

using cutyp32 = const utyp32;
using cityp32 = const ityp32;
using cutyp64 = const utyp64;

using dtyp = utyp32;

class LRnd {
private:
    utyp64 a,b,c,s1,s2,s3;
public:
    LRnd( cutyp64 __sd) {
        seed( __sd );
    }
    void seed( cutyp64 __sd ) {
        a = __sd;
        b = __sd ^ 0x4A37D2E9E5D5C6Aull;
        c = __sd ^ 0xD76C0A50DACE77Dull;
        s1 = s2 = s3 = 1;
    }
    utyp32 operator ()() {
        a = a * 195366727ull + 3788059271ull;
        if( s1++ == 2 ) {
            a = a * 195366727ull + 3788059271ull;
            s1 = 0;
        }
        b = b * 201733549ull + 6004841807ull;
        if( s2++ == 4 ) {
            b = b * 201733549ull + 6004841807ull;
            s2 = 0;
        }
        c = c * 87604849ull + 11409409549ull;
        if( s3++ == 6 ) {
            c = c * 87604849ull + 11409409549ull;
            s3 = 0;
        }
        return (utyp32) ( (a >> (64-11)) | ((b >> (64-11)) << 11) | ((c >> (64-10))<<22) );
    }
};

void initLRnd( LRnd &rnd , ) {

}

struct TSPItem {

};





int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
