CC=gcc

all: srvv6 cliv6 srvv4 cliv4
v4: srvv4 cliv4
v6: srvv6 cliv6
srvv6: daytimetcpsrvv6.c 
	gcc -o srvv6 daytimetcpsrvv6.c 
cliv6: daytimetcpcliv6.c 
	gcc -o cliv6 daytimetcpcliv6.c 
srvv4: daytimetcpsrvv4.c
	gcc -o srvv4 daytimetcpsrvv4.c
cliv4: daytimetcpcliv4.c
	gcc -o cliv4 daytimetcpcliv4.c
clean:
	rm srvv6 cliv6 srvv4 cliv4
