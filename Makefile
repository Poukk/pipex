#------------------ Config -----------------#
NAME = pipex
SRCS = $(SRCDIR)/main.c     \
       $(SRCDIR)/error.c    \
       $(SRCDIR)/exec.c     \
       $(SRCDIR)/ft_split.c \
       $(SRCDIR)/helper.c     \
	   $(SRCDIR)/env.c     \

#---------------- Variables ----------------#
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./include
SRCDIR = src
OBJDIR = obj
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

GREEN = $$(tput setaf 2)
RESET = $$(tput sgr0)

#----------------- Targets ----------------#
all: $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@echo "$(GREEN)Created object directory$(RESET)"

$(NAME): $(OBJDIR) $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS)
	@echo "$(GREEN)$(NAME) created successfully!$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)
	@echo "$(GREEN)Cleaned object files$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(GREEN)Cleaned program$(RESET)"

re: fclean all

.PHONY: all clean fclean re
