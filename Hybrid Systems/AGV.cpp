#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>

// 시뮬레이션 파라미터
const double dt = 0.1;     // 시간 간격 (s)
const double t_max = 100.0; // 시뮬레이션 시간 (s)
const double epsilon1 = 0.5;
const double epsilon2 = 1.0;
const double max_speed = 10.0; // 최대 속도 (mph)
const double track_center_y = 0.0; // 트랙의 중앙 y 좌표

// AGV 상태 구조체
struct AGVState {
    double x;
    double y;
    double theta;
    double e;
};

// 함수 선언
void updateState(AGVState &state, const std::string &mode);
double calculateDisplacement(double x, double y);

int main() {
    std::vector<double> time;
    std::vector<AGVState> states;
    std::string mode = "straight";
    double t = 0.0;

    // 초기 상태 설정
    AGVState state = {0.0, 0.0, 0.0, 0.0}; // 트랙 중앙에서 시작
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

        // 오른쪽 또는 왼쪽으로 치우치는 입력 추가
        if (t == 30.0 || t == 70.0) {
            state.y += 2.0; // 오른쪽으로 치우침
        }
        if (t == 50.0 || t == 90.0) {
            state.y -= 4.0; // 왼쪽으로 치우침
        }

        // 모드 전환 로직
        state.e = calculateDisplacement(state.x, state.y);
        if (state.e < -epsilon2) {
            mode = "left";
        } else if (state.e > epsilon2) {
            mode = "right";
        } else if (fabs(state.e) < epsilon1) {
            mode = "straight";
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
        angular_speed = M_PI / 8; // 약 22.5 degrees/sec
    } else if (mode == "right") {
        speed = max_speed;
        angular_speed = -M_PI / 8; // 약 -22.5 degrees/sec
    } else if (mode == "stop") {
        speed = 0.0;
        angular_speed = 0.0;
    }

    // 상태 업데이트 (선형 및 각속도 사용)
    state.x += speed * cos(state.theta) * dt;
    state.y += speed * sin(state.theta) * dt;
    state.theta += angular_speed * dt;
}

// 트랙 중심에서의 변위 계산 (y축을 기준으로)
double calculateDisplacement(double x, double y) {
    return y - track_center_y;
}
