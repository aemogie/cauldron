CC := gcc
CFLAGS ?= -O
EXAMPLE ?= src/main.c
# if we're formatting c/h files, use clang-format
build/fmt/%.c: FMT ?= clang-format -i
build/fmt/%.h: FMT ?= clang-format -i

# force evaluate to not recursively define
build/obj/%.o: CFLAGS := -c $(CFLAGS)
build/asm/%.s: CFLAGS := -S -fverbose-asm $(CFLAGS)
build/pp/%.c: CFLAGS := -E $(CFLAGS)
build/bin/%: CFLAGS := -g $(CFLAGS)

.PHONY: all compile run format clean clangd

.DEFAULT_GOAL: compile
compile: build/bin/$(EXAMPLE:src/%.c=%)

run: build/bin/$(EXAMPLE:src/%.c=%)
	@$<

format: $(subst src/,build/fmt/,$(wildcard src/*.c src/*.h))

clean: | build/
	rm -r build

clangd: # just piggypack off the guix stuff below
	clangd

# different compilations (.o is just there for looks currently)
build/obj/%.o: src/%.c | build/obj/
	$(CC) $(CFLAGS) $^ -o $@
build/pp/%.c: src/%.c | build/pp/
	$(CC) $(CFLAGS) $^ -o $@
build/asm/%.s: src/%.c | build/asm/
	$(CC) $(CFLAGS) $^ -o $@
build/bin/%: src/%.c | build/bin/
	$(CC) $(CFLAGS) $^ -o $@

# touch a file in `build/fmt` so that make knows when it last
# formatted
# https://www.gnu.org/software/make/manual/html_node/Empty-Targets.html
build/fmt/%.c: src/%.c | build/fmt/
	$(FMT) $<
	@touch $@
build/fmt/%.h: src/%.h | build/fmt/
	$(FMT) $<
	@touch $@

# build directories
build/:
	@mkdir $@
	@echo "*" > $@/.gitignore
build/fmt/:
	@mkdir $@
build/obj/: | build/
	@mkdir $@
build/pp/: | build/
	@mkdir $@
build/asm/: | build/
	@mkdir $@
build/bin/: | build/
	@mkdir $@

ifneq ($(shell command -v guix),)
ifeq ($(GUIX_MANIFEST_LOADED),)
# TODO: lock channels
define code
(use-modules (ice-9 textual-ports))
(define cmdline (call-with-input-file "/proc/self/cmdline" get-string-all))
(define cmdline (string-tokenize cmdline))
(define wrapped (cons* "guix" "shell" "-m" "manifest.scm" "--" cmdline))
(setenv "GUIX_MANIFEST_LOADED" "1")
(apply execlp (car wrapped) wrapped)
endef
Makefile: force
	$(guile $(code))
force: ;
endif
endif
