#include <Arduino.h>
#include "ivts.h"
#include <CAN.h>

static IVTS gCurrentSensor;

uint32_t lastPrintTime = 0;
const uint32_t printingPeriod = 1000;

void setup()
{
    Serial.begin(115200);
    CAN.begin(500E3);
    Serial.println("Ready");
    lastPrintTime = millis();
}

void loop()
{
    // RX Routine
    if (-1 != CAN.parsePacket())
    {
        CANFrame rcvdFrame;
        rcvdFrame.m_id = CAN.packetId();
        rcvdFrame.m_extended = CAN.packetExtended();
        rcvdFrame.m_rtr = CAN.packetRtr();
        rcvdFrame.m_dlc = CAN.packetDlc();

        for (int i = 0; i < rcvdFrame.m_dlc; i++)
        {
            rcvdFrame.m_data[i] = CAN.read();
        }

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

            gCurrentSensor.processFrame(rcvdFrame);
            break;

        default:
            break;
        }
    }

    // Printing Routine
    if (printingPeriod < millis() - lastPrintTime)
    {
        lastPrintTime = millis();
        Serial.println("Current = " + String(gCurrentSensor.getMeasurement(IVTS::IVT_Msg_Result_I) / 1000));
        Serial.println("Voltage 1 = " + String(gCurrentSensor.getMeasurement(IVTS::IVT_Msg_Result_U1) / 1000));
        Serial.println("Voltage 2 = " + String(gCurrentSensor.getMeasurement(IVTS::IVT_Msg_Result_U2) / 1000));
        Serial.println("Voltage 3 = " + String(gCurrentSensor.getMeasurement(IVTS::IVT_Msg_Result_U3) / 1000));
    }
}