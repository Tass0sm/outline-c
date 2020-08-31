CC=gcc

outline.o: src/outline.c
	$(CC) -c src/outline.c -o src/outline.o

outline.so: src/outline.c
	$(CC) -c -shared src/outline.c -o src/outline.so


clean:
	rm -f src/outline.so
	rm -f src/outline.o


install: src/outline.so src/outline.h src/outline_reader.h
	cp -f src/outline.so /usr/lib/liboutline.so
	cp -f src/outline.h /usr/include/liboutline.h
	cp -f src/outline_reader.h /usr/include/liboutline_reader.h

uninstall: /usr/lib/liboutline.so /usr/include/liboutline.h /usr/include/liboutline_reader.h
	rm -f /usr/lib/liboutline.so
	rm -f /usr/include/liboutline.h
	rm -f /usr/include/liboutline_reader.h

reinstall:
	make clean
	make outline.so
	make uninstall
	make install
