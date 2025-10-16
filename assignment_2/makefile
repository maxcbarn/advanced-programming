source := src/
files := $(source)* lib/*.hpp
compiler := g++
exe := app
flags := -Wall -lraylib -lm

$(exe):
	$(compiler) $(files) $(flags) -o $(exe) 

debug:
	$(compiler) $(files) $(flags) -g -o $(exe) 

clean:
	rm -f $(obj) $(exe)