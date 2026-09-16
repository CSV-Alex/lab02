# Laboratorio 02 — Evaluación de algoritmos y memoria caché

Alex Cañapataña Vargas — Computación Paralela y Distribuida

## Compilar

```bash
g++ -O2 -std=c++17 -o actividad01 src/actividad01_loops_pacheco.cpp
g++ -O2 -std=c++17 -o actividad02 src/actividad02_matmul_clasico.cpp
g++ -O2 -std=c++17 -o actividad03 src/actividad03_matmul_bloques.cpp
```

## Ejecutar

Actividad 1 — bucles anidados:

```bash
./actividad01 <n> <reps>
# ejemplo
./actividad01 4000 5
```
Actividad 2 — multiplicación clásica:

```bash
./actividad02 <n> <reps>
# ejemplo
./actividad02 1024 3
```
Actividad 3 — multiplicación por bloques:

```bash
./actividad03 <n> <BS> <reps>
# ejemplo
./actividad03 1024 64 3
```

## Cachegrind (Actividad 5)

```bash
valgrind --tool=cachegrind --cache-sim=yes --cachegrind-out-file=cg.out ./actividad02 512 1
cg_annotate cg.out > cg.txt
kcachegrind cg.out
```
