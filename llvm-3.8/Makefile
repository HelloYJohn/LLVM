INCLUDE_DIRECTORIES=-I /usr/include/llvm-c-3.8/ \
					-I /usr/include/llvm-3.8/
SRC_FILE=run_link_module.cpp
LINK=`llvm-config-3.8 --cxxflags --ldflags --libs` -fexceptions -lpthread -lz -ldl -lncurses
DEFINED=-D __STDC_LIMIT_MACROS -D __STDC_CONSTANT_MACROS
run_parser:test.cpp run_link_module.cpp 
	clang++  -c -emit-llvm -o test.ll test.cpp
	g++ -std=c++11  $(INCLUDE_DIRECTORIES) $(SRC_FILE) $(LINK) $(DEFINED) -o $@  -g

.PHONY:clean
clean:
	rm run_parser test.ll
