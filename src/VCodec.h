#pragma once
#include "Frame.h"



namespace cr
{
namespace video
{

/**
 * @brief Enum of video codec params.
 */
enum class VCodecParam
{
    /// [read/write] Log level: 0-Disable, 1-Console, 2-File, 3-Console and file.
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
    /// Custom 1. Depends on implementation.
    CUSTOM_1,
    /// Custom 2. Depends on implementation.
    CUSTOM_2,
    /// Custom 3. Depends on implementation.
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
 */
class VCodec
{
public:

    /**
     * @brief Class destructor.
     */
    virtual ~VCodec();

    /**
     * @brief Get string of current library version.
     * @return String of current library version in format "Major.Minor.Patch".
     */
    static std::string getVersion();

    /**
     * @brief Encode/decode.
     * @param src Source frame (RAW or compressed).
     * @param dst Result frame (RAW or compressed).
     * @return TRUE if frame was processed or FALSE if not.
     */
    virtual bool transcode(Frame& src, Frame& dst) = 0;

    /**
     * @brief Set parameter.
     * @param id Parameter ID.
     * @param value Parameter value to set.
     * @return TRUE if parameter was set of FALSE.
     */
    virtual bool setParam(VCodecParam id, float value) = 0;

    /**
     * @brief Get parameter.
     * @param id Parameter ID.
     * @return Parameter value or -1.
     */
    virtual float getParam(VCodecParam id) = 0;

    /**
     * @brief Execute command.
     * @param id Command ID .
     * @return TRUE if the command accepted or FALSE if not.
     */
    virtual bool executeCommand(VCodecCommand id) = 0;
};
}
}