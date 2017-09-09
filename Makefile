all: bindshell bindcon

bindshell:
	g++ -o bindshell bindshell.cpp

bindcon:
	g++ -o bindcon bindcon.cpp

clean:
	rm bindshell
	rm bindcon