FLAGS = -g # -Wall -Wextra -Werror
MKEX = gcc $(FLAGS) -o
_SRC = main.c parse_flags.c md5.c utils.c sha256.c md5_utils.c \
	sha256_utils.c sha256_printing.c
SRC = $(addprefix ./srcs/, $(_SRC))
OBJECT = $(SRC:.c=.o)
COMP = gcc -c
FT_LS = ft_ssl
OBJDIR = ./obj
INCLUDES = incl

# Colors
RED				= \033[31;1m
GREEN			= \033[32;1m
YELLOW			= \033[33;1m
BLUE			= \033[34;1m
PURPLE			= \033[35;1m
CYAN			= \033[36;1m
LGREY			= \033[37;1m
END_C			= \033[m
CLEAR			= "\033[K"

all : $(FT_LS)

%.o : %.c
	@$(COMP) $(FLAGS) -I $(INCLUDES) $< -o $@

$(FT_LS) : $(OBJECT)
	@make -C libft/
	@printf "$(RED)FT_LS building...\r$(END_C)"
	@$(MKEX) $(FT_LS) $(OBJECT) -L libft/ -lft
	@printf "\r" && printf $(CLEAR) && printf "$(GREEN)ft_ssl built!\n$(END_C)"

clean :
	@make clean -C libft/
	@/bin/rm -f $(OBJECT)

fclean : clean
	@make fclean -C libft/
	@rm -f $(FT_LS)

re : fclean all

.PHONY: all clean fclean re
.SILENT:
print-%  : ; @echo $* = $($*)