# ######################### source files ###############################

# SRCS			= 	main.c \
# 					ft_split.c \
# 					ft_move_plr.c \
# 					ft_cast_rays.c \
# 					ft_mini_map.c \
# 					ft_rendering.c \
# 					ft_intersection.c \
# 					ft_face_list.c \
# 					ft_check_next.c \
# 					ft_door_ctl.c \
# 					ft_gun_sprite.c \
# 					cube_utils.c \
# 					ft_get_im.c \
# 					bonus/parsing/ft_read_map_bonus.c \
# 					bonus/parsing/ft_check_textures_bonus.c \
# 					bonus/parsing/ft_check_colors_bonus.c \
# 					bonus/parsing/ft_check_colors_utils_bonus.c \
# 					bonus/parsing/ft_get_next_line_bonus.c \
# 					bonus/parsing/ft_get_next_line_utils_bonus.c \
# 					bonus/parsing/ft_extract_map_bonus.c \
# 					bonus/parsing/ft_get_input_bonus.c \
# 					bonus/parsing/ft_check_map_bonus.c \
# 					bonus/parsing/ft_check_map_utils_bonus.c \
# 					bonus/parsing/ft_check_around_elements_bonus.c \
# 					bonus/parsing/ft_check_first_last_line_bonus.c \
# 					bonus/parsing/ft_check_first_last_line_utils_bonus.c \
# 					bonus/parsing/ft_check_walls_and_elements_bonus.c \
# 					bonus/parsing/ft_map_carre_bonus.c \
# 					bonus/parsing/ft_map_carre_utils_bonus.c \
# 					bonus/parsing/ft_free_lst_bonus.c \
# 					mandatory/parsing/ft_read_map.c \
# 					mandatory/parsing/ft_check_textures.c \
# 					mandatory/parsing/ft_check_colors.c \
# 					mandatory/parsing/ft_check_colors_utils.c \
# 					mandatory/parsing/ft_get_next_line.c \
# 					mandatory/parsing/ft_get_next_line_utils.c \
# 					mandatory/parsing/ft_extract_map.c \
# 					mandatory/parsing/ft_get_input.c \
# 					mandatory/parsing/ft_check_map.c \
# 					mandatory/parsing/ft_check_map_utils.c \
# 					mandatory/parsing/ft_check_around_elements.c \
# 					mandatory/parsing/ft_check_first_last_line.c \
# 					mandatory/parsing/ft_check_first_last_line_utils.c \
# 					mandatory/parsing/ft_check_walls_and_elements.c \
# 					mandatory/parsing/ft_map_carre.c \
# 					mandatory/parsing/ft_map_carre_utils.c \
# 					mandatory/parsing/ft_free_lst.c 

# ######################### object files ###############################

# OBJS			= $(SRCS:.c=.o)

# ########################### variables #################################

# NAME			= cube_bonus

# LINK			= -framework Cocoa -framework OpenGL -framework IOKit

# LIBS			= MLX42/libmlx42.a -lglfw3

# CC				= cc
# CFLAGS			= -g -fsanitize=address -Ofaster

# ############################# rules ###################################

# all				: $(NAME)

# %.o				: %.c cube.h
# 	$(CC) -c $< -o $@

# $(NAME)			: $(OBJS)
# 	$(CC) $(OBJS) $(LINK) -o $(NAME) $(LIBS)

# clean			:
# 	rm -rf $(OBJS)

# fclean			: clean
# 	rm -rf $(NAME)

# re				: fclean all



######################### source files ###############################

MANDATORY_SRCS	= 	mandatory/main.c \
					mandatory/ft_split.c \
					mandatory/ft_move_plr.c \
					mandatory/ft_cast_rays.c \
					mandatory/ft_mini_map.c \
					mandatory/ft_rendering.c \
					mandatory/ft_intersection.c \
					mandatory/ft_face_list.c \
					mandatory/ft_check_next.c \
					mandatory/ft_door_ctl.c \
					mandatory/ft_gun_sprite.c \
					mandatory/cube_utils.c \
					mandatory/ft_get_im.c \
					mandatory/parsing/ft_read_map.c \
					mandatory/parsing/ft_check_textures.c \
					mandatory/parsing/ft_check_colors.c \
					mandatory/parsing/ft_check_colors_utils.c \
					mandatory/parsing/ft_get_next_line.c \
					mandatory/parsing/ft_get_next_line_utils.c \
					mandatory/parsing/ft_extract_map.c \
					mandatory/parsing/ft_get_input.c \
					mandatory/parsing/ft_check_map.c \
					mandatory/parsing/ft_check_map_utils.c \
					mandatory/parsing/ft_check_around_elements.c \
					mandatory/parsing/ft_check_first_last_line.c \
					mandatory/parsing/ft_check_first_last_line_utils.c \
					mandatory/parsing/ft_check_walls_and_elements.c \
					mandatory/parsing/ft_map_carre.c \
					mandatory/parsing/ft_map_carre_utils.c \
					mandatory/parsing/ft_free_lst.c

BONUS_SRCS		=	bonus/main.c \
					bonus/ft_split.c \
					bonus/ft_move_plr.c \
					bonus/ft_cast_rays.c \
					bonus/ft_mini_map.c \
					bonus/ft_rendering.c \
					bonus/ft_intersection.c \
					bonus/ft_face_list.c \
					bonus/ft_check_next.c \
					bonus/ft_door_ctl.c \
					bonus/ft_gun_sprite.c \
					bonus/cube_utils.c \
					bonus/ft_get_im.c \
					bonus/parsing/ft_read_map_bonus.c \
					bonus/parsing/ft_check_textures_bonus.c \
					bonus/parsing/ft_check_colors_bonus.c \
					bonus/parsing/ft_check_colors_utils_bonus.c \
					bonus/parsing/ft_get_next_line_bonus.c \
					bonus/parsing/ft_get_next_line_utils_bonus.c \
					bonus/parsing/ft_extract_map_bonus.c \
					bonus/parsing/ft_get_input_bonus.c \
					bonus/parsing/ft_check_map_bonus.c \
					bonus/parsing/ft_check_map_utils_bonus.c \
					bonus/parsing/ft_check_around_elements_bonus.c \
					bonus/parsing/ft_check_first_last_line_bonus.c \
					bonus/parsing/ft_check_first_last_line_utils_bonus.c \
					bonus/parsing/ft_check_walls_and_elements_bonus.c \
					bonus/parsing/ft_map_carre_bonus.c \
					bonus/parsing/ft_map_carre_utils_bonus.c \
					bonus/parsing/ft_free_lst_bonus.c

MANDATORY_OBJS	= $(MANDATORY_SRCS:.c=.o)
BONUS_OBJS		= $(BONUS_SRCS:.c=.o)

########################### variables #################################

NAME_MANDATORY	= cube
NAME_BONUS		= cube_bonus

LINK			= -framework Cocoa -framework OpenGL -framework IOKit
LIBS			= MLX42/libmlx42.a -lglfw3

CC				= cc

############################# rules ###################################

all				: $(NAME_MANDATORY)

bonus			: $(NAME_BONUS)

%.o				: %.c cube.h
	$(CC) -c $< -o $@

$(NAME_MANDATORY)	: $(MANDATORY_OBJS)
	$(CC) $(MANDATORY_OBJS) $(LINK) -o $(NAME_MANDATORY) $(LIBS)

$(NAME_BONUS)		: $(BONUS_OBJS)
	$(CC) $(BONUS_OBJS) $(LINK) -o $(NAME_BONUS) $(LIBS)

clean			:
	rm -rf $(MANDATORY_OBJS) $(BONUS_OBJS)

fclean			: clean
	rm -rf $(NAME_MANDATORY) $(NAME_BONUS)

re				: fclean all
