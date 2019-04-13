# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: aholster <aholster@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/02/16 15:46:43 by aholster       #+#    #+#                 #
#    Updated: 2019/04/11 17:51:26 by aholster      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

DATE := $(shell date)

BONOR := lstnew lstdelone lstdel lstadd lstiter lstmap

ADVOR := memalloc memdel strnew strdel strclr striter striteri strmap\
 strmapi strequ strnequ strsub strjoin strtrim strsplit itoa putchar\
 putstr putendl putnbr putchar_fd putstr_fd putendl_fd putnbr_fd 

BASICOR := memset bzero memcpy memccpy memmove memchr memcmp\
 strlen strdup strcpy strncpy strcat strncat strlcat strchr strrchr\
 strstr strnstr strcmp strncmp\
 atoi isalpha isdigit isalnum isascii isprint toupper tolower

CUSOR:= nbrlen del lstaddend itoba iswhitespace isprime power putstrarr\
 putstrarr_fd strarrdel strarrtolst lsttostrarr lstlen min max constrain\
 segdefault factorial count_if range sqrt absneg swap lsttardest memjoin \
 memdup strarrnew textangle stralloc bitprint putmem putmem_fd\
 putmemendl putmemendl_fd lstmemtomem lststrtostr


FILEC = $(ADVOR:%=./ft_%.c) $(BONOR:%=./ft_%.c)\
		$(CUSOR:%=./ft_%.c) $(BASICOR:%=./ft_%.c)

OBJ =	$(ADVOR:%=./ft_%.o) $(BONOR:%=./ft_%.o)\
		$(CUSOR:%=./ft_%.o) $(BASICOR:%=./ft_%.o)

HEAD = libft.h

NAME = libft.a

NORM = norminette $(FILEC) $(HEAD) | grep -e "Error"  -e "Warning" -B 1

GCCC = ${CC} -c
CC = gcc -Wall -Werror -Wextra
AR = ar rcs

all: $(NAME)

assemble: $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@ranlib $(NAME)

$(NAME):
	@echo "\033[0;33mStarting assembly of libft.a...\033[0;00m"
	@time make assemble
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
	@$(NORM) || TRUE 
	@echo "\033[0;00m**+++=====*=====*=====*=====*\
=====*=====*===*=====*=====+++**"

add: norm
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