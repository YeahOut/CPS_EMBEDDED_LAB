import numpy as np
import matplotlib.pyplot as plt

# 헬리콥터 모델 매개변수
I_yy = 1.0  # 관성 모멘트
K = 2.0     # 피드백 Gain
a = 1.0     # 스케일링 상수
b = 1.0     # 상수 b
T_total = 10.0  # 시뮬레이션 시간 (초)
dt = 0.01  # 시간 간격

# 시간 벡터 생성
t = np.arange(0, T_total, dt)

# 초기 상태
theta_y = np.zeros_like(t)  # 각속도
error = np.zeros_like(t)    # 오류

# 원하는 각속도 (0으로 설정)
desired_theta_y = np.zeros_like(t)

# 외부 입력 토크 (메인 로터의 토크)
T_t = b * np.heaviside(t, 1)  # 단위 계단 함수

# 피드백 제어 시뮬레이션
for i in range(1, len(t)):
    # 현재 오류 계산
    error[i] = desired_theta_y[i] - theta_y[i-1]

    # 제어 신호 생성
    T_r = K * error[i]

    # 전체 토크 계산
    T_y = T_t[i] + T_r

    # 각속도 업데이트 (적분 계산)
    theta_y[i] = theta_y[i-1] + (T_y / I_yy) * dt

# 시뮬레이션 결과 시각화
plt.figure(figsize=(10, 6))
plt.plot(t, theta_y, label='Actual Angular Velocity ($\\dot{\\theta}_y$)')
plt.plot(t, desired_theta_y,
         label='Desired Angular Velocity ($\\psi$)', linestyle='--')
plt.xlabel('Time (s)')
plt.ylabel('Angular Velocity (rad/s)')
plt.title('Helicopter Yaw Control using Feedback')

# 세로축 눈금 위치 설정
y_ticks = np.arange(0, 0.6, 0.05)  # 0부터 1까지 0.1 간격으로 눈금 설정
plt.yticks(y_ticks)

plt.legend()
plt.grid(True)
plt.show()
