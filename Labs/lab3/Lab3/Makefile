#specify all source files here
SRCS = 5_12.c 5_13.c 5_14.c 6_11.c 6_12.c
#specify target here (name of executable)
TARG = a
#specify compiler, compile flags, and needed libs
CC = gcc
OPTS = -WALL -O
LIBS = -lm

#this translates .c files in src list to .o's
OBJS = $(SRCS:.c=.o)

#all is not reall needed, but is used to generate the target
all: $(TARG)

#this generates the target executable
$(TARG): $(OBJS)
	$(CC) -o $(TARG) $(OBJS) $(LIBS)

#this is a generic rule for .o files
%.o: %.c
	$(CC) $(OPTS) -c $< -o $@

#and finally, a clean line
clean:
	rm -f $(OBJS) $(TARG)