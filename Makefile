NAME	:= miniRT
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	:= ./lib/MLX42

LIBFT_DIR := lib/libft
LIBFT	 := $(LIBFT_DIR)/libft.a
HEADERS	 := -I ./include -I $(LIBMLX)/include
LIBS	 := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS	 := $(shell find ./src -iname "*.c")
OBJ_DIR  := obj
OBJS	 := $(patsubst ./src/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: libmlx libft $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJ_DIR)/%.o: ./src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) $(LIBFT)

libft:
	@echo "Building libft library"
	@cd $(LIBFT_DIR) && make all

libft_clean:
	@echo "Cleaning libft objects"
	@cd $(LIBFT_DIR) && make fclean

clean: libft_clean
	@rm -rf $(OBJ_DIR)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx

