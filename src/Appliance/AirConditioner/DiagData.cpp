#include "Appliance/AirConditioner/DiagData.h"

namespace dudanov {
namespace midea {
namespace ac {

// Diag1
float DiagData::getVal1_8() const { return static_cast<float>((this->m_getValue(8) & 0xF0) >> 4); }
float DiagData::getRunMode() const { return static_cast<float>(this->m_getValue(9) & 0x07); }
float DiagData::getT1Temp() const { return static_cast<float>(this->m_getValue(10)-30)*0.5F; }
float DiagData::getT2Temp() const { return static_cast<float>(this->m_getValue(11)-30)*0.5F; }
float DiagData::getT3Temp() const { return static_cast<float>(this->m_getValue(12)-50)*0.5F; }
float DiagData::getT4Temp() const { return static_cast<float>(this->m_getValue(13)-50)*0.5F; }
float DiagData::getCompressorSpeed() const { return static_cast<float>(this->m_getValue(4)); }
float DiagData::getEEV()    const { return static_cast<float>(this->m_getValue(8) & 0x0F); }

// Diag2
float DiagData::getIdFTarget() const { return static_cast<float>(this->m_getValue(4)); }
float DiagData::getIdFVal() const { return static_cast<float>(this->m_getValue(5)); }
float DiagData::getVal2_12() const { return static_cast<float>(this->m_getValue(12)); }

// Diag3
float DiagData::getOdFVal() const { return static_cast<float>(this->m_getValue(10)); }
float DiagData::getCompressorTarget() const { return static_cast<float>(this->m_getValue(16)); }


static uint8_t bcd2u8(uint8_t bcd) { return 10 * (bcd >> 4) + (bcd & 15); }
// Diag4
float DiagData::getEnergyUsage() const {
  uint32_t power = 0;
  const uint8_t *ptr = this->m_data.data() + 7;
  for (uint32_t weight = 1;; weight *= 100, --ptr) {
    power += weight * bcd2u8(*ptr);
    if (weight == 10000)
      return static_cast<float>(power) * 0.1F;
  }
}

float DiagData::getPowerUsage() const {
  uint32_t power = 0;
  const uint8_t *ptr = this->m_data.data() + 18;
  for (uint32_t weight = 1;; weight *= 100, --ptr) {
    power += weight * bcd2u8(*ptr);
    if (weight == 10000)
      return static_cast<float>(power) * 0.1F;
  }
}

}  // namespace ac
}  // namespace midea
}  // namespace dudanov
