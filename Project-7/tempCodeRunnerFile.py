
# # Plot the speed data
# fig, ax1 = plt.subplots()
# plt.plot(x, df['current_speed'].to_numpy(), marker='o')
# plt.plot(x, df['target_speed'].to_numpy(),  marker='o')
# plt.plot(x, df['acceleration'].to_numpy(),  marker='o')

# ax1.set_xlabel('Time Step')
# ax1.set_ylabel('Speed')

# ax2 = ax1.twinx()
# plt.plot(x, df['error'].to_numpy(), marker='o')

# ax2.set_ylabel('Error')

# plt.title('Plot from Text File using Pandas')
# plt.grid(True)
# plt.show()
