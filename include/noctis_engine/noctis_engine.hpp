#pragma once

#if defined(_MSC_VER)
    // Disable warning from using STL members in classes    
#   pragma warning(disable : 4251)
#endif

#if defined(_WIN32) || defined(_WIN64)
#   ifdef NCENG_BUILD
#       define NCENG_API __declspec(dllexport)
#   else
#       define NCENG_API __declspec(dllimport)
#   endif
#else
#   define NCENG_API
#endif

namespace NoctisEngine
{

constexpr const char *OPENGL_VERSION = "#version 460 core";

} // namespace NoctisEngine
