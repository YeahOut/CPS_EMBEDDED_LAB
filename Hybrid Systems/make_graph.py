import pandas as pd
import matplotlib.pyplot as plt

# CSV 파일 로드
data = pd.read_csv('/Users/she/cps/Hybrid Systems/bouncing_ball_simulation.csv')

# 데이터 확인 (옵션)
print(data.head())

# 그래프 그리기
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 8))

# 높이 vs 시간
ax1.plot(data['Time'], data['Height'], label='Height')
ax1.set_xlabel('Time (s)')
ax1.set_ylabel('Height (m)')
ax1.set_title('Height vs Time')
ax1.legend()

# 속도 vs 시간
ax2.plot(data['Time'], data['Velocity'], label='Velocity', color='r')
ax2.set_xlabel('Time (s)')
ax2.set_ylabel('Velocity (m/s)')
ax2.set_title('Velocity vs Time')
ax2.legend()

plt.tight_layout()
plt.show()
