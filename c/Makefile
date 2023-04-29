SRC		:= main/main.c math_lib/main.c math_lib/vectormath.c
OBJ_DIR	:= OBJECT_FILES
OBJ		:= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))
I_SDL	:= -I$(shell brew --prefix)/include
L_SDL	:= -L$(shell brew --prefix sdl2)/lib
NAME	:= App
cc		:= gcc

all: $(NAME) 

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	@echo "$< Created."
	@$(cc) $(CFLAGS) $(I_SDL) -c $< -o $@

$(NAME) : $(OBJ)
	@echo "$(NAME) Created."
	@$(cc) $(CFLAGS) $(I_SDL) $(L_SDL) -lSDL2 $(OBJ) -o $(NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: clean fclean $(NAME)

.PHONY: clean fclean
