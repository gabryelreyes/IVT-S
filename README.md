# IVT-S Current Sensor Communication Library
The objective of this library is to implement the communication used by the [IVT-S Current Sensor](./Documentation/IVT-S_Datasheet.pdf) from Isabellenhütte, which is performed using CAN Bus.

## Table of contents
- [Overview](#overview)
- [Installation](#installation)
- [Quick Start](#quick-start)
- [Issues, Ideas And Bugs](#issues-ideas-and-bugs)
- [License](#license)
- [Contribution](#contribution)


## Overview
*"The IVT-S is a high precision current measurement system,
designed for DC applications, especially for automotive
application. The product is based on a modular design and
provides flexibility for fast adaptations to meet customer
requirements in the automotive and the industrial area. The
continuous current measurement has a range up to ±2500 A."*
    - Isabellenütte (IVT-S Datasheet)

This library provides an interface to communicate with the current sensor without depending on the CAN implementation of the microcontroller.


## Installation
Just copy the library into your source files, or if using PlatformIO, add the URL to the Github Repository to your platformio.ini file.


## Quick Start
``` cpp

// Instance of the IVT-S
IVTS gCurrentSensor;

// Callback when a CAN Frame is received.
void some_can_frame_received_callback(int canId, bool isExtended, bool isRtr, int dlc, int* data)
{
    // CANFrame Class is provided by the IVT-S Library as a wrapper for the CAN Frame.
    CANFrame rcvdFrame;

    // Populate the class instance with the received CAN Frame.
    rcvdFrame.m_id = canId;
    rcvdFrame.m_extended = isExtended;
    rcvdFrame.m_rtr = isRtr;
    rcvdFrame.m_dlc = dlc;

    for (int i = 0; i < rcvdFrame.m_dlc; i++)
    {
        rcvdFrame.m_data[i] = data[i];
    }

    // Check if the frame ID belongs to the IVT-S
    switch (rcvdFrame.m_id)
    {
    case IVTS::IVT_Msg_Command:
    case IVTS::IVT_Msg_Debug:
    case IVTS::IVT_Msg_Response:
    case IVTS::IVT_Msg_Result_I:
    case IVTS::IVT_Msg_Result_U1:
    case IVTS::IVT_Msg_Result_U2:
    case IVTS::IVT_Msg_Result_U3:
    case IVTS::IVT_Msg_Result_T:
    case IVTS::IVT_Msg_Result_W:
    case IVTS::IVT_Msg_Result_As:
    case IVTS::IVT_Msg_Result_Wh:
    
        // Process the Frame Data
        gCurrentSensor.processFrame(rcvdFrame);
        break;

    default:
        break;
    }
}

```

## Issues, Ideas And Bugs
If you have further ideas or you found some bugs, great! Create a [issue](https://github.com/BlueAndi/esp-rgb-led-matrix/issues) or if you are able and willing to fix it by yourself, clone the repository and create a pull request.


## License
The whole source code is published under the [MIT license](http://choosealicense.com/licenses/mit/).
Consider the different licenses of the used third party libraries too!


## Contribution
Unless you explicitly state otherwise, any contribution intentionally submitted for inclusion in the work by you, shall be licensed as above, without any additional terms or conditions.