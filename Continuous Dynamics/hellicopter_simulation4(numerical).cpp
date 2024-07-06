#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// 헬리콥터 모델 매개변수
const double I_yy = 1.0;  // 관성 모멘트
const double a = 1.0;     // 스케일링 상수
const double b = 1.0;     // 상수 b
const double T_total = 10.0;  // 시뮬레이션 시간 (초)
const double dt = 0.01;  // 시간 간격
const double output_limit = 1.0;  // 출력 신호의 최대 절대값

// 시뮬레이션 함수 정의
vector<double> simulate_feedback_control(double K, const vector<double>& desired_theta_y, const vector<double>& T_t) {
    size_t steps = desired_theta_y.size();
    vector<double> theta_y(steps, 0.0);
    vector<double> error(steps, 0.0);

    for (size_t i = 1; i < steps; ++i) {
        // 현재 오류 계산
        error[i] = desired_theta_y[i] - theta_y[i - 1];

        // 제어 신호 생성
        double T_r = K * error[i];

        // 전체 토크 계산
        double T_y = T_t[i] + T_r;

        // 각속도 업데이트 (적분 계산)
        theta_y[i] = theta_y[i - 1] + (a * T_y / I_yy) * dt;

        // 출력 신호 경계 설정
        if (theta_y[i] > output_limit) {
            theta_y[i] = output_limit;
        }
        else if (theta_y[i] < -output_limit) {
            theta_y[i] = -output_limit;
        }
    }

    return theta_y;
}

int main() {
    // 시간 벡터 생성
    size_t steps = static_cast<size_t>(T_total / dt);
    vector<double> t(steps);
    for (size_t i = 0; i < steps; ++i) {
        t[i] = i * dt;
    }

    // 초기 상태 및 원하는 각속도 설정 (0.2 rad/s)
    vector<double> desired_theta_y(steps, 0.2);

    // 외부 입력 토크 (메인 로터의 토크) 제거
    vector<double> T_t(steps, 0.0);  // 외부 입력 토크 없음

    // 세 가지 K 값에 대한 시뮬레이션 실행
    vector<double> K_values = { 2.0, 5.0, 10.0 };

    for (double K : K_values) {
        vector<double> theta_y = simulate_feedback_control(K, desired_theta_y, T_t);
        cout << "K = " << K << endl;
        for (size_t i = 0; i < steps; ++i) {
            cout << "Time = " << t[i] << " s, Angular Velocity = " << theta_y[i] << " rad/s" << endl;
        }
        cout << endl;
    }

    return 0;
}
