# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/28 18:26:57 by gwyman-m          #+#    #+#              #
#    Updated: 2020/03/24 12:59:10 by sts              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM=asm
VM=corewar

FLAGS = -g -O2 -I includes/ -I libft/
LIB = -L libft/ -lft -lncurses

ASM_DIR=src_asm/
VM_DIR=src_vm/

HEADER_VM=includes/corewar.h includes/op.h
HEADER_ASM=includes/assem.h includes/disassem.h includes/op.h

ASM_CFILES= main.c functions.c read_struct.c \
			funct1.c funct2.c funct3.c funct4.c create_list.c checks.c \
			operations.c variables.c functions2.c read_commands.c errors.c \
			code_generator.c checks2.c edgar_func.c edgar_func1.c assembler.c\
			d_functions.c d_functions2.c d_func1.c d_func2.c d_func3.c \
			d_func4.c d_reader.c disassembler.c d_errors.c

VM_CFILES= check.c cmd_add_sub.c cmd_and_or_xor.c cmd_fork.c cmd_funcs.c \
		   cmd_get.c cmd_ld.c cmd_ldi.c cmd_live.c cmd_load.c cmd_st_sti.c \
		   cmd_zjmp_aff.c cursor.c cursor_change_position.c cycle.c \
		   detect_dump_vis_flags.c detect_flags.c detect_n_flag.c do_cmd.c \
		   draw.c error_usage.c fill.c game.c game_with_vis.c \
		   init_champs.c init_ncurses.c init_vm.c main.c mem_buff_print.c \
		   memory_buffer.c valid.c color_mem.c free_game.c

ASM_OFILES= $(ASM_CFILES:%.c=%.o)
VM_OFILES= $(VM_CFILES:%.c=%.o)

ASM_SRC= $(addprefix $(ASM_DIR),$(ASM_CFILES))
ASM_OBJ= $(addprefix $(ASM_DIR),$(ASM_OFILES))

VM_SRC= $(addprefix $(VM_DIR),$(VM_CFILES))
VM_OBJ= $(addprefix $(VM_DIR),$(VM_OFILES))

LIBFT=libft/libft.a

RULE=$(firstword $(MAKECMDGOALS))

.PHONY: all clean fclean re

all: $(ASM) $(VM)

$(ASM): $(LIBFT) $(ASM_OBJ)
	clang $(FLAGS) $(ASM_OBJ) -o $(ASM) $(LIB)

src_asm/%.o: src_asm/%.c $(HEADER_ASM)
	clang -c $(FLAGS) $< -o $@

$(VM): $(LIBFT) $(VM_OBJ)
	clang $(FLAGS) $(VM_OBJ) -o $(VM) $(LIB)

src_vm/%.o: src_vm/%.c $(HEADER_VM)
	clang -c $(FLAGS) $< -o $@

#	@printf "\033[0;32mcorwar files are ready                        \033[0m\n"
#	@printf "\e[?25h\033[0;32mcorwar is ready\033[0m\n"

$(LIBFT):
	@make -C libft/

#	@printf "\e[?25l\033[0;34mcompiling $<\033[0m\033\r"
#	@printf "                                 \r"

clean:
	@rm -f $(ASM_OBJ) $(VM_OBJ)
ifneq ($(RULE),$(filter $(RULE), fclean re))
	@make clean -C libft/
endif
	@echo "\033[0;33mthe src directories are cleaned\033[0m"

fclean: clean
	@make fclean -C libft/
	@rm -f $(ASM) $(VM)
	@echo "\033[0;33mdeleted asm and corewar\033[0m"

re: fclean all
