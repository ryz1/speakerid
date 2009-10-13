#Makefile projeto Reconhecimento de Fala
#Edielson Prevato Frigieri
#Atualização: 30/07/07

#export PATH=$PATH:/media/sda4/projetos/arm/atmel/buildroot-v23434/build_arm/staging_dir/usr/bin

CC=gcc 
#CC=/media/sda4/projetos/arm/atmel/buildroot-v23434/build_arm/staging_dir/usr/bin/arm-linux-gcc-4.2.4 
CFLAGS=-pg -c -Wall
LDFLAGS= -pg -lm 

SOURCES=main.c loadconfig.c normrnd.c loadUtterances.c update_p.c update_m.c update_s.c testgmm.c showgmm.c saveGMM.c mixture.c b.c lbg.c

OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=treinagmm

all: $(SOURCES) $(EXECUTABLE)
	rm -rf *o
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(EXECUTABLE)
	

