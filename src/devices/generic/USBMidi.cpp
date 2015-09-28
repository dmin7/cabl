/*
        ##########    Copyright (C) 2015 Vincenzo Pacella
        ##      ##    Distributed under MIT license, see file LICENSE
        ##      ##    or <http://opensource.org/licenses/MIT>
        ##      ##
##########      ############################################################# shaduzlabs.com #####*/

#include "devices/generic/USBMidi.h"
#include "comm/Transfer.h"

//--------------------------------------------------------------------------------------------------

using namespace std::placeholders;

namespace sl
{
namespace kio
{
namespace devices
{

// USBMidi specs: http://www.usb.org/developers/docs/devclass_docs/midi10.pdf

//--------------------------------------------------------------------------------------------------

USBMidi::USBMidi(tPtr<DeviceHandle> pDeviceHandle_)
  : Device(std::move(pDeviceHandle_))
{

}

//--------------------------------------------------------------------------------------------------

void USBMidi::onNoteOff(NoteOff msg_)
{

}

//--------------------------------------------------------------------------------------------------

void USBMidi::onNoteOn(NoteOn msg_)
{

}

//--------------------------------------------------------------------------------------------------

void USBMidi::onPolyPressure(PolyPressure msg_)
{

}

//--------------------------------------------------------------------------------------------------

void USBMidi::onControlChange(ControlChange msg_)
{

}

//--------------------------------------------------------------------------------------------------

void USBMidi::onProgramChange(ProgramChange msg_)
{

}

//--------------------------------------------------------------------------------------------------

void USBMidi::onChannelPressure(ChannelPressure msg_)
{

}

//--------------------------------------------------------------------------------------------------

void USBMidi::onPitchBend(PitchBend msg_)
{

}

//--------------------------------------------------------------------------------------------------

void USBMidi::onSysEx(SysEx msg_)
{

}
//--------------------------------------------------------------------------------------------------

void USBMidi::onUSysExRT(sl::midi::USysExRT msg_)
{

}
//--------------------------------------------------------------------------------------------------

void USBMidi::onUSysExNonRT(sl::midi::USysExNonRT msg_)
{

}

//--------------------------------------------------------------------------------------------------

bool USBMidi::sendSysex(const midi::SysEx& sysexMessage_)
{

  tRawData message(4);
  uint8_t nCable = 0;
  unsigned msgIndex = 0;
  int bytesToSend = sysexMessage_.data().size();

  while(bytesToSend > 0)
  {
    message[0] = (nCable << 4) | 0x04;  // Start/continue

    switch(bytesToSend)
    {
      case 1: // End with one byte
      {
        message[0] = (nCable << 4) | 0x05;
        message[1] = sysexMessage_.data()[msgIndex++];
        message[2] = 0x00;
        message[3] = 0x00;
        bytesToSend--;
        break;
      }
      case 2: // End with two bytes
      {
        message[0] = (nCable << 4) | 0x06;
        message[1] = sysexMessage_.data()[msgIndex++];
        message[2] = sysexMessage_.data()[msgIndex++];
        message[3] = 0x00;
        bytesToSend -= 2;
        break;
      }
      case 3: // End with three bytes, fall thru
      {
        message[0] = (nCable << 4) | 0x07;
      }
      default:
      {
        message[1] = sysexMessage_.data()[msgIndex++];
        message[2] = sysexMessage_.data()[msgIndex++];
        message[3] = sysexMessage_.data()[msgIndex++];
        bytesToSend -= 3;
        break;
      }
    }
    
    if(!getDeviceHandle()->write(Transfer(message), 0x02))
    {
      return false;
    }
  }
  return true;
}

//--------------------------------------------------------------------------------------------------

} // devices
} // kio
} // sl
