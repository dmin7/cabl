/*
        ##########    Copyright (C) 2015 Vincenzo Pacella
        ##      ##    Distributed under MIT license, see file LICENSE
        ##      ##    or <http://opensource.org/licenses/MIT>
        ##      ##
##########      ############################################################# shaduzlabs.com #####*/

#pragma once

#include <array>
#include <map>

#include "devices/Device.h"

namespace sl
{
namespace cabl
{
namespace devices
{

//--------------------------------------------------------------------------------------------------

class Push2Display : public Device
{

public:

  void setLed(Device::Button, const util::LedColor&) override {}
  void setLed(Device::Pad, const util::LedColor&) override {}
  void sendMidiMsg(tRawData) override {}

  GDisplay* getGraphicDisplay(uint8_t displayIndex_) override;
  LCDDisplay* getLCDDisplay(uint8_t displayIndex_) override;
  DrawingContext& getDrawingContext(uint8_t /*contextIndex_*/) override
  {
    return m_display;
  }
  
  bool tick() override;

private:

  bool sendDisplayData();
  
  static constexpr uint8_t kPush2_nRows             = 160;
  static constexpr uint8_t kPush2_nColumns          = 1024;
  static constexpr uint8_t kPush2_nBytesPerPixel    = 2;

  void init() override;

  DrawingContext    m_display{1024, 160, 2};
};

//--------------------------------------------------------------------------------------------------

M_REGISTER_DEVICE_CLASS(Push2Display,"Ableton Push 2",DeviceDescriptor::Type::USB,0x2982,0x1967);

//--------------------------------------------------------------------------------------------------

} // devices
} // cabl
} // sl
