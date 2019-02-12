all:
	gcc -c TJList.c -o ../bin/TJList.o
	gcc -c TJUtil.c -o ../bin/TJUtil.o
	gcc -shared ../bin/TJUtil.o ../bin/TJList.o -o ../lib/TJUtil.dll

test:
	gcc test.c -I ../include -L ../lib -lTJUtil -o test.exe