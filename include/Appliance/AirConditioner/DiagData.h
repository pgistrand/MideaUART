#pragma once
#include <Arduino.h>
#include "Frame/FrameData.h"

namespace dudanov {
namespace midea {
namespace ac {

class DiagData : public FrameData {
 public:
  DiagData() : FrameData({  0x40, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00}) {}
  DiagData(const FrameData &data) : FrameData(data) {}

  /// Copy data from another DiagData
  void copyDiag(const DiagData &p) { memcpy(this->m_data.data() + 1, p.data() + 1, 10); }

  /* TEMP Sensors */
  // Diag1
  float getRunMode() const;
  float getVal1_8() const;
  float getT1Temp() const;
  float getT2Temp() const;
  float getT3Temp() const;
  float getT4Temp() const;
  float getEEV() const;
  float getCompressorSpeed() const;
  // Diag2
  float getIdFTarget() const;
  float getIdFVal() const;
  float getVal2_12() const;
  // Diag3
  float getOdFVal() const;
  float getCompressorTarget() const;
  // Diag4
  float getEnergyUsage() const;
  float getPowerUsage() const;
};


class QueryDiagData1 : public FrameData {
 public:
  QueryDiagData1() : FrameData({0x41, 0x00, 0x00, 0x01}) { this->appendCRC(); }
};

class QueryDiagData2 : public FrameData {
 public:
  QueryDiagData2() : FrameData({0x41, 0x00, 0x00, 0x02}) { this->appendCRC(); }
};

class QueryDiagData3 : public FrameData {
 public:
  QueryDiagData3() : FrameData({0x41, 0x00, 0x00, 0x03}) { this->appendCRC(); }
};

class QueryDiagData4 : public FrameData {
 public:
  QueryDiagData4() : FrameData({0x41, 0x00, 0x00, 0x04}) { this->appendCRC(); }
};
}  // namespace ac
}  // namespace midea
}  // namespace dudanov
