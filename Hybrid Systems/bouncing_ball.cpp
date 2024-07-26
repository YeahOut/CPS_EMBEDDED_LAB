#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

const double g = 9.81; // 중력 가속도 (m/s^2)
const double h0 = 10.0; // 초기 높이 (m)
const double a = 0.9; // 충돌 계수
const double dt = 0.01; // 시간 간격 (s)
const double t_max = 10.0; // 시뮬레이션 시간 (s)

int main() {
    std::vector<double> time, height, velocity;
    double t = 0.0;
    double y = h0;
    double v = 0.0;

    // 파일 스트림 초기화
    std::ofstream outputFile("bouncing_ball_simulation.csv");
    outputFile << "Time,Height,Velocity\n";

    while (t <= t_max) {
        time.push_back(t);
        height.push_back(y);
        velocity.push_back(v);

        // 파일에 기록
        outputFile << t << "," << y << "," << v << "\n";

        // 속도 및 위치 업데이트
        v = v - g * dt;
        y = y + v * dt;

        // 충돌 체크
        if (y <= 0) {
            y = 0;
            v = -a * v;
        }

        t += dt;
    }

    outputFile.close();
    std::cout << "Simulation completed. Data saved to bouncing_ball_simulation.csv" << std::endl;

    return 0;
}