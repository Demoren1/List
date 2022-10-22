all : mkdir list
SRC_DIR = ./src/
OBJ_DIR = ./obj/
CC = g++

# RELEASE_FLAGS := -DNDEBUG
# release:
# 	g++ $(RELEASE_FLAGS)

CFLAGS= -save-temps -Wall -Wextra -fsanitize=address -g #-D _DEBUG -ggdb3 -std=c++20 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations \
-Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported \
-Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op \
-Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo \
-Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default \
-Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing \
-Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-check -fstack-protector -fstrict-overflow -flto-odr-type-merging \
-fno-omit-frame-pointer -fPIE -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr \
-pie -Wlarger-than=8192 -Wstack-usage=8192

##include paths
INCLUDE_PATH = -I./include/

#sources
LIST_SRC := $(SRC_DIR)list.cpp $(SRC_DIR)list_func.cpp $(SRC_DIR)list_dump.cpp
LIST_OBJ := $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(LIST_SRC)) 

#exe
LIST_EXE := list

$(LIST_EXE) : $(LIST_OBJ) 
	$(CC) $(CFLAGS) $(INCLUDE_PATH) $(LIST_OBJ) -o $(LIST_EXE)

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp 
	$(CC) $(INCLUDE_PATH) -c $< -o $@

mkdir :
	@mkdir $(OBJ_DIR) -p

clean:
	rm $(OBJ_DIR)*.o $(OBJ_DIR)*.ii $(OBJ_DIR)*.s *.save list