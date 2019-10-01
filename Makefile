# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jesmith <jesmith@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2019/02/16 15:46:43 by aholster       #+#    #+#                 #
#    Updated: 2019/09/30 19:42:01 by aholster      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

DATE := $(shell date)

SUBDIR := ./formatters/

SUBSOURCE := ptraddr decimal char octal caphex lowhex unsigned_dec\
 signconv unsignconv str n lowsci capsci lowshrthd capshrthd \
 longdouble_conv lowhexpoint caphexpoint capshort lowfltpoint

SOURCE := printf vprintf dprintf vdprintf asprintf vasprintf\
sprintf vsprintf snprintf vsnprintf\
dispatcher format flinit flagharvest padder\
flag_verificators handling rounder

FILEC = $(SOURCE:%=./ft_%.c) $(SUBSOURCE:%=$(SUBDIR)ft_%.c)

OBJ =	$(FILEC:%.c=%.o)

HEAD = ./ft_printf.h ./incl/ft_internals.h ./incl/ft_writer.h

NAME = libftprintf.a

NORM = norminette $(FILEC) $(HEAD) | grep -e "Error"  -e "Warning" -B 1

GCCC = ${CC} -c
CC = gcc -g -Wall -Werror -Wextra
AR = ar rcs

all: $(NAME)

test: $(OBJ)
	@rm -f testf
	@cp ./float_tech/float_tech.a ./$(NAME)
	@$(CC) -w -o testf $(OBJ) ft_main.c -L ./ -lftprintf

assemble: $(OBJ)
	@cp ./float_tech/float_tech.a ./$(NAME)
	@$(AR) $(NAME) $(OBJ)
	@ranlib $(NAME)

$(NAME):
	@make -C ./libft -j
	@make -C ./float_tech -j
	@echo "\033[0;33mStarting assembly of $(NAME)…\033[0;00m"
	@time make assemble -j
	@echo "\033[0;32m$(NAME) successfully assembled!\033[0;00m\n"

%.o: %.c
	@$(GCCC) -o $@ $<

clean:
	@make clean -C ./libft
	@make clean -C ./float_tech
	@echo "\033[0;33mInitializing Summary Deletions...\033[0;00m"
	@rm -rf $(OBJ)
	@find "./" -type f \( -name '*~' -o -name '\#*\#' -o -name '.DS_Store' \)\
	 -exec rm -rfv {} \;
	@echo "\033[0;31m	Executed!\033[0;00m\n"

fclean: clean
	@make fclean -C ./libft
	@make fclean -C ./float_tech
	@rm -rf $(NAME)
	@echo "\033[0;31mObituary of $(NAME): Deceased on $(shell date).\
	\033[0;00m\n"

re: fclean all
#	@make re -C ./libft

norm:
	@echo "**+++=====*=====*=====*=====*{\033[0;31mOUT\033[0;00m}\
	*=====*=====*=====*=====+++**\033[0;33m"
	@time $(NORM) || TRUE
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