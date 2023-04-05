# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/04 15:47:25 by mvomiero          #+#    #+#              #
#    Updated: 2023/04/04 16:34:20 by mvomiero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CC		= gcc
CFLAGS	= -Werror -Wall -Wextra 
#-pthread

SRC_PATH = srcs/
SRC		=	main.c 
SRCS	= $(addprefix $(SRC_PATH), $(SRC))

OBJ_PATH = objs/
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

INC		= -I ./includes/

all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
#	@echo "Compiling object files"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	@echo "Compiling minishell..."
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo "\n\t\033[32;1;3mphilo ready\n"

$(OBJ_PATH):
#	@echo "Generating obj folders"
	@mkdir $(OBJ_PATH)

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean