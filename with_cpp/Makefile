NAME			:= RayTracer
LIB				:= -lSDL2
OBJ_DIR			:= OBJECT_FILES
CFLAGS			:= -std=c++17 -Ofast -g
CC				:= g++
SRC_FILES		:= $(wildcard *.cpp) $(wildcard **/*.cpp)
OBJECTS_FILES	:= $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))


$(OBJ_DIR)/%.o : %.cpp
	@ echo "compiling cpp file $< ..."
	@ mkdir -p $(dir $@)
	@ ${CC} $(CFLAGS) -c $< -o $@ 

all: $(NAME)


$(NAME) : $(OBJECTS_FILES)
	@echo "Creating $@"
	@$(CC) $(CFLAGS) $(OBJECTS_FILES) -o $@ ${LIB}

clean :
	rm $(OBJECTS_FILES)

fclean : clean
	rm $(NAME)

re: fclean all

.PHONY : clean fclean
