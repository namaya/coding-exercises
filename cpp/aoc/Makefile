
DAY?=1

ifdef DEBUG
	FILE = example.txt
else
	FILE = input.txt
endif

run:
	clang++ -std=c++20 day$(DAY)*.cpp 
	./a.out inputs/2021/day$(DAY)/$(FILE)
	@rm a.out