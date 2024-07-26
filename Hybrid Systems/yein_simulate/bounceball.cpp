#include <iostream>
#include <cmath>
#include <fstream>

// ��� ����
const double g = 9.81;     // �߷� ���ӵ� (m/s^2)
const double restitution = 0.8; // ��ź ���
const double dt = 0.01;    // �ð� ���� (s)
const double threshold = 0.001; // Ƣ�� �Ӱ谪

// Ball Ŭ���� ����
class Ball {
public:
    Ball(double height, double velocity)
        : y(height), vy(velocity), t(0.0) {}

    // ���� ���� ������Ʈ �Լ�
    void updateFreeFall() {
        vy -= g * dt; // �ӵ� ������Ʈ (�߷� ����)
        y += vy * dt; // ��ġ ������Ʈ
        t += dt;      // �ð� ������Ʈ
    }

    // �ݻ� �Լ�
    void bounce() {
        vy = -restitution * vy; // ��ź ����� �����Ͽ� �ӵ� ����
    }

    // ���� ���� ��Ҵ��� Ȯ���ϴ� �Լ�
    bool isOnGround() const {
        return y <= 0.0 && vy < 0.0;
    }

    // ������ �Լ�
    double getPosition() const { return y; }
    double getVelocity() const { return vy; }
    double getTime() const { return t; }

private:
    double y;   // ����
    double vy;  // �ӵ�
    double t;   // �ð�
};

int main() {
    // �ʱ� ���� ����
    double initialHeight = 10.0;    // �ʱ� ����
    double initialVelocity = 0.0;   // �ʱ� �ӵ�

    // Ball ��ü ����
    Ball ball(initialHeight, initialVelocity);

    // CSV ���� ����
    std::ofstream file("bouncing_ball_data.csv");
    file << "Time,Height,Velocity\n"; // ��� �ۼ�

    // �ùķ��̼� ����
    while (ball.getTime() < 10.0) { // 10�� ���� �ùķ��̼�
        ball.updateFreeFall();      // ���� ���� ������Ʈ

        // ���� ���� ��Ҵ��� Ȯ��
        if (ball.isOnGround()) {
            ball.bounce();          // �ݻ� ����
        }

        // CSV ���Ͽ� ���� ���� ���
        file << ball.getTime() << "," << ball.getPosition() << "," << ball.getVelocity() << "\n";
    }

    file.close(); // ���� �ݱ�

    return 0;
}
