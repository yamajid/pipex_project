
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yamajid <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/25 00:13:45 by yamajid           #+#    #+#              #
#    Updated: 2023/02/25 00:13:45 by yamajid          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Werror -Wextra
DBUILD = build
FILES = pipex pipex_utils ft_split_utils
	
OBJS = $(addprefix $(DBUILD)/, $(FILES:=.o))

NAME = pipex

all: $(NAME) 

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

$(DBUILD)/%.o: %.c pipex.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(DBUILD)
fclean: clean
	rm -f $(NAME) 
re: fclean all
