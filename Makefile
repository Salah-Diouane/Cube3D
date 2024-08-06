######################### source files ###############################

SRCS			= 	main.c \
					ft_split.c \
					ft_move_plr.c \
					ft_drop_rays.c \
					ft_rendering.c \
					ft_intersection.c \
					ft_create_list.c \
					ft_get_im.c \
					ft_mini_map.c \
					parsing/ft_read_map.c \
					parsing/ft_check_textures.c \
					parsing/ft_check_colors.c \
					parsing/ft_get_next_line.c \
					parsing/ft_get_next_line_utils.c \
					parsing/ft_extract_map.c \
					parsing/ft_check_map.c \
					parsing/ft_check_around_elements.c \
					parsing/ft_check_first_last_line.c \
					parsing/ft_check_walls_and_elements.c \
					parsing/ft_player_position.c \
					parsing/ft_map_carre.c \
					parsing/free_all.c 


######################### object files ###############################

OBJS			= $(SRCS:.c=.o)

########################### variables #################################

NAME			= cube

LINK			= -framework Cocoa -framework OpenGL -framework IOKit

LIBS			= MLX42/libmlx42.a -lglfw3

CFLAGS			= -g -fsanitize=address 

############################# rules ###################################

all				: $(NAME)

%.o				: %.c
	cc $(CFLAGS) -c $< -o $@

$(NAME)			: $(OBJS)
	cc  $(CFLAGS) $(OBJS) $(LINK) -o $(NAME) $(LIBS)

clean			:
	rm -rf $(OBJS)

fclean			: clean
	rm -rf $(NAME)

re				: fclean all
