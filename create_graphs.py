
import csv
import statistics
from collections import defaultdict
from pathlib import Path

import matplotlib.pyplot as plt

root = Path(__file__).resolve().parent
csv_file = root / "results" / "timings.csv"
graph_dir = root / "graphs"
graph_dir.mkdir(exist_ok=True)

measurements = defaultdict(list)

with csv_file.open(newline="", encoding="utf-8") as f:
    for row in csv.DictReader(f):
        key = (int(row["dataset_size"]), int(row["processes"]))
        measurements[key].append(float(row["elapsed_seconds"]))

means = {
    key: statistics.mean(times)
    for key, times in measurements.items()
}

# Graph 1: mean execution time versus process count
plt.figure()
for size in sorted({key[0] for key in means}):
    keys = sorted(
        [key for key in means if key[0] == size],
        key=lambda key: key[1]
    )
    plt.plot(
        [key[1] for key in keys],
        [means[key] for key in keys],
        marker="o",
        label=f"N = {size:,}"
    )

plt.xlabel("MPI processes")
plt.ylabel("Mean elapsed time (seconds)")
plt.title("Execution Time vs. MPI Process Count")
plt.xticks([1, 2, 4])
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig(graph_dir / "execution_time.png", dpi=200)
plt.close()

# Graph 2: speedup relative to one MPI process
plt.figure()
for size in sorted({key[0] for key in means}):
    baseline_key = (size, 1)
    if baseline_key not in means:
        continue

    keys = sorted(
        [key for key in means if key[0] == size],
        key=lambda key: key[1]
    )
    plt.plot(
        [key[1] for key in keys],
        [means[baseline_key] / means[key] for key in keys],
        marker="o",
        label=f"N = {size:,}"
    )

plt.plot([1, 2, 4], [1, 2, 4], linestyle="--",
         label="Ideal speedup")
plt.xlabel("MPI processes")
plt.ylabel("Speedup")
plt.title("Parallel Speedup")
plt.xticks([1, 2, 4])
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig(graph_dir / "speedup.png", dpi=200)
plt.close()

# Graph 3: parallel efficiency = speedup / process count
plt.figure()
for size in sorted({key[0] for key in means}):
    baseline_key = (size, 1)
    if baseline_key not in means:
        continue

    keys = sorted(
        [key for key in means if key[0] == size],
        key=lambda key: key[1]
    )
    plt.plot(
        [key[1] for key in keys],
        [
            means[baseline_key] / means[key] / key[1] * 100
            for key in keys
        ],
        marker="o",
        label=f"N = {size:,}"
    )

plt.xlabel("MPI processes")
plt.ylabel("Parallel efficiency (%)")
plt.title("Parallel Efficiency")
plt.xticks([1, 2, 4])
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig(graph_dir / "efficiency.png", dpi=200)
plt.close()

print("Graphs saved in:", graph_dir)
for key in sorted(means):
    print(
        f"N={key[0]:,}, processes={key[1]}, "
        f"mean={means[key]:.6f} seconds"
    )
