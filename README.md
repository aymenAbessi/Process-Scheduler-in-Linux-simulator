# Process-Scheduler-in-Linux-simulator
 Performance Measurement and Algorithms Simulation : C, Linux, GnuPlot
# Program Execution Guide

## Overview

This guide provides step-by-step instructions for executing the program successfully. Follow the steps below to run the program, generate process data, and compare different scheduling algorithms.

## Steps to Execute the Program

1. **Access the Program’s Folder:**
   - Open your terminal (VSCode terminal is also supported).
   - Navigate to the program’s folder.
   - Use one of the following commands to compile and execute the code:
     - `./script.sh`: This command runs a script that compiles and executes the code.
     - `make run`: This command runs the makefile, which executes the code.

2. **Choose Data Source:**
   - After executing the program, you will be prompted to choose whether to use the processes data registered in the config file or to generate new data through the terminal.
   - If you choose to generate a new config file, the program will ask for data including the minimum and maximum arrival time, execution time, and priority any process could have. This data will be used to generate a new random list of processes.

3. **Select Algorithm:**
   - After selecting the processes to run, a menu appears showing the different algorithms that can be simulated. Choose an algorithm by typing its corresponding number.

4. **View Execution and Metrics:**
   - A new interface is generated where you can see the execution of the different processes along with metrics like rotation time and waiting time.
   - There is also a button named “Compare algo metrics”, but it is disabled until at least two different algorithms have been run.

5. **Exit or Rerun:**
   - After closing the new window, you return to the terminal where you can choose to exit the program or try running a different algorithm.

6. **Compare Algorithms:**
   - If you choose to run another algorithm, you will notice that the "Compare algo metrics" button is now enabled, allowing you to compare the metrics of the different algorithms.

## Figures
![image](https://github.com/aymenAbessi/Process-Scheduler-in-Linux-simulator/assets/99690345/9ef3b1c2-4f22-4367-be41-0123f0aef63b)
- **Figure 1:** Running command and execution
- ![image](https://github.com/aymenAbessi/Process-Scheduler-in-Linux-simulator/assets/99690345/63a8e647-d13d-4ce7-b48c-ff37c16e96df)
- **Figure 2:** New config file generation
- ![image](https://github.com/aymenAbessi/Process-Scheduler-in-Linux-simulator/assets/99690345/bcc45a58-b332-4dad-ad43-a39af6d8e934)
- **Figure 3:** Algorithms menu
- ![image](https://github.com/aymenAbessi/Process-Scheduler-in-Linux-simulator/assets/99690345/12d41e3e-650a-4ab7-b3d3-08759c75e491)
- **Figure 4:** Gantt chart and metrics of FIFO
- ![image](https://github.com/aymenAbessi/Process-Scheduler-in-Linux-simulator/assets/99690345/bd80d995-002b-458d-a1e0-5b7c9eb5d68d)
- **Figure 5:** line chart chart and metrics of FIFO
- ![image](https://github.com/aymenAbessi/Process-Scheduler-in-Linux-simulator/assets/99690345/6fcb5ce8-73d3-4b10-a8a5-b143afb7a844)
- **Figure 6:** bar chart chart and metrics of FIFO
## Authors

- 1ING3 Aimen – Mouhib – Aness – Angham

By following these steps, you should be able to run the program, generate and choose process data, execute different scheduling algorithms, and compare their performance metrics.
