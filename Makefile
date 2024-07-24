######################### source files ###############################

SRCS			= 	main.c \
					ft_split.c \
					ft_move_plr.c \
					ft_drop_rays.c \
					ft_rendering.c \
					ft_intersection.c \
					parsing/get_next_line_utils.c \
					parsing/get_next_line.c \
					parsing/parsing.c 


######################### object files ###############################

OBJS			= $(SRCS:%c=%o)

########################### variables #################################

NAME			= cube

LINK			= -framework Cocoa -framework OpenGL -framework IOKit

LIBS			= MLX42/libmlx42.a -lglfw3

############################# rules ###################################

all				: $(NAME)

o%				: %c cube.h
	gcc -c $< -o $@

$(NAME)			: $(OBJS)
	gcc $(OBJS)  -o $(NAME) $(LINK) $(LIBS) -Ofaster

clean			:
	rm -rf *o

fclean			: clean
	rm -rf $(NAME)

re				: fclean all