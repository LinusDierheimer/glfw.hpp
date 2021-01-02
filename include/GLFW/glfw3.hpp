#pragma once

#ifndef _glfw3_hpp_
#define _glfw3_hpp_

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <system_error>
#include <functional>
#include <string>
#include <memory>
#include <type_traits>
#include <initializer_list>
#include <array>
#include <vector>
#include <GLFW/glfw3.h>

#if defined( _MSVC_LANG )
#  define GLFW_HPP_CPLUSPLUS _MSVC_LANG
#else
#  define GLFW_HPP_CPLUSPLUS __cplusplus
#endif

#if 201703L < GLFW_HPP_CPLUSPLUS
#  define GLFW_HPP_CPP_VERSION 20
#elif 201402L < GLFW_HPP_CPLUSPLUS
#  define GLFW_HPP_CPP_VERSION 17
#elif 201103L < GLFW_HPP_CPLUSPLUS
#  define GLFW_HPP_CPP_VERSION 14
#elif 199711L < GLFW_HPP_CPLUSPLUS
#  define GLFW_HPP_CPP_VERSION 11
#else
#  error "glfw.hpp needs at least c++ standard version 11"
#endif

#define GLFW_HPP_INLINE inline
#define GLFW_HPP_CONSTEXPR constexpr
#define GLFW_HPP_NOEXCEPT noexcept
#define GLFW_HPP_DEPRECATED [[ deprecated ]]

#if !defined(GLFW_HPP_NAMESPACE_NAME)
    #define GLFW_HPP_NAMESPACE_NAME glfw
#endif

#define GLFW_HPP_STRINGIFY2(text) #text
#define GLFW_HPP_STRINGIFY(text) GLFW_HPP_STRINGIFY2(text)
#define GLFW_HPP_NAMESPACE_STRING GLFW_HPP_STRINGIFY(GLFW_HPP_NAMESPACE)

namespace GLFW_HPP_NAMESPACE_NAME
{

    namespace _glfw_hpp_internal
    {
        template <typename RefType>
        class Optional
        {
        private:
            RefType *refPtr;
        public:
            Optional(RefType& reference) GLFW_HPP_NOEXCEPT
                : refPtr(&reference)
            {}

            Optional(RefType* ptr) GLFW_HPP_NOEXCEPT
                : refPtr(ptr)
            {}

            operator RefType*() const GLFW_HPP_NOEXCEPT
            {
                return this->refPtr;
            }

            RefType const* operator->() const GLFW_HPP_NOEXCEPT
            {
                return this->refPtr;
            }

            explicit operator bool() const GLFW_HPP_NOEXCEPT
            {
                return !!this->refPtr;
            }

            RefType& ref()
            {
                return *this->refPtr;
            }
        };
    }

    constexpr int version_major    = GLFW_VERSION_MAJOR;
    constexpr int version_minor    = GLFW_VERSION_MINOR;
    constexpr int version_revision = GLFW_VERSION_REVISION;

    enum class ButtonAction
    {
        eRelease = GLFW_RELEASE,
        ePress   = GLFW_PRESS,
        eRepeat  = GLFW_REPEAT
    };

    GLFW_HPP_INLINE ::std::string to_string(ButtonAction action)
    {
        switch (action)
        {
            case ButtonAction::eRelease: return "release";
            case ButtonAction::ePress:   return "press";
            case ButtonAction::eRepeat:  return "repeat";
            default:                     return "_Invalid";
        }
    }

    enum class DeviceAction
    {
        eConnected = GLFW_CONNECTED,
        eDisconnected = GLFW_DISCONNECTED
    };

    enum class Key
    {
        eUnknown      = GLFW_KEY_UNKNOWN,
        eSpace        = GLFW_KEY_SPACE,
        eApostrophe   = GLFW_KEY_APOSTROPHE,
        eComma        = GLFW_KEY_COMMA,
        eMinus        = GLFW_KEY_MINUS,
        ePeriod       = GLFW_KEY_PERIOD,
        eSlash        = GLFW_KEY_SLASH,
        e0            = GLFW_KEY_0,
        e1            = GLFW_KEY_1,
        e2            = GLFW_KEY_2,
        e3            = GLFW_KEY_3,
        e4            = GLFW_KEY_4,
        e5            = GLFW_KEY_5,
        e6            = GLFW_KEY_6,
        e7            = GLFW_KEY_7,
        e8            = GLFW_KEY_8,
        e9            = GLFW_KEY_9,
        eSemicolon    = GLFW_KEY_SEMICOLON,
        eEqual        = GLFW_KEY_EQUAL,
        eA            = GLFW_KEY_A,
        eB            = GLFW_KEY_B,
        eC            = GLFW_KEY_C,
        eD            = GLFW_KEY_D,
        eE            = GLFW_KEY_E,
        eF            = GLFW_KEY_F,
        eG            = GLFW_KEY_G,
        eH            = GLFW_KEY_H,
        eI            = GLFW_KEY_I,
        eJ            = GLFW_KEY_J,
        eK            = GLFW_KEY_K,
        eL            = GLFW_KEY_L,
        eM            = GLFW_KEY_M,
        eN            = GLFW_KEY_N,
        eO            = GLFW_KEY_O,
        eP            = GLFW_KEY_P,
        eQ            = GLFW_KEY_Q,
        eR            = GLFW_KEY_R,
        eS            = GLFW_KEY_S,
        eT            = GLFW_KEY_T,
        eU            = GLFW_KEY_U,
        eV            = GLFW_KEY_V,
        eW            = GLFW_KEY_W,
        eX            = GLFW_KEY_X,
        eY            = GLFW_KEY_Y,
        eZ            = GLFW_KEY_Z,
        eLeftBracket  = GLFW_KEY_LEFT_BRACKET,
        eBackslash    = GLFW_KEY_BACKSLASH,
        eRightBracket = GLFW_KEY_RIGHT_BRACKET,
        eGraveAccent  = GLFW_KEY_GRAVE_ACCENT,
        eWorld1       = GLFW_KEY_WORLD_1,
        eWorld2       = GLFW_KEY_WORLD_2,
        eEscape       = GLFW_KEY_ESCAPE,
        eEnter        = GLFW_KEY_ENTER,
        eTab          = GLFW_KEY_TAB,
        eBackspace    = GLFW_KEY_BACKSPACE,
        eInsert       = GLFW_KEY_INSERT,
        eDelete       = GLFW_KEY_DELETE,
        eRight        = GLFW_KEY_RIGHT,
        eLeft         = GLFW_KEY_LEFT,
        eDown         = GLFW_KEY_DOWN,
        eUp           = GLFW_KEY_UP,
        ePageUp       = GLFW_KEY_PAGE_UP,
        ePageDown     = GLFW_KEY_PAGE_DOWN,
        eHome         = GLFW_KEY_HOME,
        eEnd          = GLFW_KEY_END,
        eCapsLock     = GLFW_KEY_CAPS_LOCK,
        eScrollLock   = GLFW_KEY_SCROLL_LOCK,
        eNumLock      = GLFW_KEY_NUM_LOCK,
        ePrintScreen  = GLFW_KEY_PRINT_SCREEN,
        ePause        = GLFW_KEY_PAUSE,
        eF1           = GLFW_KEY_F1,
        eF2           = GLFW_KEY_F2,
        eF3           = GLFW_KEY_F3,
        eF4           = GLFW_KEY_F4,
        eF5           = GLFW_KEY_F5,
        eF6           = GLFW_KEY_F6,
        eF7           = GLFW_KEY_F7,
        eF8           = GLFW_KEY_F8,
        eF9           = GLFW_KEY_F9,
        eF10          = GLFW_KEY_F10,
        eF11          = GLFW_KEY_F11,
        eF12          = GLFW_KEY_F12,
        eF13          = GLFW_KEY_F13,
        eF14          = GLFW_KEY_F14,
        eF15          = GLFW_KEY_F15,
        eF16          = GLFW_KEY_F16,
        eF17          = GLFW_KEY_F17,
        eF18          = GLFW_KEY_F18,
        eF19          = GLFW_KEY_F19,
        eF20          = GLFW_KEY_F20,
        eF21          = GLFW_KEY_F21,
        eF22          = GLFW_KEY_F22,
        eF23          = GLFW_KEY_F23,
        eF24          = GLFW_KEY_F24,
        eF25          = GLFW_KEY_F25,
        eKp0          = GLFW_KEY_KP_0,
        eKp1          = GLFW_KEY_KP_1,
        eKp2          = GLFW_KEY_KP_2,
        eKp3          = GLFW_KEY_KP_3,
        eKp4          = GLFW_KEY_KP_4,
        eKp5          = GLFW_KEY_KP_5,
        eKp6          = GLFW_KEY_KP_6,
        eKp7          = GLFW_KEY_KP_7,
        eKp8          = GLFW_KEY_KP_8,
        eKp9          = GLFW_KEY_KP_9,
        eKpDecimal    = GLFW_KEY_KP_DECIMAL,
        eKpDivide     = GLFW_KEY_KP_DIVIDE,
        eKpMultiply   = GLFW_KEY_KP_MULTIPLY,
        eKpSubtract   = GLFW_KEY_KP_SUBTRACT,
        eKpAdd        = GLFW_KEY_KP_ADD,
        eKpEnter      = GLFW_KEY_KP_ENTER,
        eKpEqual      = GLFW_KEY_KP_EQUAL,
        eLeftShift    = GLFW_KEY_LEFT_SHIFT,
        eLeftControl  = GLFW_KEY_LEFT_CONTROL,
        eLeftAlt      = GLFW_KEY_LEFT_ALT,
        eLeftSuper    = GLFW_KEY_LEFT_SUPER,
        eRightShift   = GLFW_KEY_RIGHT_SHIFT,
        eRightControl = GLFW_KEY_RIGHT_CONTROL,
        eRightAlt     = GLFW_KEY_RIGHT_ALT,
        eRightSuper   = GLFW_KEY_RIGHT_SUPER,
        eMenu         = GLFW_KEY_MENU,
        eLast         = GLFW_KEY_LAST,
    };

    GLFW_HPP_INLINE ::std::string to_string(Key value)
    {
        switch (value)
        {
            case Key::eUnknown:      return "Unknown";
            case Key::eSpace:        return "Space";
            case Key::eApostrophe:   return "Apostrope";
            case Key::eComma:        return "Comma";
            case Key::eMinus:        return "Minus";
            case Key::ePeriod:       return "Period";
            case Key::eSlash:        return "Slash";
            case Key::e0:            return "0";
            case Key::e1:            return "1";
            case Key::e2:            return "2";
            case Key::e3:            return "3";
            case Key::e4:            return "4";
            case Key::e5:            return "5";
            case Key::e6:            return "6";
            case Key::e7:            return "7";
            case Key::e8:            return "8";
            case Key::e9:            return "9";
            case Key::eSemicolon:    return "Semicolon";
            case Key::eEqual:        return "Equal";
            case Key::eA:            return "A";
            case Key::eB:            return "B";
            case Key::eC:            return "C";
            case Key::eD:            return "D";
            case Key::eE:            return "E";
            case Key::eF:            return "F";
            case Key::eG:            return "G";
            case Key::eH:            return "H";
            case Key::eI:            return "I";
            case Key::eJ:            return "J";
            case Key::eK:            return "K";
            case Key::eL:            return "L";
            case Key::eM:            return "M";
            case Key::eN:            return "N";
            case Key::eO:            return "O";
            case Key::eP:            return "P";
            case Key::eQ:            return "Q";
            case Key::eR:            return "R";
            case Key::eS:            return "S";
            case Key::eT:            return "T";
            case Key::eU:            return "U";
            case Key::eV:            return "V";
            case Key::eW:            return "W";
            case Key::eX:            return "X";
            case Key::eY:            return "Y";
            case Key::eZ:            return "Z";
            case Key::eLeftBracket:  return "LeftBracket";
            case Key::eBackslash:    return "Backslash";
            case Key::eRightBracket: return "RightBracket";
            case Key::eGraveAccent:  return "GraveAccent";
            case Key::eWorld1:       return "World1";
            case Key::eWorld2:       return "World2";
            case Key::eEscape:       return "Escape";
            case Key::eEnter:        return "Enter";
            case Key::eTab:          return "Tab";
            case Key::eBackspace:    return "Backspace";
            case Key::eInsert:       return "Insert";
            case Key::eDelete:       return "Delete";
            case Key::eRight:        return "Right";
            case Key::eLeft:         return "Left";
            case Key::eDown:         return "Down";
            case Key::eUp:           return "Up";
            case Key::ePageUp:       return "PageUp";
            case Key::ePageDown:     return "PageDown";
            case Key::eHome:         return "Home";
            case Key::eEnd:          return "End";
            case Key::eCapsLock:     return "CapsLock";
            case Key::eScrollLock:   return "ScrollLock";
            case Key::eNumLock:      return "NumLock";
            case Key::ePrintScreen:  return "PrintScreen";
            case Key::ePause:        return "Pause";
            case Key::eF1:           return "F1";
            case Key::eF2:           return "F2";
            case Key::eF3:           return "F3";
            case Key::eF4:           return "F4";
            case Key::eF5:           return "F5";
            case Key::eF6:           return "F6";
            case Key::eF7:           return "F7";
            case Key::eF8:           return "F8";
            case Key::eF9:           return "F9";
            case Key::eF10:          return "F10";
            case Key::eF11:          return "F11";
            case Key::eF12:          return "F12";
            case Key::eF13:          return "F13";
            case Key::eF14:          return "F14";
            case Key::eF15:          return "F15";
            case Key::eF16:          return "F16";
            case Key::eF17:          return "F17";
            case Key::eF18:          return "F18";
            case Key::eF19:          return "F19";
            case Key::eF20:          return "F20";
            case Key::eF21:          return "F21";
            case Key::eF22:          return "F22";
            case Key::eF23:          return "F23";
            case Key::eF24:          return "F24";
            case Key::eF25:          return "F25";
            case Key::eKp0:          return "Kp0";
            case Key::eKp1:          return "Kp1";
            case Key::eKp2:          return "Kp2";
            case Key::eKp3:          return "Kp3";
            case Key::eKp4:          return "Kp4";
            case Key::eKp5:          return "Kp5";
            case Key::eKp6:          return "Kp6";
            case Key::eKp7:          return "Kp7";
            case Key::eKp8:          return "Kp8";
            case Key::eKp9:          return "Kp9";
            case Key::eKpDecimal:    return "KpDecimal";
            case Key::eKpDivide:     return "KpDivide";
            case Key::eKpMultiply:   return "KpMultiply";
            case Key::eKpSubtract:   return "KpSubtract";
            case Key::eKpAdd:        return "KpAdd";
            case Key::eKpEnter:      return "KpEnter";
            case Key::eKpEqual:      return "KpEqual";
            case Key::eLeftShift:    return "LeftShift";
            case Key::eLeftControl:  return "LeftControl";
            case Key::eLeftAlt:      return "LeftAlt";
            case Key::eLeftSuper:    return "LeftSuper";
            case Key::eRightShift:   return "RightShift";
            case Key::eRightControl: return "RightControl";
            case Key::eRightAlt:     return "RightAlt";
            case Key::eRightSuper:   return "RightSuper";
            case Key::eMenu:         return "Menu";
            default:                 return "_Invalid";
        }
    };

    enum class Hat
    {
        eCentered  = GLFW_HAT_CENTERED,
        eUp        = GLFW_HAT_UP,
        eRight     = GLFW_HAT_RIGHT,
        eDown      = GLFW_HAT_DOWN,
        eLeft      = GLFW_HAT_LEFT,
        eRightUp   = GLFW_HAT_RIGHT_UP,
        eRightDown = GLFW_HAT_RIGHT_DOWN,
        eLeftUp    = GLFW_HAT_LEFT_UP,
        eLeftDown  = GLFW_HAT_LEFT_DOWN
    };

    using KeyMod = int;

    enum class KeyModBits
    {
        eShift    = GLFW_MOD_SHIFT,
        eControl  = GLFW_MOD_CONTROL,
        eAlt      = GLFW_MOD_ALT,
        eSuper    = GLFW_MOD_SUPER,
        eCapsLock = GLFW_MOD_CAPS_LOCK,
        eNumLock  = GLFW_MOD_NUM_LOCK
    };

    GLFW_HPP_INLINE ::std::string to_string(KeyModBits keyMod)
    {
        switch (keyMod)
        {
            case KeyModBits::eShift:    return "shift";
            case KeyModBits::eControl:  return "control";
            case KeyModBits::eAlt:      return "alt";
            case KeyModBits::eSuper:    return "super";
            case KeyModBits::eCapsLock: return "capsLock";
            case KeyModBits::eNumLock:  return "numLock";
            default:                    return "_Invalid";
        }
    }

    enum class MouseButton
    {
        e1      = GLFW_MOUSE_BUTTON_1,
        e2      = GLFW_MOUSE_BUTTON_2,
        e3      = GLFW_MOUSE_BUTTON_3,
        e4      = GLFW_MOUSE_BUTTON_4,
        e5      = GLFW_MOUSE_BUTTON_5,
        e6      = GLFW_MOUSE_BUTTON_6,
        e7      = GLFW_MOUSE_BUTTON_7,
        e8      = GLFW_MOUSE_BUTTON_8,
        eLeft   = GLFW_MOUSE_BUTTON_LEFT,
        eRight  = GLFW_MOUSE_BUTTON_RIGHT,
        eMiddle = GLFW_MOUSE_BUTTON_MIDDLE,
        eLast   = GLFW_MOUSE_BUTTON_LAST
    };

    enum class GamepadButton
    {
        eA           = GLFW_GAMEPAD_BUTTON_A,
        eB           = GLFW_GAMEPAD_BUTTON_B,
        eX           = GLFW_GAMEPAD_BUTTON_X,
        eY           = GLFW_GAMEPAD_BUTTON_Y,
        eLeftBumper  = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
        eRightBumper = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,
        eSack        = GLFW_GAMEPAD_BUTTON_BACK,
        eStart       = GLFW_GAMEPAD_BUTTON_START,
        eGuide       = GLFW_GAMEPAD_BUTTON_GUIDE,
        eLeftThumb   = GLFW_GAMEPAD_BUTTON_LEFT_THUMB,
        eRightThumb  = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,
        eDpadUp      = GLFW_GAMEPAD_BUTTON_DPAD_UP,
        eDpadRight   = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,
        eDpadDown    = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,
        eDpadLeft    = GLFW_GAMEPAD_BUTTON_DPAD_LEFT,
        eLast        = GLFW_GAMEPAD_BUTTON_LAST,
        eCross       = GLFW_GAMEPAD_BUTTON_CROSS,
        eCircle      = GLFW_GAMEPAD_BUTTON_CIRCLE,
        eSquare      = GLFW_GAMEPAD_BUTTON_SQUARE,
        eTriangle    = GLFW_GAMEPAD_BUTTON_TRIANGLE
    };

    enum class GamepadAxis
    {
        eLeftX        = GLFW_GAMEPAD_AXIS_LEFT_X,
        eLeftY        = GLFW_GAMEPAD_AXIS_LEFT_Y,
        eRightX       = GLFW_GAMEPAD_AXIS_RIGHT_X,
        eRightY       = GLFW_GAMEPAD_AXIS_RIGHT_Y,
        eLeftTrigger  = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER,
        eRightTrigger = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER,
        eLast         = GLFW_GAMEPAD_AXIS_LAST
    };

    enum class CursorInputMode
    {
        eNormal = GLFW_CURSOR_NORMAL,
        eHidden = GLFW_CURSOR_HIDDEN,
        eDisabled = GLFW_CURSOR_DISABLED
    };

    namespace InputMode
    {
        namespace _glfw_hpp_internal
        {
            template<typename ValueType>
            class InputMode
            {
            private:
                int id;
            public:
                InputMode(int id)
                    : id(id)
                {}
                operator int() const noexcept
                {
                    return id;
                }
            };

            template<typename T>
            int toNativeValue(T value)
            {
                return static_cast<int>(value);
            }

            template<>
            int toNativeValue(bool value)
            {
                return value ? GLFW_TRUE : GLFW_FALSE;
            }

            template<typename T>
            T fromNativeValue(int value)
            {
                return static_cast<T>(value);
            }

            template<>
            bool fromNativeValue(int value)
            {
                return value != GLFW_FALSE;
            }
        }

        const _glfw_hpp_internal::InputMode<CursorInputMode> eCursor(GLFW_CURSOR);
        const _glfw_hpp_internal::InputMode<bool>            eStickyKeys(GLFW_STICKY_KEYS);
        const _glfw_hpp_internal::InputMode<bool>            eStickyMouseButtons(GLFW_STICKY_MOUSE_BUTTONS);
        const _glfw_hpp_internal::InputMode<bool>            eLockKeyMods(GLFW_LOCK_KEY_MODS);
        const _glfw_hpp_internal::InputMode<bool>            eRawMouseMotion(GLFW_RAW_MOUSE_MOTION);
    }

    enum class Result : int
    {
        eNoError              = GLFW_NO_ERROR,
        eNotInitialized       = GLFW_NOT_INITIALIZED,
        eNoCurrentContext     = GLFW_NO_CURRENT_CONTEXT,
        eInvalidEnum          = GLFW_INVALID_ENUM,
        eInvalidValue         = GLFW_INVALID_VALUE,
        eOutOfMemory          = GLFW_OUT_OF_MEMORY,
        eApiUnavailable       = GLFW_API_UNAVAILABLE,
        eVersionUnavailable   = GLFW_VERSION_UNAVAILABLE,
        ePlatformError        = GLFW_PLATFORM_ERROR,
        eFormatUnavailable    = GLFW_FORMAT_UNAVAILABLE,
        eNoWindowContext      = GLFW_NO_WINDOW_CONTEXT,
        eCursorUnavailable    = GLFW_CURSOR_UNAVAILABLE,
        eFeatureUnavailable   = GLFW_FEATURE_UNAVAILABLE,
        eFeatureUnimplemented = GLFW_FEATURE_UNIMPLEMENTED
    };

    GLFW_HPP_INLINE ::std::string to_string(Result value)
    {
        switch (value)
        {
            case Result::eNoError:              return "NoError";
            case Result::eNotInitialized:       return "NotInitialized";
            case Result::eNoCurrentContext:     return "NoCurrentContext";
            case Result::eInvalidEnum:          return "InvalidEnum";
            case Result::eOutOfMemory:          return "OutOfMemory";
            case Result::eApiUnavailable:       return "ApiUnavailable";
            case Result::eVersionUnavailable:   return "VersionUnavailable";
            case Result::ePlatformError:        return "PlatformError";
            case Result::eFormatUnavailable:    return "FormatUnavailable";
            case Result::eNoWindowContext:      return "NoWindowContext";
            case Result::eCursorUnavailable:    return "CursorUnavailable";
            case Result::eFeatureUnavailable:   return "FeatureUnavailable";
            case Result::eFeatureUnimplemented: return "FeatureUnimplemented";
            default:                            return "_Invalid"; //TODO: add hex string of value
        }
    }

    GLFW_HPP_INLINE Result make_result(int error)
    {
        if(error >= GLFW_NO_ERROR && error <= GLFW_FEATURE_UNIMPLEMENTED)
            return static_cast<Result>(error);
        return Result::ePlatformError;
    }

    struct ResultMessage
    {
        Result result;
        const char* message;
    };

    GLFW_HPP_INLINE ::std::string to_string(const ResultMessage& resultMessage)
    {
        return to_string(resultMessage.result) + ": " + resultMessage.message;
    }

}

namespace std
{
    template <>
    struct is_error_code_enum<GLFW_HPP_NAMESPACE_NAME::Result> : public true_type
    {};
}

namespace GLFW_HPP_NAMESPACE_NAME
{

    namespace _glfw_hpp_internal
    {
        class :
            public ::std::error_category
        {
        public:
            virtual const char* name() const noexcept override
            {
                return "glfw::Result";

            }
            virtual std::string message(int ev) const override
            {
                return ::GLFW_HPP_NAMESPACE_NAME::to_string(
                    ::GLFW_HPP_NAMESPACE_NAME::make_result(ev)
                );
            }
        } errorCategory;
    }

    class GlfwError :
        public ::std::system_error
    {
    public:
        using system_error::system_error;
    };

    GLFW_HPP_INLINE ::std::error_code make_error_code(Result result) noexcept
    {
        return ::std::error_code(static_cast<int>(result), _glfw_hpp_internal::errorCategory);
    }

    #define GLFW_HPP_CREATE_ERROR(NAME, RESULT) \
        class NAME : \
            public GlfwError \
        { \
        public: \
            NAME(const ::std::string& message) : GlfwError(make_error_code(Result::RESULT), message) {} \
            NAME(const char* message)          : GlfwError(make_error_code(Result::RESULT), message) {} \
        };

    GLFW_HPP_CREATE_ERROR(NotInitializedError, eNotInitialized)
    GLFW_HPP_CREATE_ERROR(NoCurrentContextError, eNoCurrentContext)
    GLFW_HPP_CREATE_ERROR(InvalidEnumError, eInvalidEnum)
    GLFW_HPP_CREATE_ERROR(OutOfMemoryError, eOutOfMemory)
    GLFW_HPP_CREATE_ERROR(ApiUnavailableError, eApiUnavailable)
    GLFW_HPP_CREATE_ERROR(VersionUnavailableError, eVersionUnavailable)
    GLFW_HPP_CREATE_ERROR(PlatformError, ePlatformError)
    GLFW_HPP_CREATE_ERROR(FormatUnavailableError, eFormatUnavailable)
    GLFW_HPP_CREATE_ERROR(NoWindowContextError, eNoWindowContext)
    GLFW_HPP_CREATE_ERROR(CursorUnavailableError, eCursorUnavailable)
    GLFW_HPP_CREATE_ERROR(FeatureUnavailableError, eFeatureUnavailable)
    GLFW_HPP_CREATE_ERROR(FeatureUnimplementedError, eFeatureUnimplemented)

    [[ noreturn ]]
    void throw_result_exception(Result result, const char* message)
    {
        switch (result)
        {
            case Result::eNotInitialized:       throw NotInitializedError(message);
            case Result::eNoCurrentContext:     throw NoCurrentContextError(message);
            case Result::eInvalidEnum:          throw InvalidEnumError(message);
            case Result::eOutOfMemory:          throw OutOfMemoryError(message);
            case Result::eApiUnavailable:       throw ApiUnavailableError(message);
            case Result::ePlatformError:        throw PlatformError(message);
            case Result::eFormatUnavailable:    throw FormatUnavailableError(message);
            case Result::eNoWindowContext:      throw NoWindowContextError(message);
            case Result::eCursorUnavailable:    throw CursorUnavailableError(message);
            case Result::eFeatureUnavailable:   throw FeatureUnavailableError(message);
            case Result::eFeatureUnimplemented: throw FeatureUnimplementedError(message);
            default:                            throw GlfwError(make_error_code(result), message);
        };
    }

    [[ noreturn ]]
    GLFW_HPP_INLINE void throw_result_exception(ResultMessage resultMessage)
    {
        throw_result_exception(resultMessage.result, resultMessage.message);
    }

    GLFW_HPP_INLINE Result getError(const char** description) noexcept
    {
        return make_result(glfwGetError(description));
    }

    GLFW_HPP_INLINE ResultMessage getError() noexcept
    {
        const char* message;
        auto result = make_result(glfwGetError(&message));

        return {result, message};
    }

    GLFW_HPP_INLINE void check_last_error()
    {
        auto resultMessage = getError();
        if(resultMessage.result != Result::eNoError)
            throw_result_exception(resultMessage);
    }

    namespace Hint
    {
        namespace _glfw_hpp_internal
        {
            template<typename ValueType>
            class Hint
            {
            private:
                int id;
                ValueType defaultValue;
            public:
                Hint(int id, ValueType defaultValue) :
                    id(id), defaultValue(defaultValue) {}

                operator int() const noexcept
                {
                    return id;
                }

                const ValueType& getDefaultValue() const
                {
                    return this->defaultValue;
                }

            };

            class InitHint :
                public virtual Hint<bool>
            {
            public:
                using Hint::Hint;
            };

            template<typename T>
            class WindowHint :
                public virtual Hint<T>
            {
            public:
                using Hint<T>::Hint;
            };

            template<typename T>
            int nativeValue(T value)
            {
                return static_cast<int>(value);
            }

            template<>
            int nativeValue(bool value)
            {
                return value ? GLFW_TRUE : GLFW_FALSE;
            }

        }

        const _glfw_hpp_internal::InitHint eJoystickHatButtons(GLFW_JOYSTICK_HAT_BUTTONS, true);
        const _glfw_hpp_internal::InitHint eCocoaChdirResources(GLFW_COCOA_CHDIR_RESOURCES, true);
        const _glfw_hpp_internal::InitHint eCocoaMenuBar(GLFW_COCOA_MENUBAR, true);

        // Window related

        const _glfw_hpp_internal::WindowHint<bool> eFocused(GLFW_FOCUSED, true);
        const _glfw_hpp_internal::WindowHint<bool> eIconified(GLFW_ICONIFIED, false);
        const _glfw_hpp_internal::WindowHint<bool> eResizable(GLFW_RESIZABLE, true);
        const _glfw_hpp_internal::WindowHint<bool> eVisible(GLFW_VISIBLE, true);
        const _glfw_hpp_internal::WindowHint<bool> eDecorated(GLFW_DECORATED, true);
        const _glfw_hpp_internal::WindowHint<bool> eAutoIconify(GLFW_AUTO_ICONIFY, true);
        const _glfw_hpp_internal::WindowHint<bool> eFloating(GLFW_FLOATING, false);
        const _glfw_hpp_internal::WindowHint<bool> eMaximized(GLFW_MAXIMIZED, false);
        const _glfw_hpp_internal::WindowHint<bool> eCenterCursor(GLFW_CENTER_CURSOR, true);
        const _glfw_hpp_internal::WindowHint<bool> eTransparentFramebuffer(GLFW_TRANSPARENT_FRAMEBUFFER, false);
        const _glfw_hpp_internal::WindowHint<bool> eFocusOnShow(GLFW_FOCUS_ON_SHOW, true);
        const _glfw_hpp_internal::WindowHint<bool> eScaleToMonitor(GLFW_SCALE_TO_MONITOR, false);

        //Framebuffer related

        const _glfw_hpp_internal::WindowHint<bool> eStereo(GLFW_STEREO, false);
        const _glfw_hpp_internal::WindowHint<bool> eSrgbCapable(GLFW_SRGB_CAPABLE, false);
        const _glfw_hpp_internal::WindowHint<bool> eDoublebuffer(GLFW_DOUBLEBUFFER, true);

        const _glfw_hpp_internal::WindowHint<int> eRedBits(GLFW_RED_BITS, 8);
        const _glfw_hpp_internal::WindowHint<int> eGreenBits(GLFW_GREEN_BITS, 8);
        const _glfw_hpp_internal::WindowHint<int> eBlueBits(GLFW_BLUE_BITS, 8);
        const _glfw_hpp_internal::WindowHint<int> eAlphaBits(GLFW_ALPHA_BITS, 8);
        const _glfw_hpp_internal::WindowHint<int> eDepthBIts(GLFW_DEPTH_BITS, 24);
        const _glfw_hpp_internal::WindowHint<int> eStencilBits(GLFW_STENCIL_BITS, 28);
        const _glfw_hpp_internal::WindowHint<int> eAccumRedBits(GLFW_ACCUM_RED_BITS, 0);
        const _glfw_hpp_internal::WindowHint<int> eAccumGreenBits(GLFW_ACCUM_GREEN_BITS, 0);
        const _glfw_hpp_internal::WindowHint<int> eAccumBlueBits(GLFW_ACCUM_BLUE_BITS, 0);
        const _glfw_hpp_internal::WindowHint<int> eAccumAlphaBits(GLFW_ACCUM_ALPHA_BITS, 0);
        const _glfw_hpp_internal::WindowHint<int> eAuxBuffers(GLFW_AUX_BUFFERS, 0);
        const _glfw_hpp_internal::WindowHint<int> eSamples(GLFW_SAMPLES, 0);

        //Monitor related

        const _glfw_hpp_internal::WindowHint<int> eRefreshRate(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
    }

    // enum class ContextHint : Hint
    // {
    //     eClientApi           = GLFW_CLIENT_API,
    //     eContextCreationApi  = GLFW_CONTEXT_CREATION_API,
    //     eContextVersionMajor = GLFW_CONTEXT_VERSION_MAJOR,
    //     eContextVersionMinor = GLFW_CONTEXT_VERSION_MINOR
    // };

    enum class StandardCursor
    {
        eArrow        = GLFW_ARROW_CURSOR,
        eIBEAM        = GLFW_IBEAM_CURSOR,
        eCrosshair    = GLFW_CROSSHAIR_CURSOR,
        ePointingHand = GLFW_POINTING_HAND_CURSOR,
        eResizeEW     = GLFW_RESIZE_EW_CURSOR,
        eResizeNS     = GLFW_RESIZE_NS_CURSOR,
        eResizeNWSE   = GLFW_RESIZE_NWSE_CURSOR,
        eResizeNESW   = GLFW_RESIZE_NESW_CURSOR,
        eResizeAll    = GLFW_RESIZE_ALL_CURSOR,
        eNotAllowed   = GLFW_NOT_ALLOWED_CURSOR,
        eHResize      = GLFW_HRESIZE_CURSOR, // = eResizeEW
        eVResize      = GLFW_VRESIZE_CURSOR, // = eResizeNS
        eHand         = GLFW_HAND_CURSOR     // = ePointingHand
    };

    class Vidmode;
    class Gammaramp;
    class Image;
    class Monitor;
    class Window;
    class Cursor;

    namespace Joystick
    {
        namespace _glfw_hpp_internal
        {
            class Joystick;
        }
    }

    using Scancode = int;
    using UnicodeCodePoint = unsigned int;

    typedef void (* ErrorFun)(Result, const char*);
    typedef void (* WindowPosFun)(Window, int, int);
    typedef void (* WindowSizeFun)(Window, int, int);
    typedef void (* WindowCloseFun)(Window);
    typedef void (* WindowRefreshFun)(Window);
    typedef void (* WindowFocusFun)(Window, bool);
    typedef void (* WindowIconifyFun)(Window, bool);
    typedef void (* WindowMaximizeFun)(Window, bool);
    typedef void (* FramebufferSizeFun)(Window, int, int);
    typedef void (* WindowContentScaleFun)(Window, float, float);
    typedef void (* MouseButtonFun)(Window, MouseButton, ButtonAction, KeyMod);
    typedef void (* CursorPosFun)(Window, double, double);
    typedef void (* CursorEnterFun)(Window, bool);
    typedef void (* ScrollFun)(Window, double, double);
    typedef void (* KeyFun)(Window, Key, Scancode, ButtonAction, KeyMod);
    typedef void (* CharFun)(Window, UnicodeCodePoint);
    typedef void (* CharModsFun)(Window, UnicodeCodePoint, KeyMod);
    typedef void (* DropFun)(Window, ::std::vector<std::string>);
    typedef void (* MonitorFun)(Monitor, DeviceAction);
    typedef void (* JoystickFun)(Joystick::_glfw_hpp_internal::Joystick, DeviceAction);

    using GlProc = GLFWglproc;
    using VkProc = GLFWvkproc;

    class Vidmode
    {
    public:
        GLFW_HPP_CONSTEXPR Vidmode(const Vidmode&) GLFW_HPP_NOEXCEPT = default;

        Vidmode(const GLFWvidmode* native)
        {
            *this = *reinterpret_cast<const Vidmode*>(native);
        }

        operator const GLFWvidmode&() const GLFW_HPP_NOEXCEPT
        {
            return *reinterpret_cast<const GLFWvidmode*>(this);
        }

        operator GLFWvidmode&() GLFW_HPP_NOEXCEPT
        {
            return *reinterpret_cast<GLFWvidmode*>(this);
        }

        #if defined(GLFW_HPP_HAS_SPACESHIP_OPERATOR)
            auto operator<=>(const Vidmode&) const = default;
        #else
            bool operator==(const Vidmode& vm) const GLFW_HPP_NOEXCEPT
            {
                return ( this->width == vm.width )
                    && ( this->height == vm.height )
                    && ( this->redBits == vm.redBits )
                    && ( this->greenBits == vm.greenBits )
                    && ( this->blueBits == vm.blueBits )
                    && ( this->refreshRate == vm.refreshRate );
            }

            bool operator!=(const Vidmode& vm) const GLFW_HPP_NOEXCEPT
            {
                return ! this->operator==(vm);
            }
        #endif

        int width;
        int height;
        int redBits;
        int greenBits;
        int blueBits;
        int refreshRate;
    };
    static_assert(sizeof(Vidmode) == sizeof(GLFWvidmode), "struct and wrapper have different size!");
    static_assert(::std::is_standard_layout<Vidmode>::value, "struct wrapper is not a standard layout!");

    class Gammaramp
    {
    public:
        GLFW_HPP_CONSTEXPR Gammaramp(const Gammaramp&) GLFW_HPP_NOEXCEPT = default;

        Gammaramp(unsigned short* red = nullptr, unsigned short* blue = nullptr, unsigned short* green = nullptr, unsigned int size = 0) GLFW_HPP_NOEXCEPT
            : red(red), blue(blue), green(green), size(size)
        {}

        Gammaramp(const GLFWgammaramp* native)
        {
            *this = *reinterpret_cast<const Gammaramp*>(native);
        }

        operator const GLFWgammaramp&() const GLFW_HPP_NOEXCEPT
        {
            return *reinterpret_cast<const GLFWgammaramp*>(this);
        }

        operator GLFWgammaramp&() GLFW_HPP_NOEXCEPT
        {
            return *reinterpret_cast<GLFWgammaramp*>(this);
        }

        #if defined(GLFW_HPP_HAS_SPACESHIP_OPERATOR)
            auto operator<=>(const Gammaramp&) const = default;
        #else
            bool operator==(const Gammaramp& gr) const GLFW_HPP_NOEXCEPT
            {
                return ( this->red == gr.red )
                    && ( this->green == gr.green )
                    && ( this->blue == gr.blue )
                    && ( this->size == gr.size );
            }

            bool operator!=(const Gammaramp& gr) const GLFW_HPP_NOEXCEPT
            {
                return ! this->operator==(gr);
            }
        #endif

        Gammaramp& setRed(unsigned short* red)
        {
            this->red = red;
            return *this;
        }

        Gammaramp& setGreen(unsigned short* green)
        {
            this->green = green;
            return *this;
        }

        Gammaramp& setBlue(unsigned short* blue)
        {
            this->blue = blue;
            return *this;
        }

        Gammaramp& setSize(unsigned int size)
        {
            this->size = size;
            return *this;
        }

        unsigned short* red = nullptr;
        unsigned short* green = nullptr;
        unsigned short* blue = nullptr;
        unsigned int size = 0;
    };
    static_assert(sizeof(Gammaramp) == sizeof(GLFWgammaramp), "struct and wrapper have different size!");
    static_assert(::std::is_standard_layout<Gammaramp>::value, "struct wrapper is not a standard layout!");

    class Image
    {
    public:
        Image(GLFWimage* native)
        {
            *this = *reinterpret_cast<Image*>(native);
        }

        int width;
        int height;
        unsigned char* pixels;
    };
    static_assert(sizeof(Image) == sizeof(GLFWimage), "struct and wrapper have different size!");
    static_assert(::std::is_standard_layout<Image>::value, "struct wrapper is not a standard layout!");

    class Monitor
    {
    private:
        GLFWmonitor* handle;
    public:
        Monitor(GLFWmonitor* handle) :
            handle(handle) {}

        operator GLFWmonitor*()
        {
            return this->handle;
        }

        bool operator==(const Monitor& other)
        {
            return this->handle == other.handle;
        }

        void getPos(int* xpos, int* ypos) const
        {
            glfwGetMonitorPos(this->handle, xpos, ypos);
            check_last_error();
        }

        void getWorkarea(int* xpos, int* ypos, int* width, int* height)
        {
            glfwGetMonitorWorkarea(this->handle, xpos, ypos, width, height);
            check_last_error();
        }

        void getPhysicalSize(int* widthMM, int* heightMM)
        {
            glfwGetMonitorPhysicalSize(this->handle, widthMM, heightMM);
            check_last_error();
        }

        void getContentScale(float* xscale, float* yscale)
        {
            glfwGetMonitorContentScale(this->handle, xscale, yscale);
            check_last_error();
        }

        const char* getName()
        {
            const char* name = glfwGetMonitorName(this->handle);
            check_last_error();
            return name;
        }

        void setUserPointer(void* ptr)
        {
            glfwSetMonitorUserPointer(this->handle, ptr);
            check_last_error();
        }

        void* getUserPointer()
        {
            void* userPointer = glfwGetMonitorUserPointer(this->handle);
            check_last_error();
            return userPointer;
        }

        const ::std::vector<Vidmode> getVideoModes()
        {
            int count;
            const GLFWvidmode* natives = glfwGetVideoModes(this->handle, &count);
            check_last_error();
            std::vector<Vidmode> vidmodes;
            for(int i = 0; i < count; i++)
                vidmodes.push_back(Vidmode(natives + i));
            return vidmodes;
        }

        const Vidmode getVideoMode()
        {
            const GLFWvidmode* native = glfwGetVideoMode(this->handle);
            check_last_error();
            return Vidmode(native);
        }

        void setGamma(float gamma)
        {
            glfwSetGamma(this->handle, gamma);
            check_last_error();
        }

        const Gammaramp getGammaRamp()
        {
            const GLFWgammaramp* native = glfwGetGammaRamp(this->handle);
            check_last_error();
            return Gammaramp(native);
        }

        void setGammaRamp(GLFWgammaramp* gr)
        {
            glfwSetGammaRamp(this->handle, gr);
            check_last_error();
        }

        void setGammaRamp(const Gammaramp& gr)
        {
            glfwSetGammaRamp(this->handle, reinterpret_cast<const GLFWgammaramp*>(&gr));
            check_last_error();
        }

    };

    class Cursor
    {
    private:
        GLFWcursor* handle;
    public:
        Cursor(GLFWcursor* handle) noexcept
            : handle(handle)
        {}

        operator GLFWcursor*() const noexcept
        {
            return this->handle;
        }

        void destroy()
        {
            glfwDestroyCursor(this->handle);
            check_last_error();
        }

    };
    static_assert(sizeof(Cursor) == sizeof(GLFWcursor*), "struct and wrapper have different size!");
    static_assert(::std::is_standard_layout<Cursor>::value, "struct wrapper is not a standard layout!");

    class Window
    {
    private:
        GLFWwindow* handle;
    public:
        Window(GLFWwindow* handle)
            : handle(handle)
        {}

        operator GLFWwindow*() const GLFW_HPP_NOEXCEPT
        {
            return this->handle;
        }

        void destroy()
        {
            glfwDestroyWindow(this->handle);
            check_last_error();
        }

        bool shouldClose()
        {
            int flag = glfwWindowShouldClose(this->handle);
            check_last_error();
            return static_cast<bool>(flag);
        }

        void setShouldClose(bool shouldClose)
        {
            glfwSetWindowShouldClose(this->handle, shouldClose);
            check_last_error();
        }

        void setWindowTitle(const char* title)
        {
            glfwSetWindowTitle(this->handle, title);
            check_last_error();
        }

        void setIcon(int count, const Image* images)
        {
            glfwSetWindowIcon(this->handle, count, reinterpret_cast<const GLFWimage*>(images));
            check_last_error();
        }

        void setIcon(::std::initializer_list<Image> images)
        {
            glfwSetWindowIcon(this->handle, images.size(), reinterpret_cast<const GLFWimage*>(images.begin()));
            check_last_error();
        }

        void setIcon(const Image image)
        {
            glfwSetWindowIcon(this->handle, 1, reinterpret_cast<const GLFWimage*>(&image));
            check_last_error();
        }

        void getPos(int* xpos, int* ypos)
        {
            glfwGetWindowPos(this->handle, xpos, ypos);
            check_last_error();
        }

        void setPos(int xpos, int ypos)
        {
            glfwSetWindowPos(this->handle, xpos, ypos);
            check_last_error();
        }

        void getSize(int* width, int* height)
        {
            glfwGetWindowSize(this->handle, width, height);
            check_last_error();
        }

        void setSize(int width, int height)
        {
            glfwSetWindowSize(this->handle, width, height);
            check_last_error();
        }

        void setSizeLimits(int minwidth, int minheight, int maxwidth, int maxheight)
        {
            glfwSetWindowSizeLimits(this->handle, minwidth, minheight, maxwidth, maxheight);
            check_last_error();
        }

        void setAspectRatio(int numer, int denom)
        {
            glfwSetWindowAspectRatio(this->handle, numer, denom);
            check_last_error();
        }

        void getFramebufferSize(int* width, int* height)
        {
            glfwGetFramebufferSize(this->handle, width, height);
            check_last_error();
        }

        void getFrameSize(int* left, int* top, int* right, int* bottom)
        {
            glfwGetWindowFrameSize(this->handle, left, top, right, bottom);
            check_last_error();
        }

        void getContentScale(float* xscale, float* yscale)
        {
            glfwGetWindowContentScale(this->handle, xscale, yscale);
            check_last_error();
        }

        float getOpacity()
        {
            float opa = glfwGetWindowOpacity(this->handle);
            check_last_error();
            return opa;
        }

        void getOpacity(float* opa)
        {
            *opa = glfwGetWindowOpacity(this->handle);
            check_last_error();
        }

        void setOpacity(float opacity)
        {
            glfwSetWindowOpacity(this->handle ,opacity);
            check_last_error();
        }

        void iconify()
        {
            glfwIconifyWindow(this->handle);
            check_last_error();
        }

        void restore()
        {
            glfwRestoreWindow(this->handle);
            check_last_error();
        }

        void maximize()
        {
            glfwMaximizeWindow(this->handle);
            check_last_error();
        }

        void show()
        {
            glfwShowWindow(this->handle);
            check_last_error();
        }

        void hide()
        {
            glfwHideWindow(this->handle);
            check_last_error();
        }

        void focus()
        {
            glfwFocusWindow(this->handle);
            check_last_error();
        }

        void requestAttention()
        {
            glfwRequestWindowAttention(this->handle);
            check_last_error();
        }

        Monitor getMonitor()
        {
            GLFWmonitor* native = glfwGetWindowMonitor(this->handle);
            check_last_error();
            return Monitor(native);
        }

        void setMonitor(GLFWmonitor* monitor, int xpos, int ypos, int width, int height, int refreshRate)
        {
            glfwSetWindowMonitor(this->handle, monitor, xpos, ypos, width, height, refreshRate);
            check_last_error();
        }

        void setUserPointer(void* ptr)
        {
            glfwSetWindowUserPointer(this->handle, ptr);
            check_last_error();
        }

        void* getUserPointer()
        {
            void* ptr = glfwGetWindowUserPointer(this->handle);
            check_last_error();
            return ptr;
        }

        GLFWwindowposfun setPosCallback(GLFWwindowposfun callback)
        {
            GLFWwindowposfun old = glfwSetWindowPosCallback(this->handle, callback);
            check_last_error();
            return old;
        }

        WindowPosFun setPosCallback(WindowPosFun callback)
        {
            GLFWwindowposfun old = glfwSetWindowPosCallback(this->handle, reinterpret_cast<GLFWwindowposfun>(callback));
            check_last_error();
            return reinterpret_cast<WindowPosFun>(old);
        }

        GLFWwindowsizefun setSizeCallback(GLFWwindowsizefun callback)
        {
            GLFWwindowsizefun old = glfwSetWindowSizeCallback(this->handle, callback);
            check_last_error();
            return old;
        }

        WindowSizeFun setSizeCallback(WindowSizeFun callback)
        {
            GLFWwindowsizefun old = glfwSetWindowSizeCallback(this->handle, reinterpret_cast<GLFWwindowsizefun>(callback));
            check_last_error();
            return reinterpret_cast<WindowSizeFun>(old);
        }

        GLFWwindowclosefun setCloseCallback(GLFWwindowclosefun callback)
        {
            GLFWwindowclosefun old = glfwSetWindowCloseCallback(this->handle, callback);
            check_last_error();
            return old;
        }

        WindowCloseFun setCloseCallback(WindowCloseFun callback)
        {
            GLFWwindowclosefun old = glfwSetWindowCloseCallback(this->handle, reinterpret_cast<GLFWwindowclosefun>(callback));
            check_last_error();
            return reinterpret_cast<WindowCloseFun>(callback);
        }

        GLFWwindowrefreshfun setRefreshCallback(GLFWwindowrefreshfun callback)
        {
            GLFWwindowrefreshfun old = glfwSetWindowRefreshCallback(this->handle, callback);
            check_last_error();
            return old;
        }

        WindowRefreshFun setRefreshCallback(WindowRefreshFun callback)
        {
            GLFWwindowrefreshfun old = glfwSetWindowRefreshCallback(this->handle, reinterpret_cast<GLFWwindowrefreshfun>(callback));
            check_last_error();
            return reinterpret_cast<WindowRefreshFun>(old);
        }

        GLFWwindowfocusfun setFocusCallback(GLFWwindowfocusfun callback)
        {
            GLFWwindowfocusfun old = glfwSetWindowFocusCallback(this->handle, callback);
            check_last_error();
            return old;
        }

        WindowFocusFun setFocusCallback(WindowFocusFun callback)
        {
            GLFWwindowfocusfun old = glfwSetWindowFocusCallback(this->handle, reinterpret_cast<GLFWwindowfocusfun>(callback));
            check_last_error();
            return reinterpret_cast<WindowFocusFun>(old);
        }

        GLFWwindowiconifyfun setIconifyCallback(GLFWwindowiconifyfun callback)
        {
            GLFWwindowiconifyfun old = glfwSetWindowIconifyCallback(this->handle, callback);
            check_last_error();
            return old;
        }

        WindowIconifyFun setIconifyCallback(WindowIconifyFun callback)
        {
            GLFWwindowiconifyfun old = glfwSetWindowIconifyCallback(this->handle, reinterpret_cast<GLFWwindowiconifyfun>(callback));
            check_last_error();
            return reinterpret_cast<WindowIconifyFun>(old);
        }

        GLFWwindowmaximizefun setMaximizeCallback(GLFWwindowmaximizefun callback)
        {
            GLFWwindowmaximizefun old = glfwSetWindowMaximizeCallback(this->handle, callback);
            check_last_error();
            return old;
        }

        WindowMaximizeFun setMaximizeCallback(WindowMaximizeFun callback)
        {
            GLFWwindowmaximizefun old = glfwSetWindowMaximizeCallback(this->handle, reinterpret_cast<GLFWwindowmaximizefun>(callback));
            check_last_error();
            return reinterpret_cast<WindowMaximizeFun>(old);
        }

        GLFWframebuffersizefun setFramebufferSizeCallback(GLFWframebuffersizefun callback)
        {
            GLFWframebuffersizefun old = glfwSetFramebufferSizeCallback(this->handle, callback);
            check_last_error();
            return old;
        }

        FramebufferSizeFun setFramebufferSizeCallback(FramebufferSizeFun callback)
        {
            GLFWframebuffersizefun old = glfwSetFramebufferSizeCallback(this->handle, reinterpret_cast<GLFWframebuffersizefun>(callback));
            check_last_error();
            return reinterpret_cast<FramebufferSizeFun>(old);
        }

        GLFWwindowcontentscalefun setContentScaleCallback(GLFWwindowcontentscalefun callback)
        {
            GLFWwindowcontentscalefun old = glfwSetWindowContentScaleCallback(this->handle, callback);
            check_last_error();
            return old;
        }

        WindowContentScaleFun setContentScaleCallback(WindowContentScaleFun callback)
        {
            GLFWwindowcontentscalefun old = glfwSetWindowContentScaleCallback(this->handle, reinterpret_cast<GLFWwindowcontentscalefun>(callback));
            check_last_error();
            return reinterpret_cast<WindowContentScaleFun>(old);
        }

        template<typename ValueType>
        ValueType getInputMode(InputMode::_glfw_hpp_internal::InputMode<ValueType> mode)
        {
            int value = glfwGetInputMode(this->handle, mode);
            check_last_error();
            return InputMode::_glfw_hpp_internal::fromNativeValue<ValueType>(value);
        }

        template<typename ValueType>
        void setInputMode(InputMode::_glfw_hpp_internal::InputMode<ValueType> mode, ValueType value)
        {
            glfwSetInputMode(this->handle, mode, InputMode::_glfw_hpp_internal::toNativeValue<ValueType>(value));
            check_last_error();
        }

        bool getKey(Key key)
        {
            int value = glfwGetKey(this->handle, static_cast<int>(key));
            check_last_error();
            return value != GLFW_FALSE;
        }

        ButtonAction getMouseButton(MouseButton button)
        {
            int value = glfwGetMouseButton(this->handle, static_cast<int>(button));
            check_last_error();
            return static_cast<ButtonAction>(value);
        }

        void getCursorPos(double* xpos, double* ypos)
        {
            glfwGetCursorPos(this->handle, xpos, ypos);
            check_last_error();
        }

        void setCursorPos(double xpos, double ypos)
        {
            glfwSetCursorPos(this->handle, xpos, ypos);
            check_last_error();
        }

        void setCursor(GLFWcursor* cursor)
        {
            glfwSetCursor(this->handle, cursor);
            check_last_error();
        }

        void setCursor(Cursor cursor)
        {
            glfwSetCursor(this->handle, cursor);
            check_last_error();
        }

        GLFWkeyfun setKeyCallback(GLFWkeyfun callback)
        {
            GLFWkeyfun old = glfwSetKeyCallback(this->handle, callback);
            check_last_error();
            return old;
        }

        KeyFun setKeyCallback(KeyFun callback)
        {
            GLFWkeyfun old = glfwSetKeyCallback(this->handle, reinterpret_cast<GLFWkeyfun>(callback));
            check_last_error();
            return reinterpret_cast<KeyFun>(old);
        }

        GLFWcharfun setCharCallback(GLFWcharfun callback)
        {
            GLFWcharfun old = glfwSetCharCallback(this->handle, callback);
            check_last_error();
            return old;
        }

        CharFun setCharCallback(CharFun callback)
        {
            GLFWcharfun old = glfwSetCharCallback(this->handle, reinterpret_cast<GLFWcharfun>(callback));
            check_last_error();
            return reinterpret_cast<CharFun>(old);
        }

        GLFWcharmodsfun setCharModCallback(GLFWcharmodsfun callback)
        {
            GLFWcharmodsfun old = glfwSetCharModsCallback(this->handle, callback);
            check_last_error();
            return old;
        }

        CharModsFun setCharModCallback(CharModsFun callback)
        {
            GLFWcharmodsfun old = glfwSetCharModsCallback(this->handle, reinterpret_cast<GLFWcharmodsfun>(callback));
            check_last_error();
            return reinterpret_cast<CharModsFun>(old);
        }

        GLFWmousebuttonfun setMouseButtonCallback(GLFWmousebuttonfun callback)
        {
            GLFWmousebuttonfun old = glfwSetMouseButtonCallback(this->handle, callback);
            check_last_error();
            return old;
        }

        MouseButtonFun setMouseButtonCallback(MouseButtonFun callback)
        {
            GLFWmousebuttonfun old = glfwSetMouseButtonCallback(this->handle, reinterpret_cast<GLFWmousebuttonfun>(callback));
            check_last_error();
            return reinterpret_cast<MouseButtonFun>(old);
        }

        GLFWcursorposfun setCursorPosCallback(GLFWcursorposfun callback)
        {
            GLFWcursorposfun old = glfwSetCursorPosCallback(this->handle, callback);
            check_last_error();
            return old;
        }

        CursorPosFun setCursorPosCallback(CursorPosFun callback)
        {
            GLFWcursorposfun old = glfwSetCursorPosCallback(this->handle, reinterpret_cast<GLFWcursorposfun>(callback));
            check_last_error();
            return reinterpret_cast<CursorPosFun>(old);
        }

        GLFWcursorenterfun setCursorEnterCallback(GLFWcursorenterfun callback)
        {
            GLFWcursorenterfun old = glfwSetCursorEnterCallback(this->handle, callback);
            check_last_error();
            return old;
        }

        CursorEnterFun setCursorEnterCallback(CursorEnterFun callback)
        {
            GLFWcursorenterfun old = glfwSetCursorEnterCallback(this->handle, reinterpret_cast<GLFWcursorenterfun>(callback));
            check_last_error();
            return reinterpret_cast<CursorEnterFun>(old);
        }

        GLFWscrollfun setScrollCallback(GLFWscrollfun callback)
        {
            GLFWscrollfun old = glfwSetScrollCallback(this->handle, callback);
            check_last_error();
            return old;
        }

        ScrollFun setScrollCallback(ScrollFun callback)
        {
            GLFWscrollfun old = glfwSetScrollCallback(this->handle, reinterpret_cast<GLFWscrollfun>(callback));
            check_last_error();
            return reinterpret_cast<ScrollFun>(old);
        }

        GLFWdropfun setDropCallback(GLFWdropfun callback)
        {
            GLFWdropfun old = glfwSetDropCallback(this->handle, callback);
            check_last_error();
            return old;
        }

        DropFun setDropCallback(DropFun callback)
        {
            GLFWdropfun old = glfwSetDropCallback(this->handle, reinterpret_cast<GLFWdropfun>(callback));
            check_last_error();
            return reinterpret_cast<DropFun>(old);
        }

        void setClipboardString(const char* clipboard)
        {
            glfwSetClipboardString(this->handle, clipboard);
            check_last_error();
        }

        ::std::string getClipboardString()
        {
            const char* clipboard = glfwGetClipboardString(this->handle);
            check_last_error();
            return ::std::string(clipboard);
        }

        void makeContextCurrent()
        {
            glfwMakeContextCurrent(this->handle);
            check_last_error();
        }

        void swapBuffers()
        {
            glfwSwapBuffers(this->handle);
            check_last_error();
        }

        #ifdef VK_VERSION_1_0
            VkResult createSurface(VkInstance instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface)
            {
                VkResult result = glfwCreateWindowSurface(instance, this->handle, allocator, surface);
                check_last_error();
                return result;
            }

            #ifdef VULKAN_HPP

                vk::SurfaceKHR createSurface(vk::Instance instace, vk::Optional<vk::AllocationCallbacks> allocator VULKAN_HPP_DEFAULT_ARGUMENT_NULLPTR_ASSIGNMENT)
                {
                    VkSurfaceKHR surface;
                    createSurface(instace, reinterpret_cast<VkAllocationCallbacks*>(&(vk::AllocationCallbacks&) allocator), &surface);
                    return vk::SurfaceKHR(surface);
                }

            #endif

        #endif

    };
    static_assert(sizeof(Window) == sizeof(GLFWwindow*), "struct and wrapper have different size!");
    static_assert(::std::is_standard_layout<Window>::value, "struct wrapper is not a standard layout!");

    class GamepadState
    {
    public:
        unsigned char buttons[15];
        float axes[6];
    };
    static_assert(sizeof(GamepadState) == sizeof(GLFWgamepadstate), "struct and wrapper have different size!");
    static_assert(::std::is_standard_layout<GamepadState>::value, "struct wrapper is not a standard layout!");

    namespace Joystick
    {
        namespace _glfw_hpp_internal
        {
            class Joystick
            {
            private:
                int handle;
            public:
                Joystick(int handle)
                    : handle(handle)
                {}

                operator int() const noexcept
                {
                    return this->handle;
                }

                bool present() const
                {
                    int value = glfwJoystickPresent(this->handle);
                    check_last_error();
                    return value != GLFW_FALSE;
                }

                const float* getAxes(int* count) const
                {
                    const float* values = glfwGetJoystickAxes(this->handle, count);
                    check_last_error();
                    return values;
                }

                const ::std::vector<float> getAxes() const
                {
                    int count;
                    const float* axes = glfwGetJoystickAxes(this->handle, &count);
                    check_last_error();
                    return ::std::vector<float>(&axes[0], &axes[count -1]);
                }

                const unsigned char* getButtons(int* count) const
                {
                    const unsigned char* values = glfwGetJoystickButtons(this->handle, count);
                    check_last_error();
                    return values;
                }

                const ::std::vector<ButtonAction> getButtons() const
                {
                    int count;
                    const unsigned char* values = glfwGetJoystickButtons(this->handle, &count);
                    check_last_error();
                    ::std::vector<ButtonAction> buttons;
                    for(int i = 0; i < count; i++)
                        buttons.push_back(
                            static_cast<ButtonAction>(values[i])
                        );
                    return buttons;
                }

                const unsigned char* getHats(int* count) const
                {
                    const unsigned char* values = glfwGetJoystickHats(this->handle, count);
                    check_last_error();
                    return values;
                }

                const ::std::vector<Hat> getHats() const
                {
                    int count;
                    const unsigned char* values = glfwGetJoystickHats(this->handle, &count);
                    check_last_error();
                    ::std::vector<Hat> hats;
                    for(int i = 0; i < count; i++)
                        hats.push_back(
                            static_cast<Hat>(values[i])
                        );
                    return hats;
                }

                ::std::string getName() const
                {
                    const char* name = glfwGetJoystickName(this->handle);
                    check_last_error();
                    return ::std::string(name);
                }

                ::std::string getGUID() const
                {
                    const char* guid = glfwGetJoystickGUID(this->handle);
                    check_last_error();
                    return ::std::string(guid);
                }

                void setUserPointer(void* pointer) const
                {
                    glfwSetJoystickUserPointer(this->handle, pointer);
                    check_last_error();
                }

                void* getUserPointer() const
                {
                    void* pointer = glfwGetJoystickUserPointer(this->handle);
                    check_last_error();
                    return pointer;
                }

                bool isGamepad() const
                {
                    int value = glfwJoystickIsGamepad(this->handle);
                    check_last_error();
                    return value != GLFW_FALSE;
                }

                ::std::string getGamepadName()
                {
                    const char* name = glfwGetGamepadName(this->handle);
                    check_last_error();
                    return ::std::string(name);
                }

                int getGamepadState(GLFWgamepadstate* state)
                {
                    int value = glfwGetGamepadState(this->handle, state);
                    check_last_error();
                    return value;
                }

                bool getGamepadState(GamepadState& state)
                {
                    int value = glfwGetGamepadState(this->handle, reinterpret_cast<GLFWgamepadstate*>(&state));
                    check_last_error();
                    return value != GLFW_FALSE;
                }
            };
            static_assert(sizeof(Joystick) == sizeof(int), "struct and wrapper have different size!");
            static_assert(::std::is_standard_layout<Joystick>::value, "struct wrapper is not a standard layout!");
        }

        const _glfw_hpp_internal::Joystick e1(GLFW_JOYSTICK_1);
        const _glfw_hpp_internal::Joystick e2(GLFW_JOYSTICK_2);
        const _glfw_hpp_internal::Joystick e3(GLFW_JOYSTICK_3);
        const _glfw_hpp_internal::Joystick e4(GLFW_JOYSTICK_4);
        const _glfw_hpp_internal::Joystick e5(GLFW_JOYSTICK_5);
        const _glfw_hpp_internal::Joystick e6(GLFW_JOYSTICK_6);
        const _glfw_hpp_internal::Joystick e7(GLFW_JOYSTICK_7);
        const _glfw_hpp_internal::Joystick e8(GLFW_JOYSTICK_8);
        const _glfw_hpp_internal::Joystick e9(GLFW_JOYSTICK_9);
        const _glfw_hpp_internal::Joystick e10(GLFW_JOYSTICK_10);
        const _glfw_hpp_internal::Joystick e11(GLFW_JOYSTICK_11);
        const _glfw_hpp_internal::Joystick e12(GLFW_JOYSTICK_12);
        const _glfw_hpp_internal::Joystick e13(GLFW_JOYSTICK_13);
        const _glfw_hpp_internal::Joystick e14(GLFW_JOYSTICK_14);
        const _glfw_hpp_internal::Joystick e15(GLFW_JOYSTICK_15);
        const _glfw_hpp_internal::Joystick e16(GLFW_JOYSTICK_16);

        const std::array<const _glfw_hpp_internal::Joystick, GLFW_JOYSTICK_LAST + 1> list({
            e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16
        });
    }

    bool init()
    {
        bool success = glfwInit() != GLFW_FALSE;
        check_last_error();
        return success;
    }

    void terminate()
    {
        glfwTerminate();
        check_last_error();
    }

    void initHint(Hint::_glfw_hpp_internal::InitHint hint, bool value)
    {
        glfwInitHint(hint, value);
        check_last_error();
    }

    void getVersion(int* major, int* minor, int* rev) noexcept
    {
        glfwGetVersion(major, minor, rev);
    }

    std::string getVersionString() noexcept
    {
        return glfwGetVersionString();
    }

    GLFWerrorfun setErrorCallback(GLFWerrorfun callback) noexcept
    {
        return glfwSetErrorCallback(callback);
    }

    namespace _glfw_hpp_internal
    {
        ErrorFun error_callback;

        void error_callback_impl(int error, const char* message)
        {
            error_callback(make_result(error), message);
        }
    }

    GLFWerrorfun setErrorCallback(ErrorFun callback) noexcept
    {
        _glfw_hpp_internal::error_callback = callback;
        return glfwSetErrorCallback(
            callback == nullptr ? NULL : _glfw_hpp_internal::error_callback_impl
        );
    }

    const ::std::vector<Monitor> getMonitors()
    {
        int count;
        GLFWmonitor** handels = glfwGetMonitors(&count);
        check_last_error();

        ::std::vector<Monitor> monitors;
        monitors.reserve(count);
        for(int i = 0; i < count; i++)
            monitors.push_back(Monitor(handels[i]));

        monitors.shrink_to_fit();

        return monitors;
    }

    Monitor getPrimaryMonitor()
    {
        Monitor primary(glfwGetPrimaryMonitor());
        check_last_error();
        return primary;
    }

    GLFWmonitorfun setMonitorCallback(GLFWmonitorfun callback)
    {
        GLFWmonitorfun old = glfwSetMonitorCallback(callback);
        check_last_error();
        return old;
    }

    namespace _glfw_hpp_internal
    {
        MonitorFun monitor_callback;

        void monitor_callback_impl(GLFWmonitor* handle, int action)
        {
            monitor_callback(Monitor(handle), static_cast<DeviceAction>(action));
        }
    }

    GLFWmonitorfun setMonitorCallback(MonitorFun callback)
    {
        _glfw_hpp_internal::monitor_callback = callback;
        return glfwSetMonitorCallback(
            callback == nullptr ? NULL : _glfw_hpp_internal::monitor_callback_impl
        );
    }

    void defaultWindowHints()
    {
        glfwDefaultWindowHints();
        check_last_error();
    }

    template<typename T>
    void windowHint(Hint::_glfw_hpp_internal::WindowHint<T> hint, T value)
    {
        glfwWindowHint(hint, Hint::_glfw_hpp_internal::nativeValue(value));
        check_last_error();
    }

    template<>
    void windowHint(Hint::_glfw_hpp_internal::WindowHint<const char*> hint, const char* value)
    {
        glfwWindowHintString(hint, value);
        check_last_error();
    }

    const auto windowHintString = windowHint<const char*>;

    Window createWindow(int width, int height, const char* title, _glfw_hpp_internal::Optional<Monitor> monitor = nullptr, _glfw_hpp_internal::Optional<Window> share = nullptr)
    {
        GLFWwindow* native = glfwCreateWindow(width, height, title, monitor ? monitor.ref() : NULL, share ? share.ref() : NULL);
        check_last_error();
        return Window(native);
    }

    void pollEvents()
    {
        glfwPollEvents();
        check_last_error();
    }

    void waitEvents()
    {
        glfwWaitEvents();
        check_last_error();
    }

    void waitEventsTimeout(double timeout)
    {
        glfwWaitEventsTimeout(timeout);
        check_last_error();
    }

    void postEmptyEvent()
    {
        glfwPostEmptyEvent();
        check_last_error();
    }

    bool rawMouseMotionSupported()
    {
        int value = glfwRawMouseMotionSupported();
        check_last_error();
        return value != GLFW_FALSE;
    }

    const char* getKeyName(Key key, Scancode scancode)
    {
        const char* name = glfwGetKeyName(static_cast<int>(key), scancode);
        check_last_error();
        return name;
    }

    Scancode getKeyScancode(Key key)
    {
        int scancode = glfwGetKeyScancode(static_cast<int>(key));
        check_last_error();
        return scancode;
    }

    Cursor createCursor(const GLFWimage* image, int xhot, int yhot)
    {
        GLFWcursor* native = glfwCreateCursor(image, xhot, yhot);
        check_last_error();
        return Cursor(native);
    }

    Cursor createCursor(const Image& image, int xhot, int yhot)
    {
        GLFWcursor* native = glfwCreateCursor(reinterpret_cast<const GLFWimage*>(&image), xhot, yhot);
        check_last_error();
        return Cursor(native);
    }

    Cursor createStandardCursor(int standardCursorShape)
    {
        GLFWcursor* native = glfwCreateStandardCursor(standardCursorShape);
        check_last_error();
        return Cursor(native);
    }

    Cursor createStandardCursor(StandardCursor cursor)
    {
        GLFWcursor* native = glfwCreateStandardCursor(static_cast<int>(cursor));
        check_last_error();
        return Cursor(native);
    }

    GLFWjoystickfun setJoystickCallback(GLFWjoystickfun callback)
    {
        GLFWjoystickfun old = glfwSetJoystickCallback(callback);
        check_last_error();
        return old;
    }

    JoystickFun setJoystickCallback(JoystickFun callback)
    {
        GLFWjoystickfun old = glfwSetJoystickCallback(reinterpret_cast<GLFWjoystickfun>(callback));
        check_last_error();
        return reinterpret_cast<JoystickFun>(old);
    }

    bool updateGamepadMappings(const char* gamepad)
    {
        int value = glfwUpdateGamepadMappings(gamepad);
        check_last_error();
        return value != GLFW_FALSE;
    }

    double getTime()
    {
        double value = glfwGetTime();
        check_last_error();
        return value;
    }

    void setTime(double time)
    {
        glfwSetTime(time);
        check_last_error();
    }

    uint64_t getTimerValue()
    {
        uint64_t value = glfwGetTimerValue();
        check_last_error();
        return value;
    }

    uint64_t getTimerFrequency()
    {
        uint64_t frequency = glfwGetTimerFrequency();
        check_last_error();
        return frequency;
    }

    Window getCurrentContext()
    {
        GLFWwindow* native = glfwGetCurrentContext();
        check_last_error();
        return Window(native);
    }

    void swapInterval(int interval)
    {
        glfwSwapInterval(interval);
        check_last_error();
    }

    bool extensionSupported(const char* glExtension)
    {
        int value = glfwExtensionSupported(glExtension);
        check_last_error();
        return value != GLFW_FALSE;
    }

    GlProc getProcAddress(const char* procname)
    {
        GlProc proc = glfwGetProcAddress(procname);
        check_last_error();
        return proc;
    }

    bool vulkanSupported()
    {
        int value = glfwVulkanSupported();
        check_last_error();
        return value != GLFW_FALSE;
    }

    const char** getRequiredInstanceExtensions(uint32_t* count)
    {
        const char** extensions = glfwGetRequiredInstanceExtensions(count);
        check_last_error();
        return extensions;
    }

    const ::std::vector<const char*> getRequiredInstanceExtensions()
    {
        uint32_t count;
        const char** extensions = getRequiredInstanceExtensions(&count);
        if(count)
            return std::vector<const char*>(&extensions[0], &extensions[count -1]);
        else
            return std::vector<const char*>();
    }

    #ifdef VK_VERSION_1_0

        VkProc getInstanceProcAddress(VkInstance instance, const char* procname)
        {
            VkProc proc = glfwGetInstanceProcAddress(instance, procname);
            check_last_error();
            return proc;
        }

        VkProc getInstanceProcAddress(const char* procname)
        {
            return getInstanceProcAddress(NULL, procname);
        }

        bool getPhysicalDevicePresentationSupport(VkInstance instance, VkPhysicalDevice device, uint32_t queuefamily)
        {
            int value = glfwGetPhysicalDevicePresentationSupport(instance, device, queuefamily);
            check_last_error();
            return value != GLFW_FALSE;
        }

    #endif
}

#endif
