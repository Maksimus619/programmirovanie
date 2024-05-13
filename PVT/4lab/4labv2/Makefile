all: app0 app1 app2 app3 app4 app5

app0: Serial.c
	gcc -g -o app0 Serial.c -lm -pg

app1: v1.c
	gcc -g -o app1 v1.c -lm -fopenmp -pg

app2: v2.c
	gcc -g -o app2 v2.c -lm -fopenmp -pg

app3: v3.c
	gcc -g -o app3 v3.c -lm -fopenmp -pg

app4: v4.c
	gcc -g -o app4 v4.c -lm -fopenmp -pg

app5: v5.c
	gcc -g -o app5 v5.c -lm -fopenmp -pg

.PHONY: clean

clean: app*
	rm app*
