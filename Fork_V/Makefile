.PHONY:all
all:Fork VFork

Fork:Fork.c
	gcc -o $@ $^
VFork:VFork.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -rf Fork VFork
