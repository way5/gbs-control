#ifndef _OPTIONS_H_
#define _OPTIONS_H_

#if defined(ESP8266)
    #include <ESP8266WiFi.h>
#else
    #include <Arduino.h>
#endif

// options
// #define FRAMESYNC_DEBUG
// #define FRAMESYNC_DEBUG_LED                  // just blink LED (off = adjust phase, on = normal phase)
// #define HAVE_BUTTONS
#ifdef HAVE_BUTTONS
#define INPUT_SHIFT 0
#define DOWN_SHIFT 1
#define UP_SHIFT 2
#define MENU_SHIFT 3
#define BACK_SHIFT 4
#endif                      // HAVE_BUTTONS
#if !defined(DISPLAY_SDA)
// SDA = D2 (Lolin), D14 (Wemos D1) // ESP8266 Arduino default map: SDA
#define DISPLAY_SDA                     D2
#endif                      // DISPLAY_SDA
#if !defined(DISPLAY_SCL)
// SCL = D1 (Lolin), D15 (Wemos D1) // ESP8266 Arduino default map: SCL
#define DISPLAY_SCL                     D1
#endif                      // DISPLAY_SCL
#if !defined(DEBUG_IN_PIN)
// marked "D12/MISO/D6" (Wemos D1) or D6 (Lolin NodeMCU)
#define DEBUG_IN_PIN                    D6   // 12
#endif                      // DEBUG_IN_PIN
#define USE_NEW_OLED_MENU               1
#define PIN_CLK                         14   // D5 = GPIO14 (input of one direction for encoder)
#define PIN_DATA                        13   // D7 = GPIO13	(input of one direction for encoder)
#define PIN_SWITCH                      0    // D3 = GPIO0 pulled HIGH, else boot fail (middle push button for encoder)
#define MENU_WIDTH                      131
#define MENU_HEIGHT                     19
#define SLOTS_TOTAL                     72   // max number of slots
#define OSD_TIMEOUT                     8000
#define AUTO_GAIN_INIT                  0x48
#define THIS_DEVICE_MASTER
// #define HAVE_PINGER_LIBRARY
#define OLED_MENU_WIDTH                                 128
#define OLED_MENU_HEIGHT                                64
#define OLED_MENU_MAX_SUBITEMS_NUM                      16 // should be less than 256
#define OLED_MENU_MAX_ITEMS_NUM                         64    // should be less than 1024
#define OLED_MENU_MAX_DEPTH                             8 // maximum levels of submenus
#define OLED_MENU_REFRESH_INTERVAL_IN_MS                50 // not precise
#define OLED_MENU_SCREEN_SAVER_REFRESH_INTERVAL_IN_MS   5000 // not precise
#define OLED_MENU_SCROLL_LEAD_IN_TIME_IN_MS             600 // milliseconds before items start to scroll after being selected
#define OLED_MENU_SCREEN_SAVER_KICK_IN_SECONDS          180 // after "OLED_MENU_SCREEN_SAVE_KICK_IN_SECONDS" seconds, screen saver will show up until any key is pressed
#define OLED_MENU_OVER_DRAW                             0 // if set to 0, the last menu item of a page will not be drawn at all if partially outside the screen, and you need to scroll down to see them
#define OLED_MENU_RESET_ALWAYS_SCROLL_ON_SELECTION      0 // if set 1, scrolling items will reset to original position on selection
#define OLED_MENU_WRAPPING_SPACE                        (OLED_MENU_WIDTH / 3)
#define REVERSE_ROTARY_ENCODER_FOR_OLED_MENU            0 // if set 1, rotary encoder will be reversed for menu navigation
#define REVERSE_ROTARY_ENCODER_FOR_OSD                  0 // if set 1, rotary encoder will be reversed for OSD navigation
#define OSD_TIMEOUT                                     8000 // OSD will disappear after OSD_TIMEOUT milliseconds without inputs

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define _STRING(x)                      #x
#define STRING(x)                       _STRING(x)

// do not edit these
#define OLED_MENU_STATUS_BAR_HEIGHT                     (OLED_MENU_HEIGHT / 4) // status bar uses 1/4 of the screen
#define OLED_MENU_USABLE_AREA_HEIGHT                    (OLED_MENU_HEIGHT - OLED_MENU_STATUS_BAR_HEIGHT)
#define OLED_MENU_SCROLL_LEAD_IN_FRAMES                 (OLED_MENU_SCROLL_LEAD_IN_TIME_IN_MS / OLED_MENU_REFRESH_INTERVAL_IN_MS)

#define LEDON                     \
    pinMode(LED_BUILTIN, OUTPUT); \
    digitalWrite(LED_BUILTIN, LOW)
#define LEDOFF                       \
    digitalWrite(LED_BUILTIN, HIGH); \
    pinMode(LED_BUILTIN, INPUT)
// fast ESP8266 digitalRead (21 cycles vs 77), *should* work with all possible input pins
// but only "D7" and "D6" have been tested so far
#define digitalRead(x) ((GPIO_REG_READ(GPIO_IN_ADDRESS) >> x) & 1)

// using Ascii8 = uint8_t;
/// Output resolution requested by user, *given to* applyPresets().
enum PresetPreference : uint8_t {
    Output960P = 0,
    Output480P = 1,
    OutputCustomized = 2,
    Output720P = 3,
    Output1024P = 4,
    Output1080P = 5,
    OutputDownscale = 6,
    OutputBypass = 10,
};

// userOptions holds user preferences / customizations
struct userOptions
{
    // 0 - normal, 1 - x480/x576, 2 - customized, 3 - 1280x720, 4 - 1280x1024, 5 - 1920x1080,
    // 6 - downscale, 10 - bypass
    PresetPreference presetPreference;
    uint8_t presetSlot;
    uint8_t enableFrameTimeLock;
    uint8_t frameTimeLockMethod;
    uint8_t enableAutoGain;
    uint8_t wantScanlines;
    uint8_t wantOutputComponent;
    uint8_t deintMode;
    uint8_t wantVdsLineFilter;
    uint8_t wantPeaking;
    uint8_t wantTap6;
    uint8_t preferScalingRgbhv;
    uint8_t PalForce60;
    uint8_t disableExternalClockGenerator;
    uint8_t matchPresetSource;
    uint8_t wantStepResponse;
    uint8_t wantFullHeight;
    uint8_t enableCalibrationADC;
    uint8_t scanlineStrength;
};

// runTimeOptions holds system variables
struct runTimeOptions
{
    uint32_t freqExtClockGen;
    uint16_t noSyncCounter; // is always at least 1 when checking value in syncwatcher
    uint8_t presetVlineShift;
    uint8_t videoStandardInput; // 0 - unknown, 1 - NTSC like, 2 - PAL like, 3 480p NTSC, 4 576p PAL
    uint8_t phaseSP;
    uint8_t phaseADC;
    uint8_t currentLevelSOG;
    uint8_t thisSourceMaxLevelSOG;
    uint8_t syncLockFailIgnore;
    uint8_t applyPresetDoneStage;
    uint8_t continousStableCounter;
    uint8_t failRetryAttempts;
    uint8_t presetID;  // PresetID
    bool isCustomPreset;
    uint8_t HPLLState;
    uint8_t medResLineCount;
    uint8_t osr;
    uint8_t notRecognizedCounter;
    bool isInLowPowerMode;
    bool clampPositionIsSet;
    bool coastPositionIsSet;
    bool phaseIsSet;
    bool inputIsYpBpR;
    bool syncWatcherEnabled;
    bool outModeHdBypass;
    bool printInfos;
    bool sourceDisconnected;
    bool webServerEnabled;
    bool webServerStarted;
    bool allowUpdatesOTA;
    bool enableDebugPings;
    bool autoBestHtotalEnabled;
    bool videoIsFrozen;
    bool forceRetime;
    bool motionAdaptiveDeinterlaceActive;
    bool deinterlaceAutoEnabled;
    bool scanlinesEnabled;
    bool boardHasPower;
    bool presetIsPalForce60;
    bool syncTypeCsync;
    bool isValidForScalingRGBHV;
    bool useHdmiSyncFix;
    bool extClockGenDetected;
};
// remember adc options across presets
struct adcOptions
{
    // If `uopt->enableAutoGain == 1` and we're not before/during
    // doPostPresetLoadSteps(), `adco->r_gain` must match `GBS::ADC_RGCTRL`.
    //
    // When we either set `uopt->enableAutoGain = 1` or call
    // `GBS::ADC_RGCTRL::write()`, we must either call
    // `GBS::ADC_RGCTRL::write(adco->r_gain)`, or set `adco->r_gain =
    // GBS::ADC_RGCTRL::read()`.
    uint8_t r_gain;
    uint8_t g_gain;
    uint8_t b_gain;
    uint8_t r_off;
    uint8_t g_off;
    uint8_t b_off;
};

/// Video processing mode, loaded into register GBS_PRESET_ID by applyPresets()
/// and read to rto->presetID by doPostPresetLoadSteps(). Shown on web UI.
enum PresetID : uint8_t {
    PresetHdBypass = 0x21,
    PresetBypassRGBHV = 0x22,
};

extern struct runTimeOptions *rto;
extern struct userOptions *uopt;
extern struct adcOptions *adco;

const char preferencesFile[] PROGMEM = "/preferencesv2.txt";
const char systemInfo[] PROGMEM = "h:%4u v:%4u PLL:%01u A:%02x%02x%02x S:%02x.%02x.%02x %c%c%c%c I:%02x D:%04x m:%hu ht:%4d vt:%4d hpw:%4d u:%3x s:%2x S:%2d W:%2d\n";
const char commandDescr[] PROGMEM = "%s command %c (0x%02X) at settings source %d, custom slot %d, status %x\n";

#ifdef THIS_DEVICE_MASTER
const char ap_ssid[] PROGMEM = "gbscontrol";
const char ap_password[] PROGMEM = "qqqqqqqq";
const char gbsc_device_hostname[] PROGMEM = "gbscontrol"; // for MDNS
#else
const char ap_ssid[] PROGMEM = "gbsslave";
const char ap_password[] PROGMEM = "qqqqqqqq";
const char gbsc_device_hostname[] PROGMEM = "gbsslave"; // for MDNS
#endif

#endif                                  // _OPTIONS_H_