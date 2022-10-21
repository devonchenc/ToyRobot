CXX = g++
CPPFLAGS = -Wall -g
LDFLAGS = -Wall -g
TESTFLAGS = -lgtest -lgtest_main
RM = rm -f

TARGET = toyrobot
SRCS = main.cpp Board.cpp Robot.cpp
OBJS = $(subst .cpp,.o, $(SRCS))

TESTTARGET = test
TESTSRCS = test.cpp Board.cpp Robot.cpp
TESTOBJS = $(subst .cpp,.o, $(TESTSRCS))

all: $(TARGET) $(TESTTARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJS)

run: $(TARGET) 
	./$(TARGET) move.txt
	
$(TESTTARGET): $(TESTOBJS)
	$(CXX) $(LDFLAGS) $(TESTOBJS) $(TESTFLAGS) -o $(TESTTARGET)
	
runtest: $(TESTTARGET)
	./$(TESTTARGET)

clean:
	$(RM) $(OBJS) $(TESTOBJS) $(TARGET) $(TESTTARGET)