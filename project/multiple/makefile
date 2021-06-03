CC=gcc
CFLAGS= -I.
DEPS=myheader.h
OBJ=pipes.o function.o
%o:%c$(DEPS)
	$(CC) -save-temps -c -o $@ $< $(CFLAGS)
projectmake:$(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
