# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ataouaf <ataouaf@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/24 17:34:01 by ataouaf           #+#    #+#              #
#    Updated: 2023/05/29 15:49:19 by ataouaf          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDE = ./inc
SOURCES = ./src
OBJECTS = ./obj
NAME = philo

SRCS = philo.c parsing.c init.c activity.c thread.c utils.c

CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJS = $(addprefix $(OBJECTS)/, $(SRCS:.c=.o))
RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJECTS)/%.o : $(SOURCES)/%.c $(INCLUDE)/philo.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $(NAME)

clean :
	$(RM) $(OBJECTS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re