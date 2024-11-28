##########
#
#    #
#      #
#  # # #
#
##########

SRC_DIR			=	./src/
HDR_DIR			=	./hdr/
OBJ_DIR			=	./obj/

SRC				=	$(shell find $(SRC_DIR) -type f -name '*.c' -not -path "./src/examples/*")
OBJ				=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
LIB				=	libexceptions.a

HEADERS			=	$(shell find $(HDR_DIR) -name '*.h')

CC				=	gcc
AR				=	ar rc

CFLAGS			=	-Wall -Wextra -Werror -static -O3
CPPFLAGS		=	-D_GNU_SOURCE -I$(HDR_DIR)

EXAMPLES_DIR	=	./src/examples/
EX_OBJ_DIR		=	./obj/examples/
EXAMPLES		=	$(shell find $(EXAMPLES_DIR) -type f -name '*.c')
EXAMPLES_OBJ	=	$(patsubst $(EXAMPLES_DIR)%.c, $(EX_OBJ_DIR)%.o, $(EXAMPLES))

EXAMPLE			=	example

LDLIBS			=	-L. -lexceptions

.PHONY:	all
all:	$(LIB)

.PHONY: dev
dev:
	@echo "[+] Starting dev session"
	@echo Makefile $(SRC) $(HEADERS) | tr ' ' '\n' | entr bash -c 'clear && echo "[+] Change detected, recompiling" && make --no-print-directory re'

$(LIB):	$(OBJ)
	@echo "[+] Compiling $@"
	@$(AR) $@ $(OBJ)

$(EXAMPLE):	$(LIB)	$(EXAMPLES_OBJ)
	@echo "[+] Compiling $@"
	@$(CC) $(LDFLAGS) $(EXAMPLES_OBJ) $(LOADLIBES) $(LDLIBS) -o $@

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
	@mkdir -p $(@D)
	@echo ">> Compiling C object $@"
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

.PHONY:	clean
clean:
	@echo "Removing compiled object directory"
	@rm -rf $(OBJ_DIR)
	@echo "Removing traces"
	@rm -f vgcore*
	@rm -f *.swp
	@rm -f *~

.PHONY:	fclean
fclean:	clean
	@echo "Removing executable"
	@rm -f $(EXAMPLE)
	@rm -f $(LIB)

.PHONY:	re
re:	fclean	all