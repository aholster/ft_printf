# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: aholster <aholster@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/02/16 15:46:43 by aholster       #+#    #+#                 #
#    Updated: 2019/09/25 15:37:54 by jesmith       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

DATE := $(shell date)

SOURCE := custom_ld_to_text numlst_del numlst_to_txt\
 numlst_newnode  numlst_fwlen numlst_bwlen numlst_postfix numlst_prefix\
 lst_math_halve lst_math_mul lst_math_add numlst_dec_init numlst_minsize\
 numlst_up_magni mantissa_to_numlst numlst_inline_copy

FILEC := $(SOURCE:%=./ft_%.c)

OBJ := $(SOURCE:%=./ft_%.o)

HEAD := float_tech.h

NAME := float_tech.a

NORM := norminette $(FILEC) $(HEAD) | grep -e "Error"  -e "Warning" -B 1

GCCC := ${CC} -c
CC := gcc -g -Wall -Werror -Wextra -L ./../libft/ -lft
AR := ar rcs

all: $(NAME)

assemble: $(OBJ)
	@cp ./../libft/libft.a ./float_tech.a
	@$(AR) $(NAME) $(OBJ)
	@ranlib $(NAME)

$(NAME):
#	@make -C ./../libft/
	@echo "\033[0;33mStarting assembly of $(NAME)…\033[0;00m"
	@time make assemble
	@echo "\033[0;32m$(NAME) successfully assembled!\033[0;00m\n"

%.o: %.c
	@$(GCCC) -o $@ $<

clean:
#	@make clean -C ./../libft/
	@echo "\033[0;33mInitializing Summary Deletions...\033[0;00m"
	@rm -rf $(OBJ)
	@find "./" -type f \( -name '*~' -o -name '\#*\#' -o -name '.DS_Store' \)\
	 -exec rm -rfv {} \;
	@echo "\033[0;31m	Executed!\033[0;00m\n"

fclean: clean
#	@make fclean -C ./../libft/
	@rm -rf $(NAME)
	@echo "\033[0;31mObituary of $(NAME): Deceased on $(shell date).\
	\033[0;00m\n"

re: fclean all

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