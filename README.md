# RT-OS
Exploring the world of *real-time operating systems* through my project focused on hands-on learning.
<br>
Watch three LEDs blink concurrently using a round-robin scheduler on the STM32 Blue Pill.
<br>
[Watch the Project in Motion](https://www.youtube.com/watch?v=vqOGAk-3Y6g)
# Setting up the build environment
1. Download [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html#)
2. Import this project in workspace by clicking on File->Import->General, select **Existing Projects into Workspace**
3. In STM32CubeIDE, click the hammer icon or select "Project" > "Build Project" to compile the code.
4. Connect the ST-Link V2 programmer, select the firmware binary, and use the ST-Link Utility to program the STM32 Blue Pill board

## Source Code Description

The source code for this project is organized as follows:
- **CMSIS**: Contains CMSIS related files.
- **Core**
  - **Inc**
    - `led.h`
    - `os_kernel.h`
    - `tick_timer.h`
    - `uart.h`
  - **Src**
    - `main.c`: Main application code and entry point
    - `os_kernel.c`: OS kernel implementation
    - `led.c`: Configures onboard LED and external 3 LEDs
    - `tick_timer.c`: Source for tick interrupt used by scheduler
    - `uart.c`: Bare minimal driver for USART1
    - `sys_mem.c`: System memory management
    - `syscalls.c`: System calls for newlib
# Todos
- Implement Preemptive Scheduler for enhanced task management.
- Add support of synchronisation mechanisms
- Implement inter-task communication mechanisms	
# Reference
- A comprehensive [ video playlist](https://www.youtube.com/playlist?list=PLPW8O6W-1chyrd_Msnn4LD6LBs2slJITs) by Quantum Leaps on understanding and implementing RTOS concepts.
