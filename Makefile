######################### source files ###############################

SRCS			= 	main.c \
					ft_split.c \
					ft_move_plr.c \
					ft_drop_rays.c \
					ft_rendering.c \
					ft_intersection.c \
					ft_create_list.c \
					ft_get_im.c \
					ft_mini_map.c

######################### object files ###############################

OBJS			= $(SRCS:%c=%o)

########################### variables #################################

NAME			= cube

LINK			= -framework Cocoa -framework OpenGL -framework IOKit

LIBS			= MLX42/libmlx42.a -lglfw3

############################# rules ###################################

all				: $(NAME)

o%				: %c cube.h
	gcc -g -fsanitize=address $< -o $@

$(NAME)			: $(OBJS)
	gcc -g -fsanitize=address $(OBJS) $(LINK) -o $(NAME) $(LIBS) -Ofaster

clean			:
	rm -rf *o

fclean			: clean
	rm -rf $(NAME)

re				: fclean all