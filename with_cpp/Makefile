NAME			:= App
LIB				:= -lSDL2
OBJ_DIR			:= OBJECT_FILES
CFLAGS			:= -std=c++17 -Ofast -g
CC				:= g++
SRC_FILES		:= $(wildcard *.cpp) $(wildcard **/*.cpp) $(wildcard **/*.c) $(wildcard raytracer/objects/*.cpp) 
OBJECTS_FILES	:= $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
# LIB_SDL			:= -L$(shell brew --prefix sdl2)/lib
# INCLUDES		:= -I$(shell brew --prefix)/include 
Math_lib		:=	qbLinAlg 
	

all: $(NAME)

$(Math_lib) :
	@ git clone https://github.com/QuantitativeBytes/qbLinAlg.git

$(OBJ_DIR)/%.o : %.cpp
	@ echo "compiling cpp file $< ..."
	@ mkdir -p $(dir $@)
	@ ${CC} $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME) : $(Math_lib) $(OBJECTS_FILES)
	@echo "Creating $@"
	@$(CC) $(CFLAGS) $(OBJECTS_FILES) -o $@  ${LIB} 

clean :
	@ echo "deleting object OBJECTS_FILES"
	@ rm -rf $(OBJ_DIR)/*

fclean : clean
	@ echo "deleting $(NAME)"
	@ rm -rf $(NAME)

re: fclean all

.PHONY : clean fclean
