#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// �︮���� �� �Ű�����
const double I_yy = 1.0;  // ���� ���Ʈ
const double a = 1.0;     // �����ϸ� ���
const double b = 1.0;     // ��� b
const double T_total = 10.0;  // �ùķ��̼� �ð� (��)
const double dt = 0.01;  // �ð� ����
const double output_limit = 1.0;  // ��� ��ȣ�� �ִ� ���밪

// �ùķ��̼� �Լ� ����
vector<double> simulate_feedback_control(double K, const vector<double>& desired_theta_y, const vector<double>& T_t) {
    size_t steps = desired_theta_y.size();
    vector<double> theta_y(steps, 0.0);
    vector<double> error(steps, 0.0);

    for (size_t i = 1; i < steps; ++i) {
        // ���� ���� ���
        error[i] = desired_theta_y[i] - theta_y[i - 1];

        // ���� ��ȣ ����
        double T_r = K * error[i];

        // ��ü ��ũ ���
        double T_y = T_t[i] + T_r;

        // ���ӵ� ������Ʈ (���� ���)
        theta_y[i] = theta_y[i - 1] + (a * T_y / I_yy) * dt;

        // ��� ��ȣ ��� ����
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
    // �ð� ���� ����
    size_t steps = static_cast<size_t>(T_total / dt);
    vector<double> t(steps);
    for (size_t i = 0; i < steps; ++i) {
        t[i] = i * dt;
    }

    // �ʱ� ���� �� ���ϴ� ���ӵ� ���� (0.2 rad/s)
    vector<double> desired_theta_y(steps, 0.2);

    // �ܺ� �Է� ��ũ (���� ������ ��ũ) ����
    vector<double> T_t(steps, 0.0);  // �ܺ� �Է� ��ũ ����

    // �� ���� K ���� ���� �ùķ��̼� ����
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
