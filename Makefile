######################### source files ###############################

SRCS			= 	main.c \
					ft_split.c \
					ft_move_plr.c \
					ft_drop_rays.c \
					ft_rendering.c \
					ft_intersection.c \
					ft_create_list.c

######################### object files ###############################

OBJS			= $(SRCS:%c=%o)

########################### variables #################################

NAME			= cube

LINK			= -lmlx42 -lglfw -lm

############################# rules ###################################

all				: $(NAME)

o%				: %c cube.h
	gcc -c $< -o $@

$(NAME)			: $(OBJS)
	gcc $(OBJS) $(LINK) -o $(NAME) -Ofaster

clean			:
	rm -rf *o

fclean			: clean
	rm -rf $(NAME)

re				: fclean all