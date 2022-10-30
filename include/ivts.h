/* MIT License

Copyright (c) 2022 Gabryel Reyes <gabryelrdiaz@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

/*******************************************************************************
    DESCRIPTION
*******************************************************************************/
/**
 *  @brief  Library for the communication with the Isabellenhuete IVT-S Current Sensor
 *  @author Gabryel Reyes <gabryelrdiaz@gmail.com>
 */

#ifndef IVTS_H_
#define IVTS_H_

/******************************************************************************
 * Includes
 *****************************************************************************/

#include "CANFrame.h"

/******************************************************************************
 * Macros
 *****************************************************************************/

/******************************************************************************
 * Types and Classes
 *****************************************************************************/

class IVTS
{
public:
    enum IVT_Msg
    {
        IVT_Msg_Command     = 0x411,
        IVT_Msg_Debug       = 0x510,
        IVT_Msg_Response    = 0x511,
        IVT_Msg_Result_I    = 0x521,
        IVT_Msg_Result_U1   = 0x522,
        IVT_Msg_Result_U2   = 0x523,
        IVT_Msg_Result_U3   = 0x524,
        IVT_Msg_Result_T    = 0x525,
        IVT_Msg_Result_W    = 0x526,
        IVT_Msg_Result_As   = 0x527,
        IVT_Msg_Result_Wh   = 0x528
    };

    enum IVT_Mode
    {
        IVT_Mode_Stop = 0,
        IVT_Mode_Run = 1
    };

    /**
     *  Constructor of IVTS Instance.
     *  @param[in] canInt Instance of CAN Interface.
     */
    IVTS();

    /**
     *  Destructor of IVTS Instance.
     */
    ~IVTS();

    bool processFrame(const CANFrame &frame);

    int32_t getMeasurement(const IVT_Msg measurement);

private:
    int32_t m_current;
    int32_t m_voltage1;
    int32_t m_voltage2;
    int32_t m_voltage3;
    int32_t m_temperature;
    int32_t m_power;
    int32_t m_currentCounter;
    int32_t m_energyCounter;

    bool parseValue(int32_t *outputVariable, const CANFrame frame);
};

#endif /* IVTS_H_ */