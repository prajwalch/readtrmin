CFLAGS = -Wall -Wextra

LIB_SRCS = input_reader.c
LIB_OBJ = input_reader.o

TEST_SRCS = ./test/test.c
TEST_OBJS = ./test/test.o
TEST_DEPS = ./test/test.d
TEST_BIN = ./test/testreader
TEST_CFLAGS = $(CFLAGS) -MMD -I./

all: inputreader test

test: $(TEST_BIN)

inputreader: $(LIB_OBJ)
	ar rcs libinputreader.a $^

$(LIB_OBJ): $(LIB_SRCS)
	$(CC) $(CFLAGS) -c $^ -o $@

$(TEST_BIN): $(TEST_OBJS)
	$(CC) $^ -L. -linputreader -o $@

-include ($(TEST_DEPS));

$(TEST_OBJS): $(TEST_SRCS)
	$(CC) $(TEST_CFLAGS) -c $^ -o $@

.PHONEY: clean_all
clean_all: clean_lib clean_test

.PHONEY: clean_lib
clean_lib:
	rm -rf input_reader.o lib*

.PHONEY: clean_test
clean_test:
	rm -rf $(TEST_OBJS) $(TEST_DEPS) $(TEST_BIN)

