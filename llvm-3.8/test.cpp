extern void test() ;

extern "C" void exec(void*) {
    test();
}
