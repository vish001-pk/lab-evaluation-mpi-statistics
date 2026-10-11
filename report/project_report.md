\# Distributed Dataset Statistics using MPI



\## 1. Problem Definition



The objective of this project is to calculate basic statistical properties of a dataset using sequential and parallel computing. The required statistics are sum, average, minimum, and maximum.



The parallel implementation uses the Message Passing Interface (MPI) to divide the work among multiple processes and combine their local results.



\## 2. Sequential Algorithm



1\. Initialize the sum to zero.

2\. Initialize the minimum and maximum.

3\. Generate each dataset value.

4\. Update the sum, minimum, and maximum.

5\. Compute the average as sum divided by dataset size.

6\. Display the results and execution time.



The time complexity is O(N), where N is the dataset size.



\## 3. Parallel Design



The MPI implementation distributes dataset indices among processes. Each process calculates local statistics for its assigned range.



The implementation uses:

\- `MPI\_Init` to initialize MPI.

\- `MPI\_Comm\_rank` to obtain the process rank.

\- `MPI\_Comm\_size` to obtain the total number of processes.

\- `MPI\_Reduce` with sum, minimum, and maximum operations to combine local results.

\- `MPI\_Wtime` to measure elapsed time.



Process 0 displays the final statistics.



The dataset values are generated deterministically using the formula:



`value = (index % 1000) + 1`



Thus, the values repeat from 1 through 1000. This avoids storing a large dataset in memory.



\## 4. Experimental Setup



The experiments were conducted on a Windows computer using:

\- C compiler and MPI compiler wrapper

\- Microsoft MPI runtime

\- Python and Matplotlib for graphs



Dataset sizes tested:

\- 100,000 values

\- 1,000,000 values

\- 5,000,000 values



MPI process counts tested:

\- 1 process

\- 2 processes

\- 4 processes



For the 1-million and 5-million datasets, five trials were recorded for each process count. For the 100,000 dataset, one trial was recorded for each process count.



\## 5. Experimental Results



\### Mean MPI execution time



| Dataset size | Processes | Mean time (seconds) |

|---:|---:|---:|

| 100,000 | 1 | 0.000621 |

| 100,000 | 2 | 0.000775 |

| 100,000 | 4 | 0.001219 |

| 1,000,000 | 1 | 0.004306 |

| 1,000,000 | 2 | 0.001759 |

| 1,000,000 | 4 | 0.001261 |

| 5,000,000 | 1 | 0.015383 |

| 5,000,000 | 2 | 0.007572 |

| 5,000,000 | 4 | 0.004244 |



\### Correctness validation



The output was checked against the expected statistics:



| Dataset size | Sum | Average | Minimum | Maximum |

|---:|---:|---:|---:|---:|

| 100,000 | 50,050,000 | 500.500 | 1 | 1000 |

| 1,000,000 | 500,500,000 | 500.500 | 1 | 1000 |

| 5,000,000 | 2,502,500,000 | 500.500 | 1 | 1000 |



All recorded MPI runs produced the expected statistics.



\## 6. Performance Analysis



For the 1-million dataset, the mean runtime was approximately 0.004306 seconds with one process, 0.001759 seconds with two processes, and 0.001261 seconds with four processes.



For the 5-million dataset, the mean runtime was approximately 0.015383 seconds with one process, 0.007572 seconds with two processes, and 0.004244 seconds with four processes.



The larger dataset showed lower mean execution time with more MPI processes. The 100,000-value workload did not benefit from additional processes in the recorded trials, illustrating that process startup and communication overhead can outweigh computational gains for small workloads.



The timings are very short and show variability. The 100,000-value results have only one trial per process count, so they should not be treated as reliable averages. Further repeated trials would improve confidence in the performance comparison.



\## 7. Speedup and Parallel Efficiency



Speedup is calculated as:



`Speedup = Mean time with 1 process / Mean time with p processes`



Parallel efficiency is calculated as:



`Efficiency = Speedup / p × 100%`



For the 1-million dataset, the observed speedup was approximately 2.45× with two processes and 3.42× with four processes.



For the 5-million dataset, the observed speedup was approximately 2.03× with two processes and 3.62× with four processes.



These values are preliminary because of timing variability. Efficiency can exceed 100% when noisy measurements make the parallel runtime appear disproportionately low; this is not proof of superlinear scalability.



\## 8. Graphs



The following graphs were generated from the recorded timings:

\- `graphs/execution\_time.png`

\- `graphs/speedup.png`

\- `graphs/efficiency.png`



\## 9. Conclusion



The project demonstrates the use of MPI to distribute statistical calculations and combine partial results. The implementation correctly computes sum, average, minimum, and maximum for the tested dataset sizes.



The measured experiments show benefits from using multiple MPI processes for the larger datasets. For small workloads, MPI overhead can reduce or eliminate those benefits. More repetitions and consistent timing methodology would improve the reliability of the performance evaluation.



\## 10. Future Improvements



\- Repeat every configuration several times.

\- Align the sequential and parallel timing methodology.

\- Test additional dataset sizes and process counts.

\- Compare sequential and parallel execution under the same experimental conditions.

\- Automate collection of runtime measurements.



