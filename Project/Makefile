APP:=MyUser
CC:=gcc
CFLAGS:=-c
OBJS:=main.o User.o menu.o

export APP CC CFLAGS OBJS

ALL:
	make -C src
	make -C obj
.PHONY:clean
clean:
	$(RM) obj/*.o
	$(RM) bin/*

