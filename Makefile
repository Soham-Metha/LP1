BUILDS := ./builds
CC	   := gcc
CFLAGS := -Wall -Wextra -Werror -Wfatal-errors -Wswitch-enum -pedantic -O3 -std=c99
LIBS   := $(addprefix -I, $(wildcard ./include/*/))

define BUILD_RULE
$1: $2
	@$(CC) $$^ $(CFLAGS) $(LIBS) -o $$@
	@printf "\e[32m		[ BUILD COMPLETED ]\t: [ $$@ ] \e[0m\n\n"
endef

B2:= $(BUILDS)/B2.o
$(eval $(call BUILD_RULE, $(B2),  $(wildcard src/B2/*.c)))
B2: clean $(B2)
	@$(B2)

B1:= $(BUILDS)/B1.o
$(eval $(call BUILD_RULE, $(B1),  $(wildcard src/B1/*.c)))
B1: clean $(B1)
	@$(B1)

clean:
	@rm -rf $(BUILDS)/*.o
	@printf "\e[31m		[ CLEAN COMPLETED ]\t: [ $(BUILDS)/*.o ] \e[0m\n\n"