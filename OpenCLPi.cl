
/////////////////////////////////////////////////////////////////////////////
struct Rnd4Lin {
    ulong a,b,c,d,e;
    uint  s1,s2,s3,s4,s5;
};
uint perm( const ulong a, const ulong b, const ulong c) {
    return (uint) ( (a >> (64-11)) | ((b >> (64-11)) << 11) | ((c >> (64-10))<<22) );
}
bool test( uint *const s , const uint max) {
    if( (*s)++ < max ) {
        return false;
    }
    *s = 0;
    return true;
}
void nextV( ulong *const v, const ulong A, const ulong B ) {
    *v = *v * A + B;
}
void next( ulong *const v, uint *const s, const uint max, const ulong A, const ulong B ) {
    nextV( v , A , B );
    if( test( s , max ) ) {
        nextV( v , A , B );
    }
}
void seed( struct Rnd4Lin *const r, const ulong __sd ) {
    r->a = __sd ^ (ulong)0x140CA25429E95B21;
    r->b = __sd ^ (ulong)0x4A37D2E9E5D5C6A3;
    r->c = __sd ^ (ulong)0xD76C0A509DACE77D;
    r->d = __sd ^ (ulong)0x2C5A00D35721B705;
    r->e = __sd ^ (ulong)0x944AC881D66E20A3;
    r->s1 = r->s2 = r->s3 = r->s4 = r->s5 = 0;
}
uint getRnd(struct Rnd4Lin *const r) {
    next( &r->a , &r->s1 ,  6 , (ulong)195366727,  (ulong)3788059271 );
    next( &r->b , &r->s2 , 10 , (ulong)201733549,  (ulong)6004841807 );
    next( &r->c , &r->s3 , 12 ,  (ulong)87604849, (ulong)11409409549 );
    next( &r->d , &r->s4 , 16 , (ulong)219699203, (ulong)16379749871 );
    next( &r->e , &r->s5 , 18 , (ulong)186217943, (ulong)36457959557 );
    switch( r->a >> 61 ) {
        case 0:  return perm(r->b,r->c,r->d) ^ (uint)(r->e>>31);
        case 1:  return perm(r->b,r->c,r->d) ^ (uint)(r->e>>32);
        case 2:  return perm(r->b,r->d,r->c) ^ (uint)(r->e>>31);
        case 3:  return perm(r->b,r->d,r->c) ^ (uint)(r->e>>32);
        case 4:  return perm(r->c,r->b,r->d) ^ (uint)(r->e>>32);
        case 5:  return perm(r->c,r->d,r->b) ^ (uint)(r->e>>32);
        case 6:  return perm(r->d,r->b,r->c) ^ (uint)(r->e>>32);
        default: return perm(r->d,r->c,r->b) ^ (uint)(r->e>>32);
    }

}
/////////////////////////////////////////////////////////////////////////////

struct Worker {
    ulong seed;
    ulong count;
};

__kernel void OpenCLPi(__global struct Worker const* workers, const ulong n_loops) {
    struct Worker *const worker = workers + get_global_id(0);
    struct Rnd4Lin rnd;
    seed( &rnd, worker->seed );
    ulong count = 0;
    for( ulong i=0 ; i<n_loops ; i++ ) {
        count += getRnd( &rnd ) & 0xFF;
    }
    worker->count = count;
}
