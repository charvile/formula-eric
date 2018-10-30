CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99 -pedantic -g

OBJS=src/formulaone.o src/path_finder.o src/path_finder_2.o src/utilities.o src/list.o #FIXME: add your obj files here
OBJS_CHECK=tests/check.o tests/utils.o
OBJS_GHOST=tests/ghost.o tests/utils.o

VIEWER=FormulaOne.exe
CHECKER=check
GHOST=ghost
LIB=libformulaone.so

MAP_PATH=maps/lvl1_simple.frc

all: $(LIB)

$(LIB): CFLAGS += -fPIC
$(LIB): LDFLAGS += -shared
$(LIB): $(OBJS)
	$(LINK.c) -o $@ $^

run: $(LIB)
	cp $(LIB) viewer/
	cd viewer && mono $(VIEWER)

$(CHECKER): LDFLAGS += -Wl,-rpath,.:viewer
$(CHECKER): LDLIBS += -L. -Lviewer -lformulaone -lformulaonecontrol -lm
$(CHECKER): CPPFLAGS += -Isrc
$(CHECKER): $(LIB) $(OBJS_CHECK)
	$(LINK.c) -o $@ $(OBJS_CHECK) $(LDLIBS)

$(GHOST): LDFLAGS += -Wl,-rpath,.:viewer
$(GHOST): LDLIBS += -L. -Lviewer -lformulaone -lformulaonecontrol -lm
$(GHOST): CPPFLAGS += -Isrc
$(GHOST): $(LIB) $(OBJS_GHOST)
	$(LINK.c) -o $@ $(OBJS_GHOST) $(LDLIBS)

test : $(CHECKER)
	./$(CHECKER) $(MAP_PATH)

clean:
	$(RM) $(LIB) $(OBJS) $(OBJS_CHECK) $(OBJS_GHOST) $(CHECKER)

.PHONY: all run clean
