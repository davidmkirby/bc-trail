# BC-TRAIL

BC-TRAIL (Beam Control - TRacking And Integration of Layers) is a multi-mode control system for Fast-Steering Mirrors (FSM) and gimbals with automatic tracking capabilities.

## System Overview

The BC-TRAIL system manages both a Fast-Steering Mirror and a 3-stage gimbal with the following features:

- Real-time closed-loop control at 1000 Hz using FSM feedback
- Joystick input for controlling both systems
- Automatic tracking using EO Imaging/Moog 7007 tracker card data
- Mode switching between three states:
  - **Coarse Track**: Manual control of both gimbal and FSM
  - **Fine Track**: Manual control of FSM only
  - **Auto Track**: Using tracker card X/Y error signals

## Hardware Requirements

- PCIE-1816 DAQ card for FSM control (analog input/output)
- PCIE-1824 DAQ card for 3-axis gimbal control
- EO Imaging/Moog 7007 tracker card providing X/Y track errors
- Fast-Steering Mirror with ±10V input/output range
- 3-stage gimbal (azimuth, elevation, auxiliary elevation)
- Joystick with button for mode switching

## Software Requirements

- Rocky Linux 9.5 with real-time kernel
- Qt6 framework
- CMake 3.16+
- C++17 compatible compiler

## Building

1. Ensure that Qt6 and CMake are installed on your system.
2. Clone the repository:
   ```
   git clone https://github.com/your-organization/bc-trail.git
   cd bc-trail
   ```
3. Create a build directory and configure the project:
   ```
   mkdir build
   cd build
   cmake ..
   ```
4. Build the project:
   ```
   make
   ```
5. Install the application (optional):
   ```
   sudo make install
   ```

## Hardware Setup

1. Ensure that the PCIE-1816 and PCIE-1824 DAQ cards are properly installed and recognized by the system.
2. Connect the Fast-Steering Mirror's X and Y inputs to the analog outputs of the PCIE-1816 DAQ card.
3. Connect the Fast-Steering Mirror's X and Y position feedback to the analog inputs of the PCIE-1816 DAQ card.
4. Connect the 3-stage gimbal's azimuth, elevation, and auxiliary elevation inputs to the analog outputs of the PCIE-1824 DAQ card.
5. Connect the tracker card to the system.
6. Connect the joystick to a USB port on the system.

## Running

If installed:
```
bc-trail
```

From the build directory:
```
./bc-trail
```

For real-time thread priority (requires root privileges or appropriate permissions):
```
bc-trail --rt-priority
```

## Using the System

1. Start the system by clicking the "Start System" button.
2. Control modes can be switched using the "Change Mode" button or by pressing the mode button on the joystick.
3. In Coarse Track mode, the joystick controls both the FSM and gimbal.
4. In Fine Track mode, the joystick controls only the FSM.
5. In Auto Track mode, the system uses tracking errors from the tracker card to control the FSM.
6. The system can be stopped using the "Stop System" button.

## Architecture

The system consists of the following main components:

- **FSM Controller**: Manages the Fast-Steering Mirror using the PCIE-1816 DAQ card.
- **Gimbal Controller**: Controls the 3-stage gimbal using the PCIE-1824 DAQ card.
- **Tracker Interface**: Interfaces with the EO Imaging/Moog 7007 tracker card.
- **Joystick Interface**: Handles joystick input for manual control.
- **Control Loop**: Coordinates the above components and implements the control logic.
- **Main Window**: Provides the user interface for monitoring and controlling the system.

## License

Copyright (c) 2023 Your Organization. All rights reserved.

## Contact

For questions or support, please contact your organization's technical support team.