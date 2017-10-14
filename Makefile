# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/13 18:15:03 by mmeziyan          #+#    #+#              #
#    Updated: 2017/05/05 19:24:46 by juhallyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#_Colors_#

GREEN	=	echo "\x1b[32m $1 \x1b[0m $2"

PURPLE	=	echo "\x1b[35m $1 \x1b[0m $2"

#_Files_#

NAME	=	ft_ls

SRC 	=	main.c			\
			tools.c			\
			tabtools.c		\
			options.c		\
			args.c			\
			data.c			\
			list.c			\
			print.c			\
			sort.c			\

OBJ		=	$(SRC:.c=.o)

LIB		=	libft/

# INC		= -I ./includes/ -I ./libft/

#_Compilation_#

FLAG 	=	-g -W -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@$(call PURPLE,"=== Compilation of ft_ls ==="\t\t"LOADING")
	@cd $(LIB) && $(MAKE) libft.a
	@cd srcs/ && gcc $(FLAG) -c $(SRC)
	@cd srcs/ && gcc $(OBJ) -L ../libft -lft -o ../$(NAME)
	@$(call GREEN,"=== $(NAME) created ==="\t\t\t"DONE")

clean:
	@cd srcs && rm -f $(OBJ)
	@cd $(LIB) && $(MAKE) $@
	@$(call GREEN,"=== .o files deleted ==="\t\t\t"DONE")

fclean:
	@cd $(LIB) && $(MAKE) $@
	@cd srcs/ && rm -f $(OBJ)
	@rm -f $(NAME)
	@$(call GREEN,"=== Repository is clean ==="\t\t"DONE")

re: fclean all

norm: fclean
	@clear
	@norminette $(SRC)

.PHONY: all norm clean fclean