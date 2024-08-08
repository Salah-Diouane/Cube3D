######################### source files ###############################

SRCS			= 	main.c \
					ft_split.c \
					ft_move_plr.c \
					ft_cast_rays.c \
					ft_mini_map.c \
					ft_rendering.c \
					ft_intersection.c \
					ft_face_list.c \
					ft_check_next.c \
					ft_door_ctl.c \
					ft_gun_sprite.c \
					cube_utils.c \
					ft_get_im.c \
					parsing/ft_read_map.c \
					parsing/ft_check_textures.c \
					parsing/ft_check_colors.c \
					parsing/ft_check_colors_utils.c \
					parsing/ft_get_next_line.c \
					parsing/ft_get_next_line_utils.c \
					parsing/ft_extract_map.c \
					parsing/ft_get_input.c \
					parsing/ft_check_map.c \
					parsing/ft_check_map_utils.c \
					parsing/ft_check_around_elements.c \
					parsing/ft_check_first_last_line.c \
					parsing/ft_check_first_last_line_utils.c \
					parsing/ft_check_walls_and_elements.c \
					parsing/ft_map_carre.c \
					parsing/ft_map_carre_utils.c \
					parsing/ft_free_lst.c 

######################### object files ###############################

OBJS			= $(SRCS:.c=.o)

########################### variables #################################

NAME			= cube

LINK			= -framework Cocoa -framework OpenGL -framework IOKit

LIBS			= MLX42/libmlx42.a -lglfw3

CC				= cc
CFLAGS			= -g -fsanitize=address -Ofaster

############################# rules ###################################

all				: $(NAME)

%.o				: %.c cube.h
	$(CC) -c $< -o $@

$(NAME)			: $(OBJS)
	$(CC) $(OBJS) $(LINK) -o $(NAME) $(LIBS)

clean			:
	rm -rf $(OBJS)

fclean			: clean
	rm -rf $(NAME)

re				: fclean all
