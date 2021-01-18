all:
	gcc -Wall -o leperssay leperssay.c -lncurses
install:
	cp leperssay /usr/bin/
	mkdir -p /usr/share/leperssay
	cp -R templates/ /usr/share/leperssay/.
clean:
	rm leperssay
