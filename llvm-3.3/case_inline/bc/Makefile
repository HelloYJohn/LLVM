static_library:
	clang -emit-llvm -c static_library.cpp -o static_library.bc
test:test_llvm.cpp
	g++ -g test_llvm.cpp -D __STDC_LIMIT_MACROS -D __STDC_CONSTANT_MACROS `llvm-config --cxxflags --ldflags --libs` -o $@
testinline:test_llvm_inline.cpp
	g++ -O3 -g test_llvm_inline.cpp -D __STDC_LIMIT_MACROS -D __STDC_CONSTANT_MACROS `llvm-config --cxxflags --ldflags --libs` -o $@

.PHONY:clean
clean:
	rm -fr test  testinline *.a *.o *.ll *.S *.bc

