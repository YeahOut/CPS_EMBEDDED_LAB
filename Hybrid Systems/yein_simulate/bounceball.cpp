#include <iostream>
#include <cmath>
#include <fstream>

// 상수 정의
const double g = 9.81;     // 중력 가속도 (m/s^2)
const double restitution = 0.8; // 반탄 계수
const double dt = 0.01;    // 시간 간격 (s)
const double threshold = 0.001; // 튀는 임계값

// Ball 클래스 정의
class Ball {
public:
    Ball(double height, double velocity)
        : y(height), vy(velocity), t(0.0) {}

    // 자유 낙하 업데이트 함수
    void updateFreeFall() {
        vy -= g * dt; // 속도 업데이트 (중력 영향)
        y += vy * dt; // 위치 업데이트
        t += dt;      // 시간 업데이트
    }

    // 반사 함수
    void bounce() {
        vy = -restitution * vy; // 반탄 계수를 적용하여 속도 반전
    }

    // 공이 땅에 닿았는지 확인하는 함수
    bool isOnGround() const {
        return y <= 0.0 && vy < 0.0;
    }

    // 접근자 함수
    double getPosition() const { return y; }
    double getVelocity() const { return vy; }
    double getTime() const { return t; }

private:
    double y;   // 높이
    double vy;  // 속도
    double t;   // 시간
};

int main() {
    // 초기 조건 설정
    double initialHeight = 10.0;    // 초기 높이
    double initialVelocity = 0.0;   // 초기 속도

    // Ball 객체 생성
    Ball ball(initialHeight, initialVelocity);

    // CSV 파일 열기
    std::ofstream file("bouncing_ball_data.csv");
    file << "Time,Height,Velocity\n"; // 헤더 작성

    // 시뮬레이션 루프
    while (ball.getTime() < 10.0) { // 10초 동안 시뮬레이션
        ball.updateFreeFall();      // 자유 낙하 업데이트

        // 공이 땅에 닿았는지 확인
        if (ball.isOnGround()) {
            ball.bounce();          // 반사 동작
        }

        // CSV 파일에 현재 상태 기록
        file << ball.getTime() << "," << ball.getPosition() << "," << ball.getVelocity() << "\n";
    }

    file.close(); // 파일 닫기

    return 0;
}
