#------------------ Config -----------------#
NAME = pipex
SRCS = $(SRCDIR)/main.c     \
	   $(SRCDIR)/error.c    \
	   $(SRCDIR)/exec.c     \
	   $(SRCDIR)/helper.c   \
	   $(SRCDIR)/env.c     \

#---------------- Variables ----------------#
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./include -I./libft
SRCDIR = src
OBJDIR = obj
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Libft configuration
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

GREEN = $$(tput setaf 2)
RESET = $$(tput sgr0)

#----------------- Targets ----------------#
all: $(LIBFT) $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@echo "$(GREEN)Created object directory$(RESET)"

# Rule to make libft
$(LIBFT):
	@echo "Compiling libft..."
	@make --no-print-directory -C $(LIBFT_DIR)

$(NAME): $(OBJDIR) $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft
	@echo "$(GREEN)$(NAME) created successfully!$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

test:
	@../pipex-tester/run.sh

clean:
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@rm -rf $(OBJDIR)
	@echo "$(GREEN)Cleaned object files$(RESET)"

fclean:
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@rm -rf $(OBJDIR)
	@echo "$(GREEN)Cleaned object files$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)Cleaned program$(RESET)"

re: fclean all

.PHONY: all clean fclean re