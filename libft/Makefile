# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achirat <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/08 16:17:01 by achirat           #+#    #+#              #
#    Updated: 2018/06/20 17:06:14 by lbelda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_squareroot.c ft_lstdup.c ft_putchar.c ft_putstr.c ft_putnbr.c ft_strdup.c ft_strlen.c ft_strcpy.c\
	   ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c\
	   ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c\
	   ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c\
	   ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c\
	   ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c\
	   ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c \
	   ft_itoa.c ft_strsplit.c ft_putendl.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	   ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c \
	   ft_lstaddend.c ft_lstlen.c ft_swap.c ft_sqrt.c ft_foreach.c ft_nextsqrt.c ft_lstrev.c \
	   ft_strrev.c get_next_line.c ft_unicode.c check_width.c update_flags.c ft_precision_str.c \
	   ft_printf.c fill_conv.c ft_conv.c fill_buff.c modif_var.c check_buff.c add_flags.c \
	   ft_str_unicode.c ft_itoabase.c ft_strnjoin.c ft_strndup.c ft_tabdel.c \
	   ft_clamp.c ft_fclamp.c

CC = gcc

VPATHS = OBJS:./obj

CFLAGS = -Wall -Werror -Wextra

OBJS = $(addprefix obj/, $(SRCS:.c=.o))

CPPFLAGS = -Iincludes

.PHONY: re all fclean clean

all: $(NAME)

$(NAME): $(OBJS) 
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

obj/%.o: %.c
	@mkdir obj 2> /dev/null || true
	@$(CC) $(CFLAGS) -o $@ -c $< $(CPPFLAGS)

clean : 
	@rm -rf $(OBJS)
	@rmdir obj 2> /dev/null || true

fclean: clean
	@rm -rf $(NAME)

re: fclean all
