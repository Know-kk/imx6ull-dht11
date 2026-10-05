CC=arm-buildroot-linux-gnueabihf-gcc
sensor : main.o sensor.o
	$(CC) -o sensor main.o sensor.o
main.o : main.c sensor.h
	$(CC) -c -o main.o main.c
sensor.o : sensor.c sensor.h
	$(CC) -c -o sensor.o sensor.c
clean :
	rm -f main.o sensor.o sensor
