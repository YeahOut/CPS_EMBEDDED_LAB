import matplotlib.pyplot as plt
import pandas as pd

# CSV 파일 읽기
data = pd.read_csv('C:\\Users\\최예인\\Desktop\\bounce\\bouncing_ball_data.csv')
# 시간, 높이, 속도 데이터를 리스트로 변환
time = data['Time']
height = data['Height']
velocity = data['Velocity']

# 높이 시각화
plt.figure(figsize=(12, 6))
plt.subplot(2, 1, 1)
plt.plot(time, height, marker='o', linestyle='-', color='b')
plt.title('Height and Velocity of Bouncing Ball Over Time')
plt.ylabel('Height (m)')
plt.grid(True)

# 속도 시각화
plt.subplot(2, 1, 2)
plt.plot(time, velocity, marker='o', linestyle='-', color='r')
plt.xlabel('Time (s)')
plt.ylabel('Velocity (m/s)')
plt.grid(True)

# 그래프 출력
plt.tight_layout()
plt.show()
