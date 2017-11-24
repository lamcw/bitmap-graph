CC = gcc
CFLAGS = -Wall -Werror -g
LIBS = -lm
# C files
SRC = $(wildcard src/*.c)
$(info source files are [${SRC}])
# object files
OBJ = $(patsubst src/%.c,obj/%.o,$(SRC))
$(info object files are [${OBJ}])

test_graph: test/test.c obj/graph.o
	$(CC) $(CFLAGS) $(LIBS) $^ -o t

obj/%.o: $(SRC)
	$(CC) $(CFLAGS) $(LIBS) -c $^ -o $@

.PHONY: clean
clean:
	$(RM) $(OBJ) test.o src/core t
