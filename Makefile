# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/12 16:03:52 by obanshee          #+#    #+#              #
#    Updated: 2020/01/06 17:37:29 by obanshee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

FLAGS = -g -Wall -Wextra -Werror

LIBFTPRINTF_PATH = libftprintf/
LIBFTPRINTF = libftprintf/libftprintf.a

INC = -I includes/ -I libftprintf/includes/

SRCS_NAME = main.c options.c ft_ls.c lib_ls.c option_R.c option_l.c \
			dir_array.c files_array.c reader.c printer.c

SRCS_PATH = srcs/
OBJ_PATH  = obj/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(SRCS_NAME:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFTPRINTF_PATH)
	@gcc -o $(NAME) $(FLAGS) $(INC) $(OBJ) $(LIBFTPRINTF)

$(OBJ_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir -p obj
	@gcc -c $(FLAGS) $(INC) $< -o $@

clean:
	@make -C $(LIBFTPRINTF_PATH)/ clean
	@/bin/rm -rf $(OBJ_PATH)

fclean: clean
	@make -C $(LIBFTPRINTF_PATH)/ fclean
	@/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re