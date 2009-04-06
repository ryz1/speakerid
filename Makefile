all:LOADCONFIG NORMRND LOADUTTERANCES UPDATE_P UPDATE_M UPDATE_S TESTGMM SHOWGMM SAVEGMM MIXTURE B
	gcc main.c loadconfig.o normrnd.o loadUtterances.o update_p.o update_m.o update_s.o testgmm.o showgmm.o saveGMM.o mixture.o b.o -o treinamento -lm
LOADCONFIG:
	gcc -c loadconfig.c
NORMRND:
	gcc -c normrnd.c
LOADUTTERANCES:
	gcc -c loadUtterances.c
UPDATE_P:
	gcc -c update_p.c
UPDATE_M:
	gcc -c update_m.c
UPDATE_S:
	gcc -c update_s.c
TESTGMM:
	gcc -c testgmm.c
SHOWGMM:
	gcc -c showgmm.c
SAVEGMM:
	gcc -c saveGMM.c
MIXTURE:
	gcc -c mixture.c
B:
	gcc -c b.c
