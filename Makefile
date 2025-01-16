c:
	gcc -c stringlib.c userfilelib.c userlib.c validationlib.c studentlib.c teacherlib.c
	gcc -o c main.c stringlib.o userfilelib.o userlib.o validationlib.o studentlib.o teacherlib.o
	./c.exe