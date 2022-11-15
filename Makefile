CC := clang
CFLAGS := -Wno-return-stack-address
LDFLAGS :=

SRC := $(wildcard *.c lib/*.c)
# OBJs are under out/ and out/lib directory
OBJ := $(patsubst %.c, out/%.o, $(SRC))
EXE := out/main

.PHONY: all

all: clean out build

# prepare out/ directory
out:
	@mkdir -p out
	@mkdir -p out/lib

# build .c files to .o files
out/%.o: %.c
	@echo "[CC] $< -> $@"
	@$(CC) $(CFLAGS) -c $< -o $@

# build sources in out/ directory
build: $(OBJ)
	@echo "[LD] $^ -> $(EXE)"
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(EXE) $(OBJ)

# clean up
clean:
	@rm -rf out