# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/07 19:03:17 by rsibiet           #+#    #+#              #
#    Updated: 2016/03/29 13:00:24 by rsibiet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select

FTC = main_ft_select.c \
	  lst_ft_select.c \
	  gen_lst_select.c \
	  gen2_lst_select.c \
	  gen3_lst_select.c \
	  signal_ft_select.c \
	  bonus_ft_select.c \
	  interface_ft_select.c

FTO = $(subst .c,.o,$(FTC))

.PHONY: all re clean fclean

all: $(NAME)

$(NAME): $(FTO)
	@echo ""
	@echo ""
	@echo "\033[32m• $(NAME) created!\033[0m"
	@echo "\n"
	@echo "\033[34;1m___________________________ Loading libft ______________________________\033[0m\n"
	@make -C ./libft
	@gcc -o $(NAME) $(FTO) ./libft/libft.a -ltermcap

%.o: %.c
	@gcc -Wall -Wextra -Werror -I./libft/ -c $<
	@echo "\033[42m         \033[0m\c"

clean:
	@make -C ./libft clean
	@rm -rf $(FTO)
	@echo "\033[33m• $(NAME) object deleted!\033[0m"

fclean: clean
	@make -C ./libft fcleana
	@rm -rf $(NAME)
	@echo "\033[31;1m• \033[31m$(NAME) deleted!\033[0m"

re: fclean all
