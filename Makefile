NAME		= miniRT

SRC	= $(addprefix srcs/,$(addsuffix .c, $(FILES)))
FILES		= main init/init parsing/parser

CC			= cc 
RM			= rm -f

OBJ			= $(addprefix $(OBJ_DIR)/,$(SRC:srcs/%.c=%.o))
OBJ_DIR		= objs

LIBFT 			= ./libs/libft/libft.a
INC    			= -I./includes

#CFLAGS			= -Wall -Wextra -Werror -g
MLXFLAGS		= -O3 -L libs/minilibx-linux/ -lmlx -L/usr/lib -Ilmlx -lXext -lX11 -lm -lz -lpthread #lpthread maybe we can

WHITE="\033[1m"
PURPLE:="\033[1;35m"
PINK="\033[95m"
RED="\033[1;91m"
GREEN:="\033[1;32m"
BLUE:="\033[1;36m"
ORANGE="\033[1;38;5;208m"
YELLOW="\033[1;33m"
EOC:="\033[0;0m" #END OF COLOR

all:		$(NAME)
			@echo
			@echo $(PINK) "*KEYBOARD INSTRUCTIONS*" $(EOC) $(RED)
			@echo
			@echo $(PURPLE)
			@echo "✨The program is ready✨" $(EOC)

# @echo "maybe instruct put cylinder" $(EOC) $(GREEN)
# @echo "maybe instruct put cube" $(EOC) $(BLUE)
# @echo "maybe instruct put cylinder etc" $(EOC) $(WHITE)
# @echo "etc" $(EOC) $(YELLOW)
# @echo "Z, X, I, O: changing image sharpness" $(EOC) $(ORANGE)
# @echo "W, A, S, D: changing Julia set" $(EOC) $(PINK)

$(LIBFT):
	$(MAKE) -C ./libs/libft

$(OBJ): ./includes/minirt.h

$(OBJ_DIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJ)
	@echo $(BLUE) "*Compiling miniRT*" $(EOC) $(GREEN) 
	$(CC) $(SRC) $(INC) $(OPENGLFLAGS) $(MLXFLAGS) $(LIBFT) $(CFLAGS) -o $(NAME)

clean:
	@echo $(PURPLE) "🧽🧼" $(EOC)
	$(MAKE) -C ./libs/libft clean
	$(RM) -r $(OBJ_DIR)
	@echo $(PURPLE) "✨Clean✨" $(EOC)

fclean:		clean
	@echo $(PURPLE) "🛁🧴" $(EOC)
	$(RM) $(NAME)
	$(MAKE) -C ./libs/libft fclean
	@echo $(PURPLE) "✨FClean✨" $(EOC)

re:	fclean all

# gdb:	all
# 		gdb --args $(NAME) $(ARGS)

valgrind: 	all
			valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

.PHONY:		all clean fclean re