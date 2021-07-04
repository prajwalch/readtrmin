DEBUG = 0
CFLAGS = -MMD -std=c11 -I./include/readtrmin/

ifeq ($(DEBUG), 1)
	CFLAGS += -g -Wall -Werror -Wextra -DDEBUG
else
	CFLAGS += -DNDEBUG -O2
endif

LDFLAGS = -shared

ifeq ($(PREFIX),)
	PREFIX := /usr/local
endif

BUILD_DIR = build
SRC_DIR = src

LIB_SRCS = $(SRC_DIR)/readtrmin.c \
					 $(SRC_DIR)/str_util.c
LIB_HEADER = readtrmin.h

LIB_OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(LIB_SRCS))
LIB_DEPS = $(patsubst %.o, %.d, $(LIB_OBJS))

TARGET = readtrmin
LIB_NAME = lib$(TARGET).so
LIB_FILE = $(BUILD_DIR)/$(LIB_NAME)

LIB_INSTALL_PATH = $(PREFIX)/lib/readtrmin
LIB_HEADER_PATH = $(PREFIX)/include/readtrmin

all: readtrmin install

.PHONY: clean_all
clean_all: clean

.PHONY: readtrmin
readtrmin: make_build_dir $(LIB_FILE)

.PHONY: make_build_dir
make_build_dir:
	@if [ ! -d $(BUILD_DIR) ]; then mkdir $(BUILD_DIR); fi

$(LIB_FILE): $(LIB_OBJS)
	$(CC) $(LDFLAGS) -fPIC -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

-include ($(LIB_DEPS))

.PHONY: install
install:
	@if [ ! -f $(LIB_FILE) ]; then \
		echo "installation failed"; \
		echo "$(LIB_NAME) not found"; \
		echo "run 'make readtrmin' to build it"; \
	else \
		if [ ! -d $(LIB_INSTALL_PATH) ]; then \
			mkdir $(LIB_INSTALL_PATH); \
		fi; \
		cp $(LIB_FILE) $(LIB_INSTALL_PATH); \
		echo "installation successful"; \
	fi

.PHONY: install_header
install_header:
	cp $(LIB_HEADER) $(PREFIX)/include

.PHONY: uninstall
uninstall:
	$(RM) -r $(LIB_INSTALL_PATH)
	$(RM) -r $(LIB_HEADER_PATH)

.PHONY: clean
clean:
	$(RM) $(LIB_OBJS) $(LIB_DEPS) $(LIB_FILE)
