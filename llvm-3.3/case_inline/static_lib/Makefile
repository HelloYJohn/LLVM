static_library:
	g++ -O3 -g -c static_library.cpp -o static_library.o
	ar -crv libstatic_library.a static_library.o
test:test_llvm.cpp
	g++ -O3 -std=c++11 -g test_llvm.cpp -D __STDC_LIMIT_MACROS -D __STDC_CONSTANT_MACROS `llvm-config --cxxflags --ldflags --libs` -L. -lstatic_library -o $@

testinline:test_llvm.cpp
	g++ -O3 -std=c++11 -g test_llvminline.cpp -D __STDC_LIMIT_MACROS -D __STDC_CONSTANT_MACROS `llvm-config --cxxflags --ldflags --libs` -L. -lstatic_library -o $@
.PHONY:clean
clean:
	rm -fr test testinline *.a *.o *.ll *.S 

