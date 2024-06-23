#OBJS specifies which files to compile as part of the project
OBJS = SDL_tutorial.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -Wall show all warnings
COMPILER_FLAGS = -Wall 

DEBUG_FLAGS = -g

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = ./build/SDL_tutorial 

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
db : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(DEBUG_FLAGS) -o $(OBJ_NAME)  
run : 
	$(OBJ_NAME)
rundb :
	gdb $(OBJ_NAME)
clean : 
	rm ./build/*
