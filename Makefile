build.test:
	cc -o test test.c -lcunit

test: build.test
	./test
