all: clean report
	clang lab7a.c -o lab7a
	clang lab7b.c -o lab7b
	clang lab7c.c -lm -o lab7c
clean:
	rm -f lab7a
	rm -f lab7b
	rm -f lab7c
report:
	rm -f report.dvi
	latex report.tex