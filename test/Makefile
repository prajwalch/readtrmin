CFLAGS = -g -Wall -Werror -Wextra -DDEBUG -MMD -I../src
TEST_SRCS = test.c
TEST_OBJS = test.o
TEST_DEPS = test.d
TEST_BIN = testreader
LIBRARIES = -lreadtrmin

all: test
## for test

.PHONY: test
test: $(TEST_BIN)

$(TEST_BIN): $(TEST_OBJS)
	$(CC) $^ $(LIBRARIES) -o $@

-include ($(TEST_DEPS));
$(TEST_OBJS): $(TEST_SRCS)
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: clean
clean:
	rm -rf $(TEST_OBJS) $(TEST_DEPS) $(TEST_BIN)

