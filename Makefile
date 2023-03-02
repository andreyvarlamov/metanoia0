CFLAGS = -g3 -std=c99 -Wall -Wextra -Werror -Wconversion -Wno-unused-parameter
INCLUDE = -Ilib/glad/include -Ilib/glfw/include
LIBS = lib/glad/src/glad.o lib/glfw/src/libglfw3.a -lm
EXE = bin/metanoia

# ------------------------------------------------------------------------------

SOURCES = \
main.c

# ------------------------------------------------------------------------------

.PHONY: all
all: clean bin $(EXE)

libs:
	cd lib/glad && clang -o src/gald.o -I include -c src/glad.c
# cd lib/cglm && cmake . -DCGLM_STATIC=ON && make
	cd lib/glfw && cmake . && make

bin:
	mkdir -p bin

$(EXE):
	clang -o $(EXE) $(addprefix src/,$(SOURCES)) $(CFLAGS) $(INCLUDE) $(LIBS)

.PHONY: run
run: all
	@echo -e "\n---------------------------------\n"
	@$(EXE)

.PHONY: clean
clean:
	rm -rf bin
