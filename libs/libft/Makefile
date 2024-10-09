# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/19 19:28:24 by yioffe            #+#    #+#              #
#    Updated: 2024/06/23 16:15:18 by yioffe           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	ft_bzero.c ft_isalnum.c ft_isalpha.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c \
		ft_memcpy.c ft_memmove.c ft_memset.c \
		ft_strdup.c ft_strcat.c ft_strlcat.c ft_strcpy.c ft_strlcpy.c \
		ft_strlen.c ft_strcmp.c ft_strncmp.c ft_toupper.c \
		ft_tolower.c ft_strchr.c ft_strrchr.c \
		ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c ft_strjoin.c \
		ft_substr.c ft_strtrim.c ft_split.c \
		ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putstr_nl.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
		ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
		ft_lstclear.c ft_lstiter.c ft_lstmap.c get_next_line.c \
		ft_chars.c ft_nums.c ft_printf.c ft_strndup.c

OBJS = $(SRCS:.c=.o)
NAME = libft.a
LIBC = ar rcs
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g3 -O3 -I.

GREEN = \033[0;32m
CYAN = \033[0;36m
NC = \033[0m

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(CYAN)Creating $(NAME) ..."
	@$(LIBC) $(NAME) $(OBJS)
	@echo "✅ $(GREEN)$(NAME) created $(NC)"

all: $(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all fclean clean re