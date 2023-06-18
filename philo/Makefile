# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/24 17:34:01 by ataouaf           #+#    #+#              #
#    Updated: 2023/06/16 16:57:13 by ataouaf          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDE = ./inc
SOURCES = ./src
OBJECTS = ./obj
NAME = philo

SRCS = philo.c init.c routine.c thread.c utils.c

CC = cc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=thread
OBJS = $(addprefix $(OBJECTS)/, $(SRCS:.c=.o))
RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJECTS)/%.o : $(SOURCES)/%.c $(INCLUDE)/philo.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJECTS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re