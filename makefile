INCLUDE = -Ibun2d -Ibun2d/include
FLAGS = -Wall -Wextra -g
LIB = lib/libglfw3.a lib/libglfw3dll.a -lgdi32
SRCS=$(wildcard *.c)

all:
	gcc $(FLAGS) $(INCLUDE) $(SRCS) -O1 -o run $(LIB) 
	./run
