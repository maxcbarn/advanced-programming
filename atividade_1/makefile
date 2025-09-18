source := src/
files := $(source)* lib/*.hpp
compiler := g++
exe := app
flags := -Wall -g -lraylib -lm

$(exe):
	$(compiler) $(files) $(flags) -o $(exe) 

clean:
	rm -f $(obj) $(exe)