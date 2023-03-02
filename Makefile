CFLAGS = -g3 -std=c99 -Wall -Wextra -Werror -Wconversion
INCLUDE = -Ilib/glad/include -Ilib/cglm/include
EXE = bin/metanoia

# ------------------------------------------------------------------------------

SOURCES = \
main.c

# ------------------------------------------------------------------------------

.PHONY: all
all: bin $(EXE)

libs:
	cd lib/glad && clang -o src/gald.o -I include -c src/glad.c
	cd lib/cglm && cmake . -DCGLM_STATIC=ON && make

bin:
	mkdir -p bin

$(EXE):
	clang -o $(EXE) $(addprefix src/,$(SOURCES)) $(CFLAGS) $(INCLUDE)

.PHONY: run
run: all
	@echo -e "\n---------------------------------\n"
	@$(EXE)

.PHONY: clean
clean:
	rm -rf bin
