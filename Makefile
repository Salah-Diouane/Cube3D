######################### source files ###############################

MANDA_GAME		= manda_game

MANDA_PARSER	= manda_parser

BONUS_GAME		= bonus_game

BONUS_PARSER	= bonus_parser

MANDA_GAME_SRCS		=	$(MANDA_GAME)/main.c \
						$(MANDA_GAME)/ft_intersection.c \
						$(MANDA_GAME)/ft_face_list.c \
						$(MANDA_GAME)/ft_clean_up.c \
						$(MANDA_GAME)/ft_texture.c \
						$(MANDA_GAME)/ft_rendering.c  \
						$(MANDA_GAME)/ft_cast_rays.c \
						$(MANDA_GAME)/ft_move_plr.c \
						$(MANDA_GAME)/cube_utils.c \
						$(MANDA_GAME)/ft_split.c  \
						$(MANDA_GAME)/ft_check_next.c

MANDA_PARSER_SRCS	=	$(MANDA_PARSER)/ft_check_walls_and_elements.c \
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

BONUS_GAME_SRCS		=	$(BONUS_GAME)/main.c \
						$(BONUS_GAME)/ft_intersection.c \
						$(BONUS_GAME)/ft_face_list.c \
						$(BONUS_GAME)/ft_clean_up.c \
						$(BONUS_GAME)/ft_texture.c \
						$(BONUS_GAME)/ft_rendering.c  \
						$(BONUS_GAME)/ft_cast_rays.c \
						$(BONUS_GAME)/ft_move_plr.c \
						$(BONUS_GAME)/cube_utils.c \
						$(BONUS_GAME)/ft_split.c \
						$(BONUS_GAME)/ft_mouse.c \
						$(BONUS_GAME)/ft_door_ctl.c \
						$(BONUS_GAME)/ft_mini_map.c \
						$(BONUS_GAME)/ft_gun_sprite.c \
						$(BONUS_GAME)/ft_check_next.c

BONUS_PARSER_SRCS	=	$(BONUS_PARSER)/ft_check_walls_and_elements_bonus.c \
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

MANDA_GAME_OBJS		=	$(MANDA_GAME_SRCS:%c=%o)
MANDA_PARSER_OBJS	=	$(MANDA_PARSER_SRCS:%c=%o)

BONUS_GAME_OBJS		=	$(BONUS_GAME_SRCS:%c=%o)
BONUS_PARSER_OBJS	=	$(BONUS_PARSER_SRCS:%c=%o)

########################### variables #################################

NAME			= cub3D

# LINK			= -framework Cocoa -framework OpenGL -framework IOKit

LINK			= -lmlx42 -lglfw -lm

# LIBS			= MLX42/libmlx42.a -lglfw3

############################# rules ###################################

all				: $(NAME)


$(MANDA_GAME)/%.o	: $(MANDA_GAME)/%.c ./include/manda.h
	gcc -c $< -o $@

$(MANDA_PARSER)/%.o	: $(MANDA_PARSER)/%.c ./include/manda_parser.h
	gcc -c $< -o $@

$(BONUS_GAME)/%.o	: $(BONUS_GAME)/%.c ./include/bonus.h
	gcc -c $< -o $@ -g -fsanitize=address
	
$(BONUS_PARSER)/%.o	: $(BONUS_PARSER)/%.c ./include/bonus_parser.h
	gcc -c $< -o $@ -g -fsanitize=address

$(NAME)			: $(MANDA_GAME_OBJS) $(MANDA_PARSER_OBJS)
	gcc $(MANDA_GAME_OBJS) $(MANDA_PARSER_OBJS)  $(LINK) $(LIBS) \
		-O3 -ffast-math -o $(NAME)

bonus			: $(BONUS_GAME_OBJS) $(BONUS_PARSER_OBJS)
	gcc $(BONUS_GAME_OBJS) $(BONUS_PARSER_OBJS)  $(LINK) $(LIBS) \
		-O3 -ffast-math -o $(NAME) -g -fsanitize=address

clean			:
	rm -rf $(MANDA_PARSER)/*.o
	rm -rf $(MANDA_GAME)/*.o
	rm -rf $(BONUS_PARSER)/*.o
	rm -rf $(BONUS_GAME)/*.o

fclean			: clean
	rm -rf $(NAME)

re				: fclean all

