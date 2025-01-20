build.test:
	cc -o test test.c chacha.c -lcunit

test: build.test
	./test
