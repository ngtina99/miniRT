NAME = miniRT

SRCS	= $(addprefix srcs/,$(addsuffix .c, $(FILES)))
FILES	= init/main parsing/parser

OBJS		= $(addprefix $(OBJS_DIR)/,$(SRCS:srcs/%.c=%.o))
OBJS_DIR	= objs

INCLUDES =	includes/
MLX_FLAGS =	-Lmlx_linux -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

CC = cc
RM = rm -f

CPPFLAGS = -Wall -Wextra -Werror -I -O3

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CPPFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re