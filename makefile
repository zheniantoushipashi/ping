all:ping


ping: ping.o libping.o icmp_timestramp.o  
	gcc -o ping libping.o ping.o 
ping.o: icmp.h icmp_address.h icmp_cksum.h  ping.h ping.c   core.h
	gcc -c	ping.c
libping.o:	libping.c  core.h  libping.h
	gcc -c 	libping.c

icmp_timestramp.o: icmp_timestramp.c  core.h icmp_timestramp.c
	gcc -c  icmp_timestramp.c 

clean:
	-rm -f *.o ping 	
