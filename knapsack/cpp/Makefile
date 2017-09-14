
NAME=knapsack
CXX=clang++
RM=rm -f
CPPFLAGS=-g -std=c++14 -Wall -O3 # $(shell root-config --cflags)
LDFLAGS=-g -Wall # $(shell root-config --ldflags)
LDLIBS= #$(shell root-config --libs)

SRCS=main.cpp Knapsack.cpp KnapsackGreedy.cpp KnapsackDP.cpp KnapsackBranchBound.cpp
OBJS=$(subst .cpp,.o,$(SRCS))


all: $(NAME)

run: all
	./knapsack ../data/ks_4_0

$(NAME): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(NAME) $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) *~ .depend

include .depend
