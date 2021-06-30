DEBUG = 0
CFLAGS = -MMD -std=c11

ifeq ($(DEBUG), 1)
	CFLAGS += -g -Wall -Werror -Wextra -DDEBUG
else
	CFLAGS += -DNDEBUG -O2
endif

LDFLAGS = -shared

ifeq ($(PREFIX),)
	PREFIX := /usr/local
endif

BUILD_DIR = ./build
SRC_DIR = ./src
LIB_SRCS = $(SRC_DIR)/readtrmin.c \
					 $(SRC_DIR)/util/str_util.c
LIB_HEADER = $(SRC_DIR)/readtrmin.h
LIB_OBJS = $(LIB_SRCS:%.c=%.o)
LIB_DEPS = $(LIB_OBJS:%.o=%.d)

NAME = readtrmin
LIB_NAME = lib$(NAME).so
LIB_FILE = $(BUILD_DIR)/$(LIB_NAME)

all: readtrmin install

.PHONY: clean_all
clean_all: clean

.PHONY: readtrmin
readtrmin: make_build_dir $(LIB_FILE)

.PHONY: make_build_dir
make_build_dir:
	if [ ! -d $(BUILD_DIR) ]; then mkdir $(BUILD_DIR); fi

$(LIB_FILE): $(LIB_OBJS)
	$(CC) $(LDFLAGS) -fPIC -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

-include ($(LIB_DEPS))

.PHONY: install
install:
	cp $(LIB_FILE) $(PREFIX)/lib

.PHONY: install_header
install_header:
	cp $(LIB_HEADER) $(PREFIX)/include

.PHONY: uninstall
uninstall:
	$(RM) $(PREFIX)/lib/$(LIB_NAME)
	$(RM) $(PREFIX)/include/$(LIB_HEADER)

.PHONY: clean
clean:
	$(RM) $(LIB_OBJS) $(LIB_DEPS) $(LIB_FILE)
