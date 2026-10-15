#include "VCodec.h"
#include "VCodecVersion.h"
#include <string>



cr::video::VCodec::~VCodec() = default;



std::string cr::video::VCodec::getVersion()
{
    return VCODEC_VERSION;
}
