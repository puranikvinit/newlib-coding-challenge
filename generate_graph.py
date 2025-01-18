import matplotlib.pyplot as plt
import numpy as np

data_sizes = [0, 3, 15, 32]
cycle_counts_aligned = {
    "memset_given": [0x10, 0x1C, 0x4C, 0x90],
    "memset_mod": [0x11, 0x1D, 0x2E, 0x36],
    "memset_bonus": [0x13, 0x21, 0x32, 0x3A],
}
cycle_counts_misaligned = {
    "memset_given": [0x10, 0x1C, 0x4C, 0x90],
    "memset_mod": [0x11, 0x1D, 0x2E, 0x36],
    "memset_bonus": [0x13, 0x27, 0x38, 0x4C],
}

bar_width = 0.25
x = np.arange(len(data_sizes))

plt.figure(figsize=(10, 6))

plt.bar(x - bar_width, cycle_counts_aligned["memset_given"], width=bar_width, label="memset_given", color='skyblue')
plt.bar(x, cycle_counts_aligned["memset_mod"], width=bar_width, label="memset_mod", color='orange')
plt.bar(x + bar_width, cycle_counts_aligned["memset_bonus"], width=bar_width, label="memset_bonus", color='green')

plt.xlabel("Test Data Sizes (Bytes)", fontsize=12)
plt.ylabel("Cycle Count", fontsize=12)
plt.title("Cycle Count vs Test Data Sizes for Aligned Memory Location", fontsize=14)
plt.xticks(x, data_sizes)
plt.legend()

plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.tight_layout()
plt.show()

plt.bar(x - bar_width, cycle_counts_misaligned["memset_given"], width=bar_width, label="memset_given", color='skyblue')
plt.bar(x, cycle_counts_misaligned["memset_mod"], width=bar_width, label="memset_mod", color='orange')
plt.bar(x + bar_width, cycle_counts_misaligned["memset_bonus"], width=bar_width, label="memset_bonus", color='green')

plt.xlabel("Test Data Sizes (Bytes)", fontsize=12)
plt.ylabel("Cycle Count", fontsize=12)
plt.title("Cycle Count vs Test Data Sizes for Misaligned Memory Location", fontsize=14)
plt.xticks(x, data_sizes)
plt.legend()

plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.tight_layout()
plt.show()
