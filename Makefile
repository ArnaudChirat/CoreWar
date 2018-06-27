# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achirat <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/26 11:41:55 by achirat           #+#    #+#              #
#    Updated: 2018/06/27 00:51:11 by lbelda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
FLAGS=-Wall -Wextra

ifneq ($(NOERR),yes)
	FLAGS += -Werror
endif

ifeq ($(FSAN),yes)
	FLAGS += -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
endif

ASM_DIR=asm/
ASM_NAME=asm
COREWAR_H=corewar.h
ASM_H=asm.h
COREWAR_DIR=corewar/
COREWAR_NAME=corewar
VISU_DIR=visu/
INSTRUCTIONS_PATH=Instructions/
LIBC=libft/libft.a

PATH_SRC=srcs/
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
				 ft_init_data.c \
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

SRC_ASM=$(addprefix $(PATH_SRC)$(ASM_DIR), $(SRC_FILE_ASM))
SRC_COREWAR=$(addprefix $(PATH_SRC)$(COREWAR_DIR), $(SRC_FILE_COREWAR))
SRC_INSTRUCTIONS= $(addprefix $(PATH_SRC)$(COREWAR_DIR)$(INSTRUCTIONS_PATH), $(SRC_FILE_INSTRUCTIONS))

SRC_DIR_VISU_INIT=init/
SRC_FILE_VISU_INIT=init_visu.c \
				   init_matrices.c init_sound.c init_controls.c \
				   init_scene.c\
				   init_text.c init_text_info.c create_text_data.c \
				   init_3d_alphabet.c init_text_utils.c str_to_mesh.c \
				   init_arena.c init_arena_data.c create_arena_mesh.c \
				   init_counters.c create_counter_mesh.c \
				   init_uniforms.c
SRC_VISU_INIT=$(addprefix $(SRC_DIR_VISU_INIT), $(SRC_FILE_VISU_INIT))

SRC_DIR_VISU_RENDER=render/
SRC_FILE_VISU_RENDER=render.c render_arena.c render_counters.c \
					 update_text_info.c render_text.c \
					 update_clock.c update_camera.c update_uniforms.c
SRC_VISU_RENDER=$(addprefix $(SRC_DIR_VISU_RENDER), $(SRC_FILE_VISU_RENDER))

SRC_DIR_VISU_CONTROLS=controls/
SRC_FILE_VISU_CONTROLS=handle_events.c \
					   kb_rot.c kb_speed.c kb_misc.c \
					   ps3_trs.c ps3_speed.c
SRC_VISU_CONTROLS=$(addprefix $(SRC_DIR_VISU_CONTROLS), $(SRC_FILE_VISU_CONTROLS))

SRC_DIR_VISU_SOUND=sound/
SRC_FILE_VISU_SOUND=update_fft.c sound_utils.c
SRC_VISU_SOUND=$(addprefix $(SRC_DIR_VISU_SOUND), $(SRC_FILE_VISU_SOUND))

SRC_DIR_VISU_UTILS=utils/
SRC_FILE_VISU_UTILS=ogl_utils.c build_ogl_program.c obj_parser.c \
					protec.c clean.c clean_scene.c clean_utils.c error.c
SRC_VISU_UTILS=$(addprefix $(SRC_DIR_VISU_UTILS), $(SRC_FILE_VISU_UTILS))

SRC_DIR_VISU=$(addprefix $(PATH_SRC), $(addprefix $(COREWAR_DIR), $(VISU_DIR)))
SRC_VISU=$(addprefix $(SRC_DIR_VISU), $(SRC_VISU_INIT)) \
		 $(addprefix $(SRC_DIR_VISU), $(SRC_VISU_RENDER)) \
		 $(addprefix $(SRC_DIR_VISU), $(SRC_VISU_CONTROLS)) \
		 $(addprefix $(SRC_DIR_VISU), $(SRC_VISU_SOUND)) \
		 $(addprefix $(SRC_DIR_VISU), $(SRC_VISU_UTILS))

OBJ_ASM=$(SRC_ASM:.c=.o)
OBJ_COREWAR=$(SRC_COREWAR:.c=.o)
OBJ_INSTRUCTIONS=$(SRC_INSTRUCTIONS:.c=.o)
OBJ_VISU=$(SRC_VISU:.c=.o)

INC_DIR=inc/
INC_FILES=asm.h asm_struct.h \
		  vm.h vm_struc.h \
		  op.h \
		  visu.h v_controls.h v_matrices.h v_sound.h \
		  v_ogl_utils.h v_common.h v_obj_parser.h
INC=$(addprefix $(INC_DIR), $(INC_FILES))

LIB_PATH=libft/
LIBFT_INCDIR=$(addprefix $(LIB_PATH), includes/)
LIBFT_INCFILES=ft_printf.h libft.h
LIBFT_INC=$(addprefix $(LIBFT_INCDIR), $(LIBFT_INCFILES))
LIB_NAME=ft

LIBFTMT_DIR=libftmath/
LIBFTMT_LIB=libftmath.a
LIBFTMT_LK=ftmath
LIBFTMT_INCDIR=$(LIBFTMT_DIR)
LIBFTMT_INCFILES=libftmath.h
LIBFTMT_INC=$(addprefix $(LIBFTMT_INCDIR), $(LIBFTMT_INCFILES))
LIBFTMT=$(addprefix $(LIBFTMT_DIR), $(LIBFTMT_LIB))

NCURSE=ncurses
NCURSE_PATH=ncurses

SDL_ROOT=sdl2/
SDL_LIBROOT=lib/
SDL_LIB=libSDL2.a
SDL_INCROOT=include/SDL2/
SDL_SRCROOT=sources/
SDL_LK=SDL2
ORIGIN=\$$ORIGIN/
SDL_SRCDIR=$(addprefix $(SDL_ROOT), $(SDL_SRCROOT))
SDL_INCDIR=$(addprefix $(SDL_ROOT), $(SDL_INCROOT))
SDL_LIBDIR=$(addprefix $(SDL_ROOT), $(SDL_LIBROOT))
SDL_RPATH=$(addprefix $(ORIGIN), $(SDL_LIBDIR))
SDL=$(addprefix $(SDL_LIBDIR), $(SDL_LIB))

FMOD_DIR=fmod/
FMOD_LK=fmodL

INT=install_name_tool -change
MAKE=make

LIB_FLAGS_COREWAR=-L$(LIB_PATH) -l$(LIB_NAME) -L$(LIBFTMT_DIR) -l$(LIBFTMT_LK) \
				  -L$(SDL_LIBDIR) -l$(SDL_LK) -lm -L$(NCURSE_PATH) -l$(NCURSE) \
				  -L$(FMOD_DIR) -l$(FMOD_LK)

ALL_INC=$(INC) $(LIBFT_INC)
-I_ALL_INC=-I$(INC_DIR) -I$(LIBFT_INCDIR) -I$(LIBFTMT_INCDIR) \
			-I$(SDL_INCDIR) -I$(FMOD_DIR)

UNAME:=$(shell uname -s)
ifeq ($(UNAME),Darwin)
	LIB_FLAGS_COREWAR+= -framework OpenGL
else
	LIB_FLAGS_COREWAR+= -lpthread -lGL -lGLU -lGLEW -Wl,-rpath,$(SDL_RPATH)
endif

all : $(ASM_NAME) $(COREWAR_NAME)

$(LIBC):
	@make -C $(LIB_PATH)

$(LIBFTMT):
	$(MAKE) -C $(LIBFTMT_DIR)

$(SDL):
	cd $(SDL_SRCDIR) && ./configure --prefix=$$PWD/../
	$(MAKE) -C $(SDL_SRCDIR) install
	git update-index --skip-worktree sdl2/sources/include/SDL_config.h

$(ASM_NAME): $(OBJ_ASM) $(LIBC)
	gcc -o $(ASM_NAME) $(FLAGS) $(OBJ_ASM) -L$(LIB_PATH) -l$(LIB_NAME)
	@echo "\033[1;34m$(ASM_NAME)\033[1;32m...compiled\t\t✓\033[0m"

$(COREWAR_NAME) : $(LIBC) $(LIBFTMT) $(SDL) $(OBJ_COREWAR) \
				$(OBJ_VISU) $(OBJ_INSTRUCTIONS)
	gcc $(FLAGS) -o $(COREWAR_NAME) $(OBJ_COREWAR) \
		$(OBJ_VISU) $(OBJ_INSTRUCTIONS) \
		$(-I_ALL_INC) $(LIB_FLAGS_COREWAR)
	$(INT) @rpath/libfmodL.dylib $(FMOD_DIR)libfmodL.dylib $(COREWAR_NAME)
	@echo "\033[1;34m$(COREWAR_NAME)\033[1;32m...compiled\t\t✓\033[0m"

%.o : %.c $(ALL_INC)
	$(CC) $(FLAGS) -o $@ $(-I_ALL_INC) -c $<

clean:
	rm -rf $(OBJ_ASM) $(OBJ_COREWAR) $(OBJ_INSTRUCTIONS) $(OBJ_VISU)
	@make clean -C $(LIB_PATH)
	@echo "\033[1;34m$(COREWAR_NAME)\033[1;33m obj files removed\t\033[1;31m✓\033[0m"
	@echo "\033[1;34m$(ASM_NAME)\033[1;33m obj files removed\t\033[1;31m✓\033[0m"

fclean : clean
	@rm -rf $(ASM_NAME) $(COREWAR_NAME)
	@make fclean -C $(LIB_PATH)
	@$(MAKE) -C $(SDL_SRCDIR) clean
	@$(MAKE) -C $(SDL_SRCDIR) uninstall
	@rm -rf $(SDL_ROOT)bin
	@rm -rf $(SDL_ROOT)include
	@rm -rf $(SDL_ROOT)lib
	@rm -rf $(SDL_ROOT)share
	@echo "\033[1;34m$(COREWAR_NAME)\033[1;33m exec removed\t\t\033[1;31m✓\033[0m"
	@echo "\033[1;34m$(ASM_NAME)\033[1;33m exec removed\t\t\033[1;31m✓\033[0m"

re:
	@make fclean
	@make
