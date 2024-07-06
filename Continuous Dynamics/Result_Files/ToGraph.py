import pandas as pd
import matplotlib.pyplot as plt

# CSV 파일 읽기
df_k2 = pd.read_csv(
    'C:\\Users\\최예인\\Desktop\\CPS_EMBEDDED_LAB\\Continuous Dynamics\\Result_Files\\helicopter_simulation_K2.csv')
df_k5 = pd.read_csv(
    'C:\\Users\\최예인\\Desktop\\CPS_EMBEDDED_LAB\\Continuous Dynamics\\Result_Files\\helicopter_simulation_K5.csv')
df_k10 = pd.read_csv(
    'C:\\Users\\최예인\\Desktop\\CPS_EMBEDDED_LAB\\Continuous Dynamics\\Result_Files\\helicopter_simulation_K10.csv')

# 그래프 그리기
plt.figure(figsize=(12, 6))

plt.plot(df_k2['Time'], df_k2['Angular Velocity'], label='K=2.0', color='b')
plt.plot(df_k5['Time'], df_k5['Angular Velocity'], label='K=5.0', color='g')
plt.plot(df_k10['Time'], df_k10['Angular Velocity'], label='K=10.0', color='r')

# 그래프 설정
plt.xlabel('Time (s)')
plt.ylabel('Angular Velocity (rad/s)')
plt.title('Helicopter Yaw Control using Feedback with Different K values')
plt.legend()
plt.grid(True)

# 그래프 보여주기
plt.show()
