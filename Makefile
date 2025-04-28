NAME = cub3D

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

CFLAGS = -Wall -Werror -Wextra

SOURCES = ./main.c

LIBFT = libft/libft.a
SRCDIR = src
OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

all: $(NAME)

$(NAME):	$(LIBFT) $(OBJS)
	@echo "${YELLOW}Compiling program...${RESET}"
	@cc ${CFLAGS} ${OBJS} -o ${NAME}
	@echo "${GREEN}Compilation success !${RESET}"

$(LIBFT):
	@make -s -C libft all

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@cc $(CFLAGS) -c $< -o $@

clean:
	@echo "${YELLOW}Cleaning...${RESET}"
	@${RM} -rf ${OBJDIR}

fclean: clean
	@echo "$(RED)Cleaning all...$(RESET)"
	@rm -f $(NAME) obj
	@make -s -C libft fclean

re: fclean all