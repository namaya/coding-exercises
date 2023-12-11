
YEAR?=2021
DAY?=1

ifdef DEBUG
	FILE = example.txt
else
	FILE = input.txt
endif

run:
	clang++ -std=c++20 src/$(YEAR)/day$(DAY)*.cpp 
	./a.out inputs/$(YEAR)/day$(DAY)/$(FILE)
	@rm a.out