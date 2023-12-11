
YEAR?=2021
DAY?=1

ifdef DEBUG
	ifdef PART
		FILE = part$(PART)/example.txt
	else
		FILE = example.txt
	endif
else
	ifdef PART
		FILE = part$(PART)/input.txt
	else
		FILE = input.txt
	endif
endif

run:
	clang++ -std=c++20 src/$(YEAR)/day$(DAY)*.cpp 
	./a.out inputs/$(YEAR)/day$(DAY)/$(FILE)
	@rm a.out