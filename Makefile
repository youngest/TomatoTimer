CC = g++
CFLAGS = -I$(CXXTEST)
TEST_GENERATOR = vendor/cxxtest/bin/cxxtestgen
TEST_GENERATOR_FLAGS = --error-printer
TEST_SUITES = tests/TomatoSuite.h
TEST_RUNNER = tests/runner
TEST_RUNNER_SOURCE = tests/runner.cpp

$(TEST_GENERATOR):
	./install-dependencies.sh
	
$(TEST_RUNNER_SOURCE): $(TEST_SUITES) $(TEST_GENERATOR)
	$(TEST_GENERATOR) $(TEST_GENERATOR_FLAGS) -o $@ $^

$(TEST_RUNNER): $(TEST_RUNNER_SOURCE)
	$(CC) -o $@ $^ $(CFLAGS)

test: $(TEST_RUNNER)
	$(^)

clean:
	rm -f $(TEST_RUNNER) $(TEST_RUNNER_SOURCE)
