# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jesmith <jesmith@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2019/02/16 15:46:43 by aholster       #+#    #+#                 #
#    Updated: 2020/02/27 11:11:13 by aholster      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

DATE := $(shell date)

FORMAT_DIR := ./formatters/
FORMAT_SRC := ptraddr decimal char octal caphex lowhex unsigned_dec\
 str n lowsci capsci lowshrthd capshrthd\
 lowhexpoint caphexpoint lowfltpoint capfltpoint

FMT_DIR := $(FORMAT_DIR)/format_dep/
FMT_DEP := naninf_handlers expon_handlers\
 float_handlers shrthd_handlers hexpoint_handlers\
 float_rounder sci_rounder hexpoint_rounder\
 lowsci_print capsci_print hexpoint_printer\
 longdouble_conv unsignconv signconv

PARSE_DIR := ./flag_parser/
PARSE_SRC := flg_verif flgdbl_verif flagharvest\
 flag_flip flag_num_parse flag_arg_extract flag_precision\
 turn_on_flag

UTIL_DIR := ./utilities/
UTIL_SRC := bzero memcpy memmove memset memdup memcmp\
 strcpy strlen strnlen nbrlen islowercase\
 del lstdel lstnew lstaddend

FLT_DIR := ./float_tech/
FLT_SRC := custom_ld_to_text numlst_del numlst_to_txt\
 numlst_newnode  numlst_fwlen numlst_bwlen numlst_postfix numlst_prefix\
 lst_math_halve lst_math_mul lst_math_add numlst_dec_init numlst_minsize\
 numlst_up_magni mantissa_to_numlst numlst_inline_copy

SOURCE := printf vprintf dprintf vdprintf asprintf vasprintf\
 sprintf vsprintf snprintf vsnprintf\
 dispatcher format padder


FILEC := $(SOURCE:%=./ft_%.c) $(FORMAT_SRC:%=$(FORMAT_DIR)ft_%.c)\
$(FMT_DEP:%=$(FMT_DIR)ft_%.c) $(PARSE_SRC:%=$(PARSE_DIR)ft_%.c)\
$(UTIL_SRC:%=$(UTIL_DIR)ft_%.c) $(FLT_SRC:%=$(FLT_DIR)ft_%.c)

OBJ :=	$(FILEC:%.c=%.o)

HEAD := ./ft_printf.h ./incl/ft_internals.h ./incl/ft_writer.h\
./incl/ft_flag_parser.h ./incl/ft_formatters.h ./incl/ft_utilities.h\
./incl/ft_flt_support.h ./float_tech/float_tech.h

NAME := libftprintf.a

NORM = norminette $(FILEC) $(HEAD) | grep -e "Error"  -e "Warning" -B 1

GCCC = ${CC} -c
CC = gcc -Wall -Werror -Wextra -pedantic -g
AR = ar rcs

all: $(NAME)

test: $(OBJ) $(HEAD)
	@rm -f testf
	@$(CC) -w -g -o testf ft_main.c $(FILEC)

assemble: $(OBJ) $(HEAD)
	@$(AR) $(NAME) $(OBJ)
	@ranlib $(NAME)

$(NAME): $(OBJ) $(HEAD)
	@echo "\033[0;33mStarting assembly of $(NAME)…\033[0;00m"
	@time make assemble -j
	@echo "\033[0;32m$(NAME) successfully assembled!\033[0;00m\n"

%.o: %.c
	@$(GCCC) -o $@ $<

clean:
	@echo "\033[0;33mInitializing Summary Deletions...\033[0;00m"
	@rm -rf $(OBJ)
	@find "./" -type f \( -name '*~' -o -name '\#*\#' -o -name '.DS_Store' \)\
	 -exec rm -rfv {} \;
	@echo "\033[0;31m	Executed!\033[0;00m\n"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[0;31mObituary of $(NAME): Deceased on $(shell date).\
	\033[0;00m\n"

re: fclean all

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
