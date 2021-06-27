DEBUG = 0
CFLAGS = -DNDEBUG -MMD -O2
ifeq ($(DEBUG), 1)
	CFLAGS = -g -Wall -Werror -Wextra -DDEBUG
endif

LIB_FOLDER = ./lib
LIB_SRCS = ./src/readtrmin_new.c ./src/util/str_util.c
LIB_OBJS = $(LIB_SRCS:%.c=%.o)
LIB_DEPS = $(LIB_OBJS:%.o=%.d)
LIB_NAME = libreadtrmin.so
LIB_FILE = $(LIB_FOLDER)/$(LIB_NAME)

all: readtrmin install

.PHONY: clean_all
clean_all: clean uninstall

.PHONY: readtrmin
readtrmin: make_lib_folder $(LIB_FILE)

.PHONY: make_lib_folder
make_lib_folder:
	mkdir lib

$(LIB_FILE): $(LIB_OBJS)
	$(CC) -shared -fPIC -o $@ $^

-include ($(LIB_DEPS))

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: install
install: uninstall
	cp $(LIB_FILE) $(LD_LIBRARY_PATH)

.PHONY: uninstall
uninstall:
	$(RM) $(LD_LIBRARY_PATH)/$(LIB_NAME)

.PHONY: clean
clean:
	$(RM) $(LIB_OBJS) $(LIB_DEPS) $(LIB_FILE)
