\# Distributed Dataset Statistics using MPI



\## Overview



This project implements sequential and parallel calculations of basic dataset statistics using C and the Message Passing Interface (MPI).



The program calculates:

\- Sum

\- Average

\- Minimum

\- Maximum



The parallel implementation divides dataset indices among MPI processes and combines local results using `MPI\_Reduce`.



\## Technologies Used



\- C

\- MPI

\- Microsoft MPI runtime

\- GCC / MPI compiler wrapper

\- Python 3

\- Matplotlib



\## Project Structure



```text

MPI\_Project/

├── README.md

├── create\_graphs.py

├── src/

│   ├── mpi\_test.c

│   ├── mpi\_statistics.c

│   └── sequential\_statistics.c

├── results/

│   └── timings.csv

├── graphs/

│   ├── execution\_time.png

│   ├── speedup.png

│   └── efficiency.png

├── report/

│   └── project\_report.md

└── presentation/

```



\## Dataset



Values are generated using:



```c

value = (index % 1000) + 1;

```



This generates a repeating sequence from 1 to 1000 without requiring the entire dataset to be stored in memory.



\## How to Compile and Run



Run these commands from the project root in Windows CMD. Ensure the MPI compiler and Microsoft MPI runtime are available in your PATH.



\### Compile the sequential version



```cmd

gcc src\\sequential\_statistics.c -o sequential\_statistics.exe

```



\### Run the sequential version



```cmd

sequential\_statistics.exe 1000000

```



\### Compile the MPI version



```cmd

mpicc src\\mpi\_statistics.c -o mpi\_statistics.exe

```



\### Run with four processes



```cmd

mpiexec -n 4 mpi\_statistics.exe 1000000

```



The final argument specifies the dataset size. Tested sizes include 100000, 1000000, and 5000000.



\## Results



The recorded experiments compare 1, 2, and 4 MPI processes. The larger datasets showed lower mean runtimes with more processes in the measured trials.



The measured statistics for the generated dataset were validated against the expected sum, average, minimum, and maximum.



See `results/timings.csv` for recorded timings and `graphs/` for the generated performance graphs.



\## Graphs



\- `graphs/execution\_time.png` — mean runtime versus MPI process count

\- `graphs/speedup.png` — speedup relative to one MPI process

\- `graphs/efficiency.png` — parallel efficiency



\## Report



The report is located at `report/project\_report.md`. It covers the problem definition, sequential algorithm, parallel design, experimental setup, results, performance analysis, and conclusion.



\## Experimental Notes



The 100,000-value measurements contain one trial per process count; the larger dataset configurations contain five trials per process count. Timings are short and may vary due to system scheduling and MPI overhead, so results should be interpreted with this limitation in mind.



\## Future Improvements



\- Increase the number of repetitions for every configuration.

\- Use consistent timing methodology for the sequential and MPI versions.

\- Test additional dataset sizes and process counts.

\- Automate collection of timing results.



\## Author



&#x20;Vishal  P K    130   01FE24BCI060

&#x20;Rohan   S B    113   01FE24BCI047

&#x20;Sandesh G T    114   01FE24BCI048

&#x20;Aditya P       129   01FE24BCI059

