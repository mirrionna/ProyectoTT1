g++ tests/EKF_GEOS3.cpp src/*cpp -lm -std=c++23 -o bin/EKF_GEOS3.exe -pg -no-pie
cd bin
EKF_GEOS3.exe
gprof EKF_GEOS3.exe gmon.out >> analysisprofiler.txt
pause