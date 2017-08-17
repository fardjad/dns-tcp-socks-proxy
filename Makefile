FLAGS=-Wall -Wextra
all:
	gcc $(FLAGS) -o dns_proxy dns_proxy.c utils.c
.PHONY : clean
clean :
	-rm dns_proxy

