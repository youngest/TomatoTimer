CC=g++
CXXTEST=vendor/cxxtest

OBJDIR=obj
_OBJ=Tomato.o
OBJ=$(patsubst %,$(OBJDIR)/%,$(_OBJ))

SRCDIR=src
_SRCDEPS=Symbol.h Tomato.h TomatoAlarm.h TomatoDisplay.h
SRCDEPS=$(patsubst %,$(SRCDIR)/%,$(_DEPS))
_SRCS=Tomato.cpp
SRCS=$(patsubst %,$(SRCDIR)/%,$(_SRCS))
CFLAGS=-I $(SRCDIR)

TEST_CFLAGS=-I $(CXXTEST) -I $(SRCDIR)
TEST_GENERATOR=$(CXXTEST)/bin/cxxtestgen
TEST_GENERATOR_FLAGS=--error-printer
TEST_SUITES=tests/TomatoSuite.h
TEST_RUNNER=tests/runner
TEST_RUNNER_SOURCE=tests/runner.cpp

$(OBJDIR)/:
	mkdir $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(OBJDIR) $(SRCDEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TEST_GENERATOR):
	./install-dependencies.sh

$(TEST_RUNNER_SOURCE): $(TEST_SUITES) $(TEST_GENERATOR)
	$(TEST_GENERATOR) $(TEST_GENERATOR_FLAGS) -o $@ $^

$(TEST_RUNNER): $(TEST_RUNNER_SOURCE) $(OBJ)
	$(CC) -o $@ $^ $(TEST_CFLAGS)

test: $(TEST_RUNNER)
	$(^)

tomato: $(OBJ)


all: tomato test


clean:
	rm -f $(TEST_RUNNER) $(TEST_RUNNER_SOURCE)
	rm -rf $(OBJDIR)
