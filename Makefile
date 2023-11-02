default:
	@echo "Check targets!"

all: digraph trigraph

digraph:
	$(CC) digraph.c -o digraph -lm

trigraph:
	$(CC) trigraph.c -o trigraph -lm

clean:
	rm digraph trigraphs
