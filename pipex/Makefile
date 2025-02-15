# **************************************************************************** #
#                                                                             #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: razamora <razamora@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/25 08:53:33 by razamora          #+#    #+#              #
#    Updated: 2024/07/25 10:16:25 by razamora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex
BONUS		= pipex_bonus
CC			= gcc -g
CFLAGS		=  #-fsanitize=leak -g3
RM			= rm -rf

SOURCES = pipex.c pipex_utils.c pipex_handle_error.c
SOURCES_BONUS = pipex_bonus.c pipex_utils_bonus_1.c pipex_utils_bonus_2.c pipex_handle_error_bonus.c
OBJECTS = $(SOURCES:.c=.o)
OBJECTS_BONUS = $(SOURCES_BONUS:.c=.o)

LIBFT		= libft/libft.a
INCLUDE		= ./include/

all : $(NAME)

bonus: $(BONUS)

$(BONUS): $(OBJECTS_BONUS) $(LIBFT) 
	$(CC) $(CFLAGS) $(OBJECTS_BONUS) $(LIBFT) -I $(INCLUDE) -o $(BONUS)

$(NAME): $(OBJECTS) $(LIBFT) 
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -I $(INCLUDE) -o $(NAME)

$(LIBFT):
	make -C libft

%.o:%.c
	$(CC) $(CFLAGS) -c $< -I $(INCLUDE) -o $@

clean :
	$(RM) $(OBJECTS) $(OBJECTS_BONUS)
	make clean -C libft

fclean : clean
	$(RM) $(NAME)
	$(RM) $(BONUS)
	$(RM) $(LIBFT)

re : fclean all

.PHONY : all clean fclean re bonus