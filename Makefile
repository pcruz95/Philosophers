# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcruz <pcruz@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/04 13:07:43 by pcruz             #+#    #+#              #
#    Updated: 2021/08/13 15:31:32 by pcruz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	=	philo

SRCS	=	philo.c \
			routines.c \
			utils.c

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc

CFLAGS	=	-pthread -Wall -Wextra -Werror

RM 		=	rm -f

$(NAME)	:	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

all 	:	$(NAME)


clean 	: 
			$(RM) $(OBJS)

fclean	:	clean
			$(RM) $(NAME)

re 		: 	fclean all

.PHONY	:	all clean fclean re