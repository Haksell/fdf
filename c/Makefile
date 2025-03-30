NAME := fdf

PATH_SRCS := srcs
PATH_OBJS := objs
PATH_INCLUDES := includes

PATH_LIBFT := libft
LIBFT := $(PATH_LIBFT)/libft.a
LIBFT_REPO := git@github.com:Haksell/libft.git

PATH_MLX := mlx
MLX := $(PATH_MLX)/libmlx.a
MLX_REPO := git@github.com:42Paris/minilibx-linux.git

RESET := \033[0m
RED := \033[1m\033[31m
GREEN := \033[1m\033[32m
BLUE := \033[1m\033[34m
PINK := \033[1m\033[35m

GARBAGE := .vscode
YEET := 1>/dev/null 2>/dev/null

CC := cc -Wall -Wextra -Werror -Ofast -mavx -g3
INCLUDES := -I./$(PATH_INCLUDES) -I./$(PATH_LIBFT) -I./$(PATH_MLX)
LIBRARIES := -L$(PATH_LIBFT) -lft -lX11 -lXext -L$(PATH_MLX) -lmlx -lm

# TOOD: wildcard
FILENAMES += main
FILENAMES += display/bresenham
FILENAMES += display/pixels
FILENAMES += display/put_lines
FILENAMES += display/render_frame
FILENAMES += events/handle_key_down
FILENAMES += events/handle_mouse
FILENAMES += parsing/parse_cell
FILENAMES += parsing/parse_map
FILENAMES += projections/cabinet
FILENAMES += projections/isometric
FILENAMES += projections/parallel
FILENAMES += transform/linear_transformations
FILENAMES += transform/transform_vertex
FILENAMES += utils/clean
FILENAMES += utils/initialize
FILENAMES += utils/math

HEADERS := fdf fdf_test

SRCS := $(addprefix $(PATH_SRCS)/, $(addsuffix .c, $(FILENAMES)))
OBJS := $(addprefix $(PATH_OBJS)/, $(addsuffix .o, $(FILENAMES)))
HEADERS := $(addprefix $(PATH_INCLUDES)/, $(addsuffix .h, $(HEADERS)))

define clone_repo
	@echo "$(GREEN)==> Cloning $(1)$(RESET)"
	@git clone $(2) $(1) $(YEET)
	@rm -rf $(1)/.git*
endef

define compile_target
	@echo "$(GREEN)==> Compiling $(1)$(RESET)"
	@$(MAKE) -s -C $(1) $(YEET)
endef

define remove_target
@if [ -e "$(1)" ]; then \
	rm -rf "$(1)"; \
	echo "$(RED)[X] $(1) removed.$(RESET)"; \
fi
endef

all: $(NAME)

$(PATH_OBJS):
	@mkdir -p $(sort $(dir $(OBJS)))

$(OBJS): $(PATH_OBJS)/%.o: $(PATH_SRCS)/%.c $(HEADERS) $(LIBFT) $(MLX) | $(PATH_OBJS)
	@mkdir -p $(PATH_OBJS)
	@$(CC) -c $< -o $@ $(INCLUDES)
	@echo "$(BLUE)+++ $@$(RESET)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBRARIES) -o $@
	@echo "$(PINK)$@ is compiled.$(RESET)"

$(PATH_LIBFT):
	$(call clone_repo,$(PATH_LIBFT),$(LIBFT_REPO))

$(LIBFT): | $(PATH_LIBFT)
	$(call compile_target,$(PATH_LIBFT))

$(PATH_MLX):
	$(call clone_repo,$(PATH_MLX),$(MLX_REPO))

$(MLX): | $(PATH_MLX)
	$(call compile_target,$(PATH_MLX))

clean:
	@rm -rf $(GARBAGE)
	$(call remove_target,$(PATH_LIBFT))
	$(call remove_target,$(PATH_MLX))
	$(call remove_target,$(PATH_OBJS))

fclean: clean
	$(call remove_target,$(NAME))

re: fclean
	@$(MAKE) -s $(NAME)

.PHONY: all clean fclean re
