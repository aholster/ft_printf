# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jesmith <jesmith@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2019/02/16 15:46:43 by aholster       #+#    #+#                 #
#    Updated: 2019/05/30 19:25:58 by aholster      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

DATE := $(shell date)

SUBDIR := ./writers/

SUBSOURCE := str ptraddr unsigned_dec
#decimal

SOURCE := printf dispatcher format flinit flagharvest clinit functblinit\
 padder

FILEC = $(SOURCE:%=./ft_%.c) $(SUBSOURCE:%=$(SUBDIR)ft_%.c)

OBJ =	$(SOURCE:%=./ft_%.o) $(SUBSOURCE:%=$(SUBDIR)ft_%.o)

HEAD = ft_printf.h

NAME = libftprintf.a

NORM = norminette $(FILEC) $(HEAD) | grep -e "Error"  -e "Warning" -B 1

GCCC = ${CC} -c
CC = gcc -Wall -Werror -Wextra
AR = ar rcs

all: $(NAME)

assemble: $(OBJ)
	@cp ./libft/libft.a ./$(NAME)
	@$(AR) $(NAME) $(OBJ)
	@ranlib $(NAME)

$(NAME):
	@make -C ./libft -j
	@echo "\033[0;33mStarting assembly of $(NAME)…\033[0;00m"
	@time make assemble -j
	@echo "\033[0;32m$(NAME) successfully assembled!\033[0;00m\n"

%.o: %.c
	@$(GCCC) -o $@ $< -I ./libft -I ./

clean:
	@make clean -C ./libft
	@echo "\033[0;33mInitializing Summary Deletions...\033[0;00m"
	@rm -rf $(OBJ)
	@find "./" -type f \( -name '*~' -o -name '\#*\#' -o -name '.DS_Store' \)\
	 -exec rm -rfv {} \;
	@echo "\033[0;31m	Executed!\033[0;00m\n"

fclean: clean
	@make fclean -C ./libft
	@rm -rf $(NAME)
	@echo "\033[0;31mObituary of $(NAME): Deceased on $(shell date).\
	\033[0;00m\n"

re: fclean all
#	@make re -C ./libft

norm:
	@echo "**+++=====*=====*=====*=====*{\033[0;31mOUT\033[0;00m}\
	*=====*=====*=====*=====+++**\033[0;33m"
	@$(NORM) || TRUE 
	@echo "\033[0;00m**+++=====*=====*=====*=====*\
=====*=====*===*=====*=====+++**"

add:
	@git add $(FILEC) $(HEAD) Makefile author
	git status

push: norm
ifdef MSG
	@git commit -m "$(MSG)"
	git push
else
	@git commit
	git push
endif