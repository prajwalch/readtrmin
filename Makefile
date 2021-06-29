DEBUG = 0
CFLAGS = -MMD -std=c11

ifeq ($(DEBUG), 1)
	CFLAGS += -g -Wall -Werror -Wextra -DDEBUG
else
	CFLAGS += -DNDEBUG -O2
endif

LIB_FOLDER = ./lib
LIB_SRCS = ./src/readtrmin.c ./src/util/str_util.c
LIB_OBJS = $(LIB_SRCS:%.c=%.o)
LIB_DEPS = $(LIB_OBJS:%.o=%.d)
LIB_NAME = libreadtrmin.so
LIB_FILE = $(LIB_FOLDER)/$(LIB_NAME)

FALLBACK_LIBRARY_PATH = ~/../usr/lib

all: readtrmin install

.PHONY: clean_all
clean_all: clean uninstall

.PHONY: readtrmin
readtrmin: make_lib_folder $(LIB_FILE)

.PHONY: make_lib_folder
make_lib_folder:
	if [ ! -d $(LIB_FOLDER) ]; then mkdir lib; fi

$(LIB_FILE): $(LIB_OBJS)
	$(CC) -shared -fPIC -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

-include ($(LIB_DEPS))

.PHONY: install
install:
	mv $(LIB_FILE) $(FALLBACK_LIBRARY_PATH)

.PHONY: uninstall
uninstall:
	$(RM) $(LD_LIBRARY_PATH)/$(LIB_NAME)

.PHONY: clean
clean:
	$(RM) $(LIB_OBJS) $(LIB_DEPS) $(LIB_FILE)
	$(RM) -r $(LIB_FOLDER)
