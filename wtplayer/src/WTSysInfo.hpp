#pragma once

class WTSysInfo {

public:
  char* getOS();

  char* getOSVersion();

  char* getCPU();

  char* getMHZ();

  char* getRAM();

  char* getResolution();

  char* getColorDepth();

  char* getVideoCard();

  char* getVideoMfg();

  char* getVideoRAM();

  char* getVideoDriver();

  char* getSoundCard();

  char* getSoundMfg();

  char* getSoundDriver();

  char* getDSoundVer();

  char* getD3DVer();

  char* getDDrawVer();

  char* getDPlayVer();

  char* getDInputVer();
};
