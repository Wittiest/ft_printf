#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpearson <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/18 11:51:28 by dpearson          #+#    #+#              #
#    Updated: 2017/10/24 12:26:34 by dpearson         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror -I ./

NAME		=	libftprintf.a

FILENAMES	=	ft_printf.c utils.c conversion_char.c parser.c chars.c hex.c \
				decimal.c

OBJECTS		= ${FILENAMES:.c=.o}

all : $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)
	ranlib $(NAME)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all