# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 17:08:42 by ataouaf           #+#    #+#              #
#    Updated: 2023/06/14 17:22:14 by ataouaf          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDE = ./inc
SOURCES = ./src
OBJECTS = ./obj_bonus
NAME = philo_bonus

SRCS = 

CC = cc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=thread
OBJS = $(addprefix $(OBJECTS)/, $(SRCS:.c=.o))
RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJECTS)/%.o : $(SOURCES)/%.c $(INCLUDE)/philo_bonus.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJECTS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re