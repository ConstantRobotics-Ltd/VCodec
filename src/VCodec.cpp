#include "VCodec.h"
#include "VCodecVersion.h"
#include <string>



rapidpixel::VCodec::~VCodec() = default;



std::string rapidpixel::VCodec::getVersion()
{
    return VCODEC_VERSION;
}
