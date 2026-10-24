#pragma once
#include "Frame.h"
#include <string>



namespace rapidpixel
{

/**
 * @brief Enum of video codec params.
 */
enum class VCodecParam
{
    /// [read/write] Log level: 0 - Disable, 1 - Console, 2 - File,
    /// 3 - Console and file.
    LOG_LEVEL = 1,
    /// [read/write] Bitrate, kbps. For H264 and H265 codecs.
    BITRATE_KBPS,
    /// [read/write] Minimum bitrate, kbps. For variable bitrate mode.
    MIN_BITRATE_KBPS,
    /// [read/write] Maximum bitrate, kbps. For variable bitrate mode.
    MAX_BITRATE_KBPS,
    /// [read/write] Bitrate mode: 0 - constant bitrate, 1 - variable bitrate.
    BITRATE_MODE,
    /// [read/write] Quality 0-100%. For JPEG codecs.
    QUALITY,
    /// [read/write] FPS. For H264 and H265 codecs.
    FPS,
    /// [read/write] GOP size. For H264 and H265 codecs.
    GOP,
    /// [read/write] H264 profile: 0 - Baseline, 1 - Main, 2 - High.
    H264_PROFILE,
    /// [read/write] Codec type. Depends on implementation.
    TYPE,
    /// [read/write] Custom parameter 1. Depends on implementation.
    CUSTOM_1,
    /// [read/write] Custom parameter 2. Depends on implementation.
    CUSTOM_2,
    /// [read/write] Custom parameter 3. Depends on implementation.
    CUSTOM_3
};



/**
 * @brief Enum of video codec commands.
 */
enum class VCodecCommand
{
    /// Reset.
    RESET = 1,
    /// Generate key frame. For H264 and H265 codecs.
    MAKE_KEY_FRAME
};



/**
 * @brief Video codec interface class.
 *
 * The class can be used only as a base class of a video codec
 * implementation. Thread safety of the methods is defined by the
 * implementation.
 */
class VCodec
{
public:

    /**
     * @brief Class destructor.
     */
    virtual ~VCodec();

    /**
     * @brief Get string of the current library version.
     * @return String of the current library version in format
     * "Major.Minor.Patch".
     */
    static std::string getVersion();

    /**
     * @brief Encode/decode.
     *
     * The data of the source frame can come from outside: the implementation
     * must check the source frame (pixel format, size of the data, frame
     * dimensions) before use.
     *
     * @param src Source frame (RAW or compressed).
     * @param dst Result frame (RAW or compressed).
     * @return TRUE if frame was processed or FALSE if not. If FALSE is
     * returned the content of the dst frame is defined by the implementation.
     */
    virtual bool transcode(Frame& src, Frame& dst) = 0;

    /**
     * @brief Set parameter.
     *
     * The interface does not check the arguments: the implementation must
     * reject an ID that it does not support (also a value outside of the
     * VCodecParam enum) and must check the value (range, NaN, infinity)
     * before use.
     *
     * @param id Parameter ID.
     * @param value Parameter value to set.
     * @return TRUE if parameter was set or FALSE if not.
     */
    virtual bool setParam(VCodecParam id, float value) = 0;

    /**
     * @brief Get parameter.
     * @param id Parameter ID.
     * @return Parameter value or -1 if the implementation does not support
     * the parameter.
     */
    virtual float getParam(VCodecParam id) = 0;

    /**
     * @brief Execute command.
     *
     * The interface does not check the ID: the implementation must reject an
     * ID that it does not support (also a value outside of the VCodecCommand
     * enum).
     *
     * @param id Command ID.
     * @return TRUE if the command is accepted or FALSE if not.
     */
    virtual bool executeCommand(VCodecCommand id) = 0;

protected:

    /**
     * @brief Default constructor. The class can be used as a base only.
     */
    VCodec() = default;

    /**
     * @brief Copy constructor.
     * @param src Source object.
     */
    VCodec(const VCodec& src) = default;

    /**
     * @brief Move constructor.
     * @param src Source object.
     */
    VCodec(VCodec&& src) = default;

    /**
     * @brief Copy assignment operator.
     * @param src Source object.
     * @return Reference to this object.
     */
    VCodec& operator=(const VCodec& src) = default;

    /**
     * @brief Move assignment operator.
     * @param src Source object.
     * @return Reference to this object.
     */
    VCodec& operator=(VCodec&& src) = default;
};
}



// Compatibility: the names of namespace rapidpixel are also available in
// namespace cr::video.
namespace cr
{
namespace video
{
using namespace ::rapidpixel;
}
}