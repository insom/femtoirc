a.out: f.c pipe
	cc f.c
	./a.out
pipe:
	mkfifo -m 0600 pipe
