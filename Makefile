# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/04 15:47:25 by mvomiero          #+#    #+#              #
#    Updated: 2023/05/05 11:40:59 by mvomiero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CC		= gcc
CFLAGS	= -Werror -Wall -Wextra -pthread -fsanitize=thread -g

SRC_PATH = srcs/
SRC		=	main.c \
			init_parsing.c \
			exit_error.c \
			utils.c \
			dinner.c \
			philosopher.c \
			utils_time.c \
			logs.c \
			waiter.c
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

test1:
	@echo "Should not eat and should die"
	./philo 1 800 200 200

test2:
	@echo "All alive!"
	sleep 1
	./philo 5 800 200 200

test3:
	./philo 5 800 200 200 7
	@echo "Everybody ate!"

test4:
	@echo "All alive!"
	sleep 1
	./philo 4 410 200 200

test5:
	./philo 4 310 200 100
	@echo "A philo should die"

.PHONY: all re clean fclean