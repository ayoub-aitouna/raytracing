src = $(wildcard *.c)
obj = $(src:.c=.o)
lib	= math_lib

all: $(lib)

$(lib) : $(obj)
	gcc $(obj) -o $(lib)
