CC = gcc
FILES = kurtis_shell.c run_process.c
OUT_EXE = prompt

build: $(FILES)
	$(CC) -o $(OUT_EXE) $(FILES)

clean:
	rm -f prompt

rebuild: clean build
