# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lchantel <lchantel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/30 10:53:46 by lchantel          #+#    #+#              #
#   Updated: 2022/06/27 15:31:13 by                  ###   ########.fr       # #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c			\
	ft_bzero.c			\
	ft_isalnum.c		\
	ft_isalpha.c		\
	ft_isascii.c		\
	ft_isdigit.c		\
	ft_isprint.c		\
	ft_itoa.c			\
	ft_memccpy.c		\
	ft_memchr.c			\
	ft_memcmp.c			\
	ft_memcpy.c			\
	ft_memmove.c		\
	ft_memset.c			\
	ft_putchar_fd.c		\
	ft_putendl_fd.c		\
	ft_putnbr_fd.c		\
	ft_putstr_fd.c		\
	ft_split.c			\
	ft_strchr.c			\
	ft_strdup.c			\
	ft_strjoin.c		\
	ft_strlcat.c		\
	ft_strlcpy.c		\
	ft_strlen.c			\
	ft_strmapi.c		\
	ft_strncmp.c		\
	ft_strnstr.c		\
	ft_strrchr.c		\
	ft_strtrim.c		\
	ft_substr.c			\
	ft_tolower.c		\
	ft_toupper.c		\
	ft_calloc.c			\

BONUS_SRC	= 			\
	ft_lstnew.c			\
	ft_lstadd_front.c	\
	ft_lstsize.c		\
	ft_lstlast.c		\
	ft_lstadd_back.c	\
	ft_lstdelone.c		\
	ft_lstclear.c		\
	ft_lstiter.c		\
	ft_lstmap.c			\

CC			= gcc
WARNS		= -Wall -Wextra -Werror -g -O0
MAIN_OBJS	= $(SRC:.c=.o)
BONUS_OBJS	= $(BONUS_SRC:.c=.o)
HEADER_DIR	= ./
HEADER		= libft.h

$(NAME): right_prep $(HEADER) $(MAIN_OBJS)
		@ar rcs $(NAME) $(MAIN_OBJS)
		@echo "All functions added to static lib..."

right_prep: $(MAIN_OBJS)
		@echo "Every mandatory function is compile proved!"

$(MAIN_OBJS): %.o: %.c
		@echo "checking $< to be right..."
		@$(CC) $(WARNS) -o $@ -c $<

all: $(NAME)

$(BONUS_OBJS): %.o: %.c
	@echo "checking $< to be right..."
	@$(CC) $(WARNS) -o $@ -c $<

bonus_right: $(BONUS_OBJS)
	@echo "Every bonus function is compile proved!"

bonus: bonus_right $(HEADER) $(BONUS_OBJS)
		@ar rcs $(NAME) $(BONUS_OBJS)
		@echo "Bonus functions succesfully added to static lib..."
		
clean:
		@echo "Removing all binaries..."
		@rm -rf $(MAIN_OBJS) $(BONUS_OBJS)

fclean: clean
		@echo "Removing static lib..." 
		@rm -rf $(NAME)

re: fclean all

