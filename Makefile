CC := gcc
CFLAGS ?= -Werror -Wall
EXAMPLE ?= src/main.c

.PHONY: all compile run format clean

.DEFAULT_GOAL: all
all: format compile

compile: build/bin/$(EXAMPLE:src/%.c=%)

run: build/bin/$(EXAMPLE:src/%.c=%)
	@$<

format: $(subst src/,build/fmt/,$(wildcard src/*.c src/*.h))

clean:
ifneq ($(wildcard build/),)
	rm -r build/
endif

define make_dir
$(let this, $(strip $(1:/=)),
$(let parent, $(dir $(this)),
# === #
$(if $(this:.=), # stop if we're at the toplevel
$(if $(findstring $(this),$(__make_dir_visited)),, # or if we've visited
$(this)/: | $(parent:./=)
	@mkdir $(this)
	@echo "*" >> $(this)/.gitignore
__make_dir_visited += $(this)
# recurse
$(call make_dir, $(parent))))))
endef

define build_kind
$(let target, $(strip $(1)),
$(let flags, $(strip $(2)),
$(let build_dir, $(dir $(target)),
# === #
$(target): src/%.c | $(build_dir)
	$(CC) $(flags) $(CFLAGS) $$^ -o $$@
$(call make_dir, $(build_dir)))))
endef

# todo: figure out how to format nested files
define format_kind
$(let target, $(strip $(1)),
$(let formatter, $(strip $(2)),
# === #
# the target is a marker
# https://www.gnu.org/software/make/manual/html_node/Empty-Targets.html
build/fmt/$(target): src/$(target) | build/fmt/
	$(formatter) $$^
	@touch $$@
$(call make_dir, build/fmt/)))
endef

$(eval $(call build_kind, build/obj/%.o, -c))
$(eval $(call build_kind, build/asm/%.s, -S))
$(eval $(call build_kind, build/pp/%.c, -E))
$(eval $(call build_kind, build/bin/%, -g))

# $(eval $(call format_kind, %.c, clang-format -i))
$(eval $(call format_kind, %.h, clang-format -i))
