######################### source files ###############################

MANDA_GAME		= manda_game

MANDA_PARSER	= manda_parser

BONUS_PARSER	= bonus_parser

SRCS_MANDA		=	$(MANDA_GAME)/main.c \
					$(MANDA_GAME)/ft_intersection.c \
					$(MANDA_GAME)/ft_face_list.c \
					$(MANDA_GAME)/ft_clean_up.c \
					$(MANDA_GAME)/ft_texture.c \
					$(MANDA_GAME)/ft_rendering.c  \
					$(MANDA_GAME)/ft_cast_rays.c \
					$(MANDA_GAME)/ft_move_plr.c \
					$(MANDA_GAME)/cube_utils.c \
					$(MANDA_GAME)/ft_split.c  \
					$(MANDA_GAME)/ft_check_next.c  \
					$(MANDA_PARSER)/ft_check_walls_and_elements.c \
					$(MANDA_PARSER)/ft_check_around_elements.c \
					$(MANDA_PARSER)/ft_check_colors_utils.c \
					$(MANDA_PARSER)/ft_check_map_utils.c \
					$(MANDA_PARSER)/ft_check_colors.c \
					$(MANDA_PARSER)/ft_check_map.c \
					$(MANDA_PARSER)/ft_get_input.c \
					$(MANDA_PARSER)/ft_check_textures.c \
					$(MANDA_PARSER)/ft_check_first_last_line.c \
					$(MANDA_PARSER)/ft_get_next_line_utils.c \
					$(MANDA_PARSER)/ft_map_carre_utils.c \
					$(MANDA_PARSER)/ft_get_next_line.c \
					$(MANDA_PARSER)/ft_extract_map.c \
					$(MANDA_PARSER)/ft_map_carre.c \
					$(MANDA_PARSER)/ft_free_lst.c \
					$(MANDA_PARSER)/ft_read_map.c \
					$(MANDA_PARSER)/ft_check_first_last_line_utils.c

SRCS_BONUS		=	$(BONUS_PARSER)/ft_check_walls_and_elements_bonus.c \
					$(BONUS_PARSER)/ft_check_around_elements_bonus.c \
					$(BONUS_PARSER)/ft_check_colors_utils_bonus.c \
					$(BONUS_PARSER)/ft_check_map_utils_bonus.c \
					$(BONUS_PARSER)/ft_check_colors_bonus.c \
					$(BONUS_PARSER)/ft_check_map_bonus.c \
					$(BONUS_PARSER)/ft_get_input_bonus.c \
					$(BONUS_PARSER)/ft_check_textures_bonus.c \
					$(BONUS_PARSER)/ft_check_first_last_line_bonus.c \
					$(BONUS_PARSER)/ft_get_next_line_utils_bonus.c \
					$(BONUS_PARSER)/ft_map_carre_utils_bonus.c \
					$(BONUS_PARSER)/ft_get_next_line_bonus.c \
					$(BONUS_PARSER)/ft_extract_map_bonus.c \
					$(BONUS_PARSER)/ft_map_carre_bonus.c \
					$(BONUS_PARSER)/ft_free_lst_bonus.c \
					$(BONUS_PARSER)/ft_read_map_bonus.c \
					$(BONUS_PARSER)/ft_check_first_last_line_utils_bonus.c

######################### object files ###############################

OBJS_MANDA		= $(SRCS_MANDA:%c=%o)

OBJS_BONUS		= $(SRCS_BONUS:%c=%o)

########################### variables #################################

NAME_MANDA		= cube

NAME_BONUS		= cube_bonus

LINK			= -framework Cocoa -framework OpenGL -framework IOKit

# LINK			= -lmlx42 -lglfw -lm

LIBS			= MLX42/libmlx42.a -lglfw3

############################# rules ###################################

all				: $(NAME_MANDA)

bonus			: $(NAME_BONUS)

%.o				: %.c cube.h
	gcc -c $< -o $@ -O3 -ffast-math -g -fsanitize=address

$(NAME_MANDA)	: $(OBJS_MANDA)
	gcc $(OBJS_MANDA) -o $(NAME_MANDA) $(LINK) $(LIBS) -O3 -ffast-math -g -fsanitize=address

$(NAME_BONUS)	: $(OBJS_BONUS)
	gcc $(OBJS_BONUS) -o $(NAME_BONUS) $(LINK) $(LIBS) -O3 -ffast-math -g -fsanitize=address

clean			:
	rm -rf $(MANDA_PARSER)/*.o
	rm -rf $(MANDA_GAME)/*.o
	rm -rf $(BONUS_PARSER)/*.o

fclean			: clean
	rm -rf $(NAME_MANDA)
	rm -rf $(NAME_BONUS)

re				: fclean all

