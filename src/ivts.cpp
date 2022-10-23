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

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "ivts.h"

/******************************************************************************
 * Macros
 *****************************************************************************/

/******************************************************************************
 * Prototypes
 *****************************************************************************/

/******************************************************************************
 * Local Variables
 *****************************************************************************/


/******************************************************************************
 * Public Methods
 *****************************************************************************/

IVTS::IVTS() : m_txFrameBuffer(nullptr), 
               m_current(0),
               m_voltage1(0),
               m_voltage2(0),
               m_voltage3(0),
               m_temperature(0),
               m_power(0),
               m_currentCounter(0),
               m_energyCounter(0)
{
}

IVTS::~IVTS()
{
}

bool IVTS::isIVTSFrame(const uint32_t frameId)
{
    bool isValid = false;

    switch (frameId)
    {
    case IVT_Msg_Response:
    case IVT_Msg_Result_I:
    case IVT_Msg_Result_U1:
    case IVT_Msg_Result_U2:
    case IVT_Msg_Result_U3:
    case IVT_Msg_Result_T:
    case IVT_Msg_Result_W:
    case IVT_Msg_Result_As:
    case IVT_Msg_Result_Wh:
        isValid = true;
        break;

    default:
        break;
    }

    return isValid;
}

bool IVTS::processFrame(const CANFrame &frame)
{
    bool isSuccess = true;
    int32_t *selectedParam = nullptr;

    switch (frame.m_id)
    {
    case IVTS::IVT_Msg_Response:
        break;

    case IVTS::IVT_Msg_Result_I:
        if(0x00 != frame.m_data[0])
        {
            // Error in CAN Message configuration
            isSuccess = false;
        }
        else
        {
            selectedParam = &m_current;
        }
        break;

    case IVTS::IVT_Msg_Result_U1:
        if(0x01 != frame.m_data[0])
        {
            // Error in CAN Message configuration
            isSuccess = false;
        }
        else
        {
            selectedParam = &m_voltage1;
        }
        break;

    case IVTS::IVT_Msg_Result_U2:
        if(0x02 != frame.m_data[0])
        {
            // Error in CAN Message configuration
            isSuccess = false;
        }
        else
        {
            selectedParam = &m_voltage2;
        }
        break;

    case IVTS::IVT_Msg_Result_U3:
        if(0x03 != frame.m_data[0])
        {
            // Error in CAN Message configuration
            isSuccess = false;
        }
        else
        {
            selectedParam = &m_voltage3;
        }
        break;

    case IVTS::IVT_Msg_Result_T:
        if(0x04 != frame.m_data[0])
        {
            // Error in CAN Message configuration
            isSuccess = false;
        }
        else
        {
            selectedParam = &m_temperature;
        }
        break;

    case IVTS::IVT_Msg_Result_W:
        if(0x05 != frame.m_data[0])
        {
            // Error in CAN Message configuration
            isSuccess = false;
        }
        else
        {
            selectedParam = &m_power;
        }
        break;

    case IVTS::IVT_Msg_Result_As:
        if(0x06 != frame.m_data[0])
        {
            // Error in CAN Message configuration
            isSuccess = false;
        }
        else
        {
            selectedParam = &m_currentCounter;
        }
        break;

    case IVTS::IVT_Msg_Result_Wh:
        if(0x07 != frame.m_data[0])
        {
            // Error in CAN Message configuration
            isSuccess = false;
        }
        else
        {
            selectedParam = &m_energyCounter;
        }
        break;

    default:
        isSuccess = false;
        break;
    }

    if(isSuccess)
    {
        parseValue(selectedParam, frame);
    }

    return isSuccess;
}

bool IVTS::getTxFrame(CANFrame *frame)
{
    bool isFramePending = false;

    if (nullptr != m_txFrameBuffer)
    {
        isFramePending = true;
        frame->m_id = m_txFrameBuffer->m_id;
        frame->m_extended = m_txFrameBuffer->m_extended;
        frame->m_rtr = m_txFrameBuffer->m_rtr;
        frame->m_dlc = m_txFrameBuffer->m_dlc;

        for (uint8_t i = 0; i < m_txFrameBuffer->m_dlc; i++)
        {
            frame->m_data[i] = m_txFrameBuffer->m_data[i];
        }
    }

    return isFramePending;
}

int32_t IVTS::getMeasurement(const IVT_Msg measurement) {
    int32_t measuredValue = INT32_MIN;

    switch (measurement)
    {
    case IVTS::IVT_Msg_Result_I:
        measuredValue = m_current;
        break;

    case IVTS::IVT_Msg_Result_U1:
        measuredValue = m_voltage1;
        break;

    case IVTS::IVT_Msg_Result_U2:
        measuredValue = m_voltage2;
        break;

    case IVTS::IVT_Msg_Result_U3:
        measuredValue = m_voltage3;
        break;

    case IVTS::IVT_Msg_Result_T:
        measuredValue = m_temperature;
        break;

    case IVTS::IVT_Msg_Result_W:
        measuredValue = m_power;
        break;

    case IVTS::IVT_Msg_Result_As:
        measuredValue = m_currentCounter;
        break;

    case IVTS::IVT_Msg_Result_Wh:
        measuredValue = m_energyCounter;
        break;

    default:
        break;
    }

    return measuredValue;
}
/******************************************************************************
 * Private Methods
 *****************************************************************************/

bool IVTS::parseValue(int32_t *outputVariable, const CANFrame frame)
{
    bool isSuccess = true;
    int32_t parsedValue = 0;

    if ((6 != frame.m_dlc) || (nullptr == outputVariable))
    {
        isSuccess = false;
    }
    else
    {
        parsedValue = (frame.m_data[2] << 24) |
                      (frame.m_data[3] << 16) |
                      (frame.m_data[4] << 8) |
                      frame.m_data[5];

        *outputVariable = parsedValue;
    }
    
    return isSuccess;    
}

/******************************************************************************
 * Local Functions
 *****************************************************************************/
