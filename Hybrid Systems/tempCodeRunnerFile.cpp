#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>

// 시뮬레이션 파라미터
const double dt = 0.01;     // 시간 간격 (s)
const double t_max = 100.0; // 시뮬레이션 시간 (s)
const double epsilon1 = 0.5;
const double epsilon2 = 1.0;
const double max_speed = 10.0; // 최대 속도 (mph)

// AGV 상태 구조체
struct AGVState {
    double x;
    double y;
    double theta;
    double e;
};

// 함수 선언
void updateState(AGVState &state, const std::string &mode);

int main() {
    std::vector<double> time;
    std::vector<AGVState> states;
    std::string mode = "stop";
    double t = 0.0;

    // 초기 상태 설정
    AGVState state = {0.0, 0.0, 0.0, 0.0};
    states.push_back(state);

    // 파일 스트림 초기화
    std::ofstream outputFile("agv_simulation.csv");
    outputFile << "Time,X,Y,Theta,Mode\n";

    while (t <= t_max) {
        time.push_back(t);

        // 파일에 기록
        outputFile << t << "," << state.x << "," << state.y << "," << state.theta << "," << mode << "\n";

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Time: " << t << "s, X: " << state.x << ", Y: " << state.y
                  << ", Theta: " << state.theta << ", Mode: " << mode << "\n";

        // 상태 업데이트
        updateState(state, mode);

        // 모드 전환 로직
        if (state.e < -epsilon2) {
            mode = "left";
        } else if (state.e > epsilon2) {
            mode = "right";
        } else if (fabs(state.e) < epsilon1) {
            mode = "straight";
        } else {
            mode = "stop";
        }

        states.push_back(state);
        t += dt;
    }

    outputFile.close();
    std::cout << "Simulation completed. Data saved to agv_simulation.csv" << std::endl;

    return 0;
}

void updateState(AGVState &state, const std::string &mode) {
    double speed = 0.0;
    double angular_speed = 0.0;

    if (mode == "straight") {
        speed = max_speed;
        angular_speed = 0.0;
    } else if (mode == "left") {
        speed = max_speed;
        angular_speed = M_PI; // 180 degrees/sec
    } else if (mode == "right") {
        speed = max_speed;
        angular_speed = -M_PI; // -180 degrees/sec
    } else if (mode == "stop") {
        speed = 0.0;
        angular_speed = 0.0;
    }

    // 상태 업데이트 (선형 및 각속도 사용)
    state.x += speed * cos(state.theta) * dt;
    state.y += speed * sin(state.theta) * dt;
    state.theta += angular_speed * dt;

    // e(t) 값 업데이트 (여기서는 간단하게 x 좌표를 기준으로 변위 측정)
    state.e = state.x - state.y; // 단순한 예시로, 실제로는 트랙과의 변위 측정 필요
}
