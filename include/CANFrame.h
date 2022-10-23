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
 *  @brief  Format of CAN Frame
 *  @author Gabryel Reyes <gabryelrdiaz@gmail.com>
 */

#ifndef CAN_FRAME_H_
#define CAN_FRAME_H_

/******************************************************************************
 * Includes
 *****************************************************************************/

#include <stdint.h>

/******************************************************************************
 * Macros
 *****************************************************************************/

/******************************************************************************
 * Types and Classes
 *****************************************************************************/

/**
 *  Maximum Data size of a Frame.
 */
static const uint8_t FRAME_DATA_SIZE = 8;

/**
 *  Format of a CAN Frame with an empty structure
 */
struct CANFrame
{
    uint32_t m_id;                   /**< CAN ID */
    bool m_rtr;                      /**< Identifies a RTR Frame */
    bool m_extended;                 /**< Identifies an Extended Frame */
    uint8_t m_dlc;                   /**< Data Length */
    uint8_t m_data[FRAME_DATA_SIZE]; /**< Data of the Frame */

    /**
     *  Initialize Frame with default values
     */
    CANFrame() : m_id(0),
              m_rtr(false),
              m_extended(false),
              m_dlc(0)
    {
        for (int i = 0; i < FRAME_DATA_SIZE; i++)
        {
            m_data[i] = 0;
        }
    }
};

#endif /* CAN_FRAME_H_ */