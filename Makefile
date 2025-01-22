install.tools:
	sudo apt install libcunit1 libcunit1-doc libcunit1-dev

build.test:
	cc -o test test.c chacha.c -lcunit

test: build.test
	./test
