NAME = cub3D

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

CFLAGS = -Wall -Werror -Wextra -g
FMLX = -I/usr/include -Iminilibx-linux
LINKMLX = -Lminilibx-linux -lmlx -lXext -lX11 -lm -lz
SOURCES = ./check_first_part_file.c ./check_map.c ./init_free.c ./main.c ./parse.c ./utils.c 

LIBFT = libft/libft.a
MLX = minilibx-linux/libmlx.a
SRCDIR = src
OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

all: $(NAME)

$(NAME):	$(LIBFT) $(MLX) $(OBJS)
	@echo "${YELLOW}Compiling program...${RESET}"
	@cc ${CFLAGS} ${FMLX} ${OBJS} ${LINKMLX} -o ${NAME} $(LIBFT)
	@echo "${GREEN}Compilation success !${RESET}"

$(LIBFT):
	@echo "${YELLOW}Building libft...${RESET}"
	@make -s -C libft all

$(MLX):
	@echo "$(YELLOW)Building minilibx...$(RESET)"
	@make -s -C minilibx-linux all

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
	@make -s -C minilibx-linux clean

re: fclean all