# The following two variable will be commandline determined by TA
# For testing, you could uncomment them.
SRIPATH ?= /Users/byronhsu/Documents/srilm-1.5.10
MACHINE_TYPE ?= macosx
LM ?= bigram.lm

CXX = /usr/bin/g++
CXXFLAGS = -O3 -I$(SRIPATH)/include -w
vpath lib%.a $(SRIPATH)/lib/$(MACHINE_TYPE)

TARGET = mydisambig
SRC = mydisambig.cpp
OBJ = $(SRC:.cpp=.o)
TO = ZhuYin-Big5.map
FROM = Big5-ZhuYin.map
.PHONY: all clean map run

all: $(TARGET)

$(TARGET): $(OBJ) -loolm -ldstruct -lmisc
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

run:
	mkdir -p ./result2
	@#TODO How to run your code toward different txt? 
	@for i in $(shell seq 1 10) ; do \
		echo "Running $$i.txt"; \
		./mydisambig -text testdata/$$i.txt -map $(TO) -lm $(LM) -order 2 > result2/$$i.txt; \
	done;
map:
	@#TODO How to map?
	@echo "Mapping!"
	@python3 mapping.py $(FROM) $(TO)
clean:
	$(RM) $(OBJ) $(TARGET)