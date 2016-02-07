libdlgpio.so:dlgpio.c
	gcc -c dlgpio.c -fPIC -shared -o libdlgpio.so
install:
	cp libdlgpio.so /usr/lib/
	cp dlgpio.h /usr/include/
uninstall:
	rm /usr/lib/libdlgpio.so
	rm /usr/include/dlgpio.h
clean:
	rm *.so
	
