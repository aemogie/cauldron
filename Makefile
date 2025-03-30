ENV := guix shell -m manifest.scm --

all: format compile

format: main.c cauldron.h
	$(ENV) clang-format -i main.c cauldron.h

compile:
	$(ENV) gcc -O -o main main.c # -O is needed for `inline` to take effect
