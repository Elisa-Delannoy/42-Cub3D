NAME = cub3D

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

CFLAGS = -Wall -Werror -Wextra -g -Iinclude
FMLX = -I/usr/include -Iminilibx-linux
LINKMLX = -Lminilibx-linux -lmlx -lXext -lX11 -lm -lz
SOURCES = ./game/game.c ./game/key_mouse.c ./game/movement.c ./game/torch.c ./game/window.c ./init_free/free.c ./init_free/init2.c ./init_free/init3.c ./init_free/init.c ./main.c ./minimap/mini_map2.c ./minimap/mini_map.c ./parsing/bonus.c ./parsing/check_first_part_file.c ./parsing/check_map.c ./parsing/check_map_space.c ./parsing/check_map_wall.c ./parsing/color.c ./parsing/coordinates.c ./parsing/parse.c ./raycasting/raycasting2.c ./raycasting/raycasting.c ./utils/utils2.c ./utils/utils.c 

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