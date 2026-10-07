![vcodec_web_logo](./static/vcodec_web_logo.png)



# **VCodec interface C++ library**

**v2.2.2**



# Table of contents

- [Overview](#overview)
- [Versions](#versions)
- [Library files](#library-files)
- [VCodec interface class description](#vcodec-interface-class-description)
  - [VCodec interface class declaration](#vcodec-interface-class-declaration)
  - [transcode method](#transcode-method)
  - [setParam method](#setparam-method)
  - [getParam method](#getparam-method)
  - [executeCommand method](#executecommand-method)
- [Data structures](#data-structures)
  - [VCodecCommand enum](#vcodeccommand-enum)
  - [VCodecParam enum](#vcodecparam-enum)
- [Build and connect to your project](#build-and-connect-to-your-project)



# Overview

The **VCodec** C++ library provides a standard interface and defines data structures and rules for different video codecs (video encoding and decoding). The **VCodec** interface class does nothing; it just provides an interface. Different video codec classes inherit the interface from the **VCodec** C++ class. The **VCodec.h** file contains the **VCodecCommand** enum, **VCodecParam** enum, and **VCodec** class declaration. The **VCodecCommand** enum contains IDs of commands supported by **VCodec** class. The **VCodecParam** enum contains IDs of parameters supported by **VCodec** class. All video codecs should include all parameters and commands listed in the **VCodec.h** file. The **VCodec** class depends on the [Frame](https://rapidpixel.constantrobotics.com/docs/Service/Frame.html) class, which determines video frame structures. The video codec interface supports only 8-bit depth input pixel formats. It uses the C++17 standard.



# Versions

**Table 1** - Library versions.

| Version | Release date | What's new                                                   |
| ------- | ------------ | ------------------------------------------------------------ |
| 1.0.0   | 14.06.2023   | First version.                                               |
| 1.1.0   | 20.06.2023   | - Added new parameter.                                       |
| 1.1.1   | 28.06.2023   | - Frame submodule updated.<br />- Documentation updated.<br />- License added.<br />- Repository made public.<br />- Added new parameters. |
| 1.1.2   | 02.08.2023   | - Frame submodule updated.                                   |
| 2.1.1   | 14.12.2023   | - Virtual destructor added.<br />- Frame submodule updated.  |
| 2.1.2   | 14.12.2023   | - Frame submodule updated.<br />- Documentation updated.     |
| 2.1.3   | 25.04.2024   | - Documentation updated.                                     |
| 2.1.4   | 16.05.2024   | - Documentation updated.<br />- Frame submodule updated.     |
| 2.1.5   | 06.07.2024   | - Frame class updated.<br />- CMake updated.                 |
| 2.2.0   | 30.10.2024   | - Add new bitrate parameters.                                |
| 2.2.1   | 02.11.2025   | - Fix code mistakes.<br />- Fix documentation mistakes.      |
| 2.2.2   | 07.10.2026   | - Added compiler options.<br/>- Frame submodule updated. |



# Library files

The library is supplied as source code only. The user is provided with a set of files in the form of a CMake project (repository). The repository structure is shown below:

```xml
CMakeLists.txt ---------- Main CMake file of the library.
3rdparty ---------------- Folder with third-party libraries.
    CMakeLists.txt ------ CMake file to include third-party libraries.
    Frame --------------- Folder with Frame library files.
src --------------------- Folder with library source code.
    CMakeLists.txt ------ CMake file of the library.
    VCodec.h ------------ Main library header file.
    VCodecVersion.h ----- Header file with library version.
    VCodecVersion.h.in -- File for CMake to generate version header.
    VCodec.cpp ---------- C++ implementation file.
```



# VCodec interface class description



## VCodec interface class declaration

The **VCodec** interface class is declared in the **VCodec.h** file. Class declaration:

```cpp
class VCodec
{
public:

    /// Class destructor.
    virtual ~VCodec();

    /// Get string of the current library version.
    static std::string getVersion();

    /// Encode/decode.
    virtual bool transcode(Frame& src, Frame& dst) = 0;

    /// Set parameter.
    virtual bool setParam(VCodecParam id, float value) = 0;

    /// Get parameter.
    virtual float getParam(VCodecParam id) = 0;

    /// Execute command.
    virtual bool executeCommand(VCodecCommand id) = 0;
};
```



## getVersion method

The **getVersion()** method returns a string of the current version of the **VCodec** class. A particular video codec class can have its own **getVersion()** method. Method declaration:

```cpp
static std::string getVersion();
```

This method can be used without a **VCodec** class instance:

```cpp
std::cout << "VCodec class version: " << VCodec::getVersion() << std::endl;
```

Console output:

```bash
VCodec class version: 2.2.1
```



## transcode method

The **transcode(...)** method is intended to encode and decode video frames ([Frame](https://rapidpixel.constantrobotics.com/docs/Service/Frame.html) class). The video codec encodes/decodes video frame-by-frame. Method declaration:

```cpp
virtual bool transcode(Frame& src, Frame& dst) = 0;
```

| Parameter | Value                                                        |
| --------- | ------------------------------------------------------------ |
| src       | Source video frame (see [Frame](https://rapidpixel.constantrobotics.com/docs/Service/Frame.html) class description). To encode video data, the **src** frame must have RAW pixel data (field **fourcc** of **Frame** class): **RGB24**, **BGR24**, **YUYV**, **UYVY**, **GRAY**, **YUV24**, **NV12** (default format for codec), **NV21**, **YU12**, or **YV12**. To decode video data, the **src** frame must have compressed pixel format (field **fourcc** of **Frame** class): **JPEG**, **H264**, or **HEVC**. A particular video codec can support a limited RAW input pixel format or only one (usually only **NV12**). When possible, the video codec should accept all supported RAW pixel formats and should do pixel format conversion internally if necessary. Also, a particular video codec can support all, few, or just one compressed pixel format. When possible, the video codec should support all compressed pixel formats to encode/decode. |
| dst       | Result video frame (see [Frame](https://rapidpixel.constantrobotics.com/docs/Service/Frame.html) class description). For decoding, the output pixel format can be set automatically by the particular video codec. To encode a video frame, the user must set the **fourcc** field of the dst frame to the necessary output compressed format: **JPEG**, **H264**, or **HEVC**. The method will write decoded frame data (RAW pixel format) to the **data** field of the **dst** frame in case of decoding or will write compressed data in case of encoding. |

**Returns:** TRUE if frame was encoded/decoded or FALSE if not.



## setParam method

The **setParam(...)** method is designed to set new video codec parameter values. Method declaration:

```cpp
virtual bool setParam(VCodecParam id, float value) = 0;
```

| Parameter | Description                                                 |
| --------- | ----------------------------------------------------------- |
| id        | Video codec parameter ID according to [VCodecParam](#vcodecparam-enum) enum. |
| value     | Video codec parameter value.                                |

**Returns:** TRUE if the parameter was set or FALSE if not.



## getParam method

The **getParam(...)** method is designed to obtain video codec parameter values. Method declaration:

```cpp
virtual float getParam(VCodecParam id) = 0;
```

| Parameter | Description                                                 |
| --------- | ----------------------------------------------------------- |
| id        | Video codec parameter ID according to [VCodecParam](#vcodecparam-enum) enum. |

**Returns:** Parameter value or -1 if the parameter doesn't exist in the particular video codec class.



## executeCommand method

The **executeCommand(...)** method is designed to execute video codec commands. Method declaration:

```cpp
virtual bool executeCommand(VCodecCommand id) = 0;
```

| Parameter | Description                                                 |
| --------- | ----------------------------------------------------------- |
| id        | Video codec command ID according to [VCodecCommand](#vcodeccommand-enum) enum. |

**Returns:** TRUE if the command was executed or FALSE if not.



# Data structures

**VCodec.h** file defines IDs for parameters (**VCodecParam** enum) and IDs for commands (**VCodecCommand** enum).



## VCodecCommand enum

Enum declaration:

```cpp
enum class VCodecCommand
{
    /// Reset.
    RESET = 1,
    /// Generate key frame. For H264 and H265 codecs.
    MAKE_KEY_FRAME
};
```

**Table 2** - Video codec commands description. Some commands may be unsupported by particular video codec classes.

| Command        | Description                                                  |
| -------------- | ------------------------------------------------------------ |
| RESET          | Reset video codec.                                           |
| MAKE_KEY_FRAME | Command to generate key frame for H264 or H265(HEVC) codecs. |



## VCodecParam enum

Enum declaration:

```cpp
namespace cr
{
namespace video
{
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
    /// [read/write] Custom parameter 1. Depends on implementation.
    CUSTOM_1,
    /// [read/write] Custom parameter 2. Depends on implementation.
    CUSTOM_2,
    /// [read/write] Custom parameter 3. Depends on implementation.
    CUSTOM_3
};
}
}
```

**Table 3** - Video codec parameters description. Some parameters may be unsupported by particular video codec classes.

| Parameter        | Access       | Description                                                  |
| ---------------- | ------------ | ------------------------------------------------------------ |
| LOG_LEVEL        | read / write | Logging mode. Default values:<br/>0 - Disable.<br/>1 - Only file.<br/>2 - Only terminal.<br/>3 - File and terminal. |
| BITRATE_KBPS     | read / write | Bitrate, kbps. For H264 and H265(HEVC) encoding. According to this value, FPS, and GOP size, the video codec calculates parameters for H264 or H265(HEVC) encoding. |
| MIN_BITRATE_KBPS | read / write | Minimum bitrate, kbps. For variable bitrate mode. For H264 and H265(HEVC) encoding. |
| MAX_BITRATE_KBPS | read / write | Maximum bitrate, kbps. For variable bitrate mode. For H264 and H265(HEVC) encoding. |
| BITRATE_MODE     | read / write | Bitrate mode: 0 - constant bitrate, 1 - variable bitrate.    |
| QUALITY          | read / write | Quality 0(low quality)-100%(maximum quality). For JPEG encoding. |
| FPS              | read / write | FPS. For H264 and H265 codecs. According to this value, FPS, and GOP size, the video codec calculates parameters for H264 or H265(HEVC) encoding. |
| GOP              | read / write | GOP size (Period of key frames) for H264 or H265(HEVC) encoding. Value: 1 - each output frame is a key frame, 20 - each 20th frame is a key frame, etc. |
| H264_PROFILE     | read / write | H264 profile for H264 encoding: 0 - Baseline, 1 - Main, 2 - High. |
| TYPE             | read / write | Codec type. Depends on implementation. It can be type of backend. Some codecs may not support this parameter. |
| CUSTOM_1         | read / write | Custom parameter. Depends on particular implementation.      |
| CUSTOM_2         | read / write | Custom parameter. Depends on particular implementation.      |
| CUSTOM_3         | read / write | Custom parameter. Depends on particular implementation.      |



# Build and connect to your project

Typical commands to build **VCodec** library:

```bash
cd VCodec
git submodule update --init --recursive
mkdir build
cd build
cmake ..
make
```

If you want to connect the **VCodec** library to your CMake project as source code, you can do the following. For example, if your repository has the structure:

```bash
CMakeLists.txt
src
    CMakeList.txt
    yourLib.h
    yourLib.cpp
```

You can add the **VCodec** repository as a submodule with the following commands:

```bash
cd <your respository folder>
git submodule add https://github.com/ConstantRobotics-Ltd/VCodec.git 3rdparty/VCodec
git submodule update --init --recursive
```

In your repository folder, a **3rdparty/VCodec** folder will be created, which contains files of the **VCodec** repository with the **Frame** sub-repository. Alternatively, you can copy the **VCodec** repository folder to the **3rdparty** folder of your repository. The new structure of your repository:

```bash
CMakeLists.txt
src
    CMakeList.txt
    yourLib.h
    yourLib.cpp
3rdparty
    VCodec
```

Create a CMakeLists.txt file in the **3rdparty** folder. The CMakeLists.txt file should contain:

```cmake
cmake_minimum_required(VERSION 3.13)

################################################################################
## 3RD-PARTY
## dependencies for the project
################################################################################
project(3rdparty LANGUAGES CXX)

################################################################################
## SETTINGS
## basic 3rd-party settings before use
################################################################################
# To inherit the top-level architecture when the project is used as a submodule.
SET(PARENT ${PARENT}_YOUR_PROJECT_3RDPARTY)
# Disable self-overwriting of parameters inside included subdirectories.
SET(${PARENT}_SUBMODULE_CACHE_OVERWRITE OFF CACHE BOOL "" FORCE)

################################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the 3rd-party configuration
################################################################################
add_subdirectory(VCodec)
```

The **3rdparty/CMakeLists.txt** file adds the **VCodec** folder to your project. Your repository's new structure will be:

```bash
CMakeLists.txt
src
    CMakeList.txt
    yourLib.h
    yourLib.cpp
3rdparty
    CMakeLists.txt
    VCodec
```

Next, you need to include the 3rdparty folder in the main **CMakeLists.txt** file of your repository. Add the following line at the end of your main **CMakeLists.txt**:

```cmake
add_subdirectory(3rdparty)
```

Next, you need to include the VCodec library in your **src/CMakeLists.txt** file:

```cmake
target_link_libraries(${PROJECT_NAME} VCodec)
```

Done!