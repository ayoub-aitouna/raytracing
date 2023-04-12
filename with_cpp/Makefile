NAME			:= App
LIB				:= -lSDL2
OBJ_DIR			:= OBJECT_FILES
CFLAGS			:= -std=c++17 -Ofast -g
CC				:= g++
SRC_FILES		:= $(wildcard *.cpp) $(wildcard **/*.cpp)
OBJECTS_FILES	:= $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
LIB_SDL			:= #-L $(shell brew --prefix sdl2)/lib
INCLUDES		:= #-I $(shell brew --prefix)/include
Math_lib		:=	qbLinAlg 
	
all: $(NAME)

$(Math_lib) :
	@git clone https://github.com/QuantitativeBytes/qbLinAlg.git

$(OBJ_DIR)/%.o : %.cpp
	@ echo "compiling cpp file $< ..."
	@ mkdir -p $(dir $@)
	@ ${CC} $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME) : $(Math_lib) $(OBJECTS_FILES)
	@echo "Creating $@"
	@$(CC) $(CFLAGS) $(OBJECTS_FILES) -o $@ $(INCLUDES) ${LIB_SDL} ${LIB} 

clean :
	@rm -rf $(OBJECTS_FILES)

fclean : clean
	@rm -rf $(NAME)

re: fclean all

.PHONY : clean fclean
