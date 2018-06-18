# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clanglai <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/07 15:30:47 by clanglai          #+#    #+#              #
#    Updated: 2018/06/18 18:34:14 by achirat          ###   ########.fr        #
#    Updated: 2018/06/07 14:11:10 by ccorsin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
FLAGS=-Wall -Wextra -Werror
ASM_NAME=asm
COREWAR_H=corewar.h
ASM_H=asm.h
COREWAR_NAME=corewar
INSTRUCTIONS_PATH=Instructions
LIBC=libft/libft.a
LIBG=minilibx/mlx.a
NCURSE=lncurses
LIB_PATH =libft
NCURSE_PATH=ncurses
LIBG_PATH=minilibx
LIBG_NAME=lmlx
PATH_SRC=srcs
SRC_FILE_ASM=asm.c \
			 ft_error.c \
			 ft_error_2.c \
			 ft_parse.c \
			 ft_aux.c \
			 ft_aux_2.c \
			 ft_parse_2.c \
			 ft_check_parse.c \
			 ft_write_file.c \
			 ft_free.c \
			 ft_check_parse_2.c \
			 ft_get_instructions_2.c \
			 ft_aux_3.c
SRC_FILE_COREWAR=ft_init_process.c \
				 ft_control_define.c \
				 ft_players.c \
				 ft_print.c \
				 tools.c \
				 tools_2.c \
				 main.c \
				 ft_game.c \
				 ft_process.c \
				 ft_free.c \
				 ft_fight.c \
				 ft_players_3.c \
				 ft_players_2.c \
				 ft_draw.c \
				 ft_draw_2.c
SRC_FILE_INSTRUCTIONS= ft_check_op.c \
					   	ft_check_op2.c \
						ft_aff.c \
						ft_add.c \
						ft_and.c \
						ft_ld.c \
						ft_ldi.c \
						ft_lld.c \
						ft_lldi.c \
						ft_st.c \
						ft_sti.c \
						ft_fork.c \
						ft_lfork.c \
						ft_sub.c \
						ft_zjmp.c \
						ft_or.c \
						ft_xor.c \
						ft_live.c
SRC_INCLUDES_FILE= inc/asm.h \
				   inc/asm_struct.h \
				   inc/corewar.h \
				   inc/op.h \
				   inc/vm.h \
				   inc/vm_define_list.h \
				   inc/vm_struc.h
SRC_ASM= $(addprefix $(PATH_SRC)/$(ASM_NAME)/, $(SRC_FILE_ASM))
SRC_COREWAR= $(addprefix $(PATH_SRC)/$(COREWAR_NAME)/, $(SRC_FILE_COREWAR))
SRC_INSTRUCTIONS= $(addprefix $(PATH_SRC)/$(COREWAR_NAME)/$(INSTRUCTIONS_PATH)/, $(SRC_FILE_INSTRUCTIONS))
OBJ_ASM=$(SRC_ASM:.c=.o)
OBJ_COREWAR=$(SRC_COREWAR:.c=.o)
OBJ_INSTRUCTIONS=$(SRC_INSTRUCTIONS:.c=.o)

all : $(LIBC) $(ASM_NAME) $(COREWAR_NAME)

$(LIBC):
	@make -C $(LIB_PATH)

$(ASM_NAME): $(OBJ_ASM)
	@gcc -o $(ASM_NAME) $(FLAGS) $(OBJ_ASM) -L$(LIB_PATH) $(LIBC)
	@echo "\033[1;34m$(ASM_NAME)\033[1;32m...compiled\t\t✓\033[0m"

$(COREWAR_NAME) : $(OBJ_COREWAR) $(OBJ_INSTRUCTIONS)
	@gcc $(FLAGS) -o $(COREWAR_NAME) $(FLAGS) $(OBJ_COREWAR) $(OBJ_INSTRUCTIONS) \
	-L$(LIB_PATH) -L$(NCURSE_PATH) -$(NCURSE) $(LIBC)
	@echo "\033[1;34m$(COREWAR_NAME)\033[1;32m...compiled\t\t✓\033[0m"

%.o : %.c $(SRC_INCLUDES_FILE)
	@$(CC) $(FLAGS) -o $@ -c $<

.PHONY : all, fclean, clean, re

clean:
	rm -rf $(OBJ_ASM) $(OBJ_COREWAR) $(OBJ_INSTRUCTIONS)
	@make clean -C $(LIB_PATH)
	@echo "\033[1;34m$(COREWAR_NAME)\033[1;33m obj files removed\t\033[1;31m✓\033[0m"
	@echo "\033[1;34m$(ASM_NAME)\033[1;33m obj files removed\t\033[1;31m✓\033[0m"

fclean : clean
	@rm -rf $(ASM_NAME) $(COREWAR_NAME)
	@make fclean -C $(LIB_PATH)
	@echo "\033[1;34m$(COREWAR_NAME)\033[1;33m exec removed\t\t\033[1;31m✓\033[0m"
	@echo "\033[1;34m$(ASM_NAME)\033[1;33m exec removed\t\t\033[1;31m✓\033[0m"

re:
	@make fclean
	@make
