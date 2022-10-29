all : mkdir list
SRC_LIST_DIR = ./src/list/
SRC_STACK_DIR = ./src/stack/src/
OBJ_DIR = ./obj/
CC = g++

# RELEASE_FLAGS := -DNDEBUG
# release:
# 	g++ $(RELEASE_FLAGS)

CFLAGS= -save-temps -Wall -Wextra -fsanitize=address -g -O0#-D _DEBUG -ggdb3 -std=c++20  -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations \
-Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported \
-Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op \
-Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo \
-Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default \
-Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing \
-Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-check -fstack-protector -fstrict-overflow -flto-odr-type-merging \
-fno-omit-frame-pointer -fPIE -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr \
-pie -Wlarger-than=8192 -Wstack-usage=8192

##include paths
INCLUDE_PATH = -I./include/ -I./src/stack/include

#sources
LIST_SRC := $(SRC_LIST_DIR)list.cpp $(SRC_LIST_DIR)list_func.cpp $(SRC_LIST_DIR)list_dump.cpp 
STACK_SRC := $(SRC_STACK_DIR)debug_funcs.cpp $(SRC_STACK_DIR)input_output.cpp $(SRC_STACK_DIR)stack_func.cpp 

#obj
LIST_OBJ  := $(patsubst $(SRC_LIST_DIR)%.cpp, $(OBJ_DIR)%.o, $(LIST_SRC)) 
STACK_OBJ := $(patsubst $(SRC_STACK_DIR)%.cpp, $(OBJ_DIR)%.o, $(STACK_SRC))

#exe
LIST_EXE := list

$(LIST_EXE) : $(LIST_OBJ) $(STACK_OBJ)
	@$(CC) $(CFLAGS) $(INCLUDE_PATH) $(LIST_OBJ) $(STACK_OBJ) -o $(LIST_EXE)

$(OBJ_DIR)%.o : $(SRC_LIST_DIR)%.cpp 
	@$(CC) $(INCLUDE_PATH) -c $< -o $@

$(OBJ_DIR)%.o : $(SRC_STACK_DIR)%.cpp
	@$(CC) $(INCLUDE_PATH) -c $< -o $@

mkdir :
	@mkdir $(OBJ_DIR) -p

clean:
	rm $(OBJ_DIR)*.o $(OBJ_DIR)*.ii $(OBJ_DIR)*.s *.save list