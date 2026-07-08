import pandas as pd
import matplotlib.pyplot as plt
import numpy

# Read data file and specify data separator as sep=',' for commas
df = pd.read_csv('Speed_Data.txt', sep=',')

x = numpy.linspace(1, len(df), len(df))
# print(x)
# print(df['current_speed'].to_numpy())
# print(len(df['current_speed'].to_numpy()))

# Plot the speed data
fig, ax1 = plt.subplots()
line1, = plt.plot(x, df['current_speed'].to_numpy(), marker='o',label='Current Speed')
line2, = plt.plot(x, df['target_speed'].to_numpy(),  marker='o',label='Target Speed')
line3, = plt.plot(x, df['acceleration'].to_numpy(),  marker='o',label='Acceleration')

ax1.set_xlabel('Time Step')
ax1.set_ylabel('Speed')
plt.title('Speed Data and Error')

# Plot the error data
ax2 = ax1.twinx()
line4, = plt.plot(x, df['error'].to_numpy(), marker='o',color='red',label='Error')

ax2.set_ylabel('Error', color='red')

# Gather handles and labels from both axes
lines1, labels1 = ax1.get_legend_handles_labels()
# lines2, labels2 = ax1.get_legend_handles_labels()
# lines3, labels3 = ax1.get_legend_handles_labels()
lines2, labels2 = ax2.get_legend_handles_labels()

# 5. Combine and create a single legend on ax1 (or ax2)
ax1.legend(lines1 + lines2, labels1 + labels2, bbox_to_anchor=(0, 1), loc='upper right')



plt.grid(True)
plt.show()
