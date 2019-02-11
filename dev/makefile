all:
	gcc -c TJList.c -o ../lib/TJList.o
	gcc -c TJUtil.c -o ../lib/TJUtil.o
	gcc -shared ../lib/TJUtil.o ../lib/TJList.o -o ../lib/TJUtil.lib

test:
	gcc test.c -I ../include -L ../lib -lTJUtil -o test.exe