all:
	gcc -c src/TJList.c -o bin/TJList.o
	gcc -c src/TJUtil.c -o bin/TJUtil.o
	gcc -shared bin/TJUtil.o bin/TJList.o -o lib/TJUtil.dll

bin/TJUtil.o: src/TJUtil.c include/TJUtil.h
	gcc -c -fPIC $< -o $@

bin/TJList.o: src/TJList.c include/TJUtil.h
	gcc -c -fPIC $< -o $@

linux: src/TJList.c src/TJUtil.c
	gcc -shared -fPIC $^ -o lib/libTJUtil.so