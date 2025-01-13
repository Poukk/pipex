#------------------ Config -----------------#
NAME = libft.a
SRCS =	ft_split.c     \
	ft_strjoin.c   \
	ft_strlcat.c   \
	ft_strlcpy.c   \
	ft_strlen.c    \
	ft_strncmp.c   \
	ft_putstr_fd.c \
	ft_strdup.c

#---------------- Variables ----------------#
CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJDIR = obj
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

GREEN = $$(tput setaf 2)
RESET = $$(tput sgr0)

#----------------- Targets ----------------#
all: $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@echo "$(GREEN)Created libft object directory$(RESET)"

$(NAME): $(OBJDIR) $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(GREEN)$(NAME) created successfully!$(RESET)"

$(OBJDIR)/%.o: %.c libft.h
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)
	@echo "$(GREEN)Cleaned object files$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(GREEN)Cleaned library$(RESET)"

re: fclean all

.PHONY: all clean fclean re
