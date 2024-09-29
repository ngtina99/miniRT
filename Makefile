NAME		= miniRT

SRC			= ./srcs/init/main.c

CC			= cc 
RM			= rm -f

OBJ				= $(SRC:.c=.o)
LIBFT 			= ./libft/libft.a

INC    			= -I./includes

CFLAGS			= -Wall -Wextra -Werror -g

MLXFLAGS		= -O3 -Lminilibx-linux/ -lmlx -L/usr/lib -Ilmlx -lXext -lX11 -lm -lz

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
	$(MAKE) -C ./libft

$(NAME):	$(LIBFT) $(OBJ)
	@echo $(BLUE) "*Compiling miniRT*" $(EOC) $(GREEN) 
	$(CC) $(SRC) $(INC) $(MLXFLAGS) $(LIBFT) $(CFLAGS) -o $(NAME)

$(OBJ): ./includes/minirt.h

clean:
	@echo $(PURPLE) "🧽🧼" $(EOC)
	$(MAKE) -C ./libft clean
	$(RM) $(OBJ)
	@echo $(PURPLE) "✨Clean✨" $(EOC)

fclean:		clean
	@echo $(PURPLE) "🛁🧴" $(EOC)
	$(RM) $(NAME)
	$(MAKE) -C ./libft fclean
	@echo $(PURPLE) "✨FClean✨" $(EOC)

re:	fclean all

# //ARGS		= Mandelbrot
# gdb:	all
# 		gdb --args $(NAME) $(ARGS)
# valgrind: 	all
# 			valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(ARGS)

.PHONY:		all clean fclean re