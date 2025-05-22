Proyecto de la asignatura Taller Transversal I del quinto curso del Doble Grado de Matemáticas e Ingeniería Informática de la Universidad de la Rioja, que implementa una operación para determinar la órbita inicial usando los métodos de Gauss y el filtro extendido de Kalman, en C++.

La orden de compilación de los tests es
```
g++ tests/tests.cpp src/*.cpp -lm -std=c++23 -o bin/tests.exe
```

Mientras que la orden de compilación del test de integración es
```
g++ tests/EKF_GEOS3.cpp src/*cpp -lm -std=c++23 -o bin/EKF_GEOS3.exe
```