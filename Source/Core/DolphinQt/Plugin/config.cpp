#include "dup_string.h"
#include "export.h"

#include "Core/Config/AchievementSettings.h"
#include "Core/Config/FreeLookSettings.h"
#include "Core/Config/GraphicsSettings.h"
#include "Core/Config/MainSettings.h"
#include "Core/Config/NetplaySettings.h"
#include "Core/Config/SYSCONFSettings.h"
#include "Core/Config/SessionSettings.h"
#include "Core/Config/UISettings.h"
#include "Core/Config/WiimoteSettings.h"

enum class PropertyType
{
  Boolean,
  Integer,
  Unsigned16,
  Unsigned32,
  Float,
  String,
  // enums
  AspectMode,
  AudioCommon_DPL2Quality,
  ColorCorrectionRegion,
  Config_ShowCursor,
  DiscIO_Region,
  ExpansionInterface_EXIDeviceType,
  FreeLook_ControlType,
  HSP_HSPDeviceType,
  PowerPC_CPUCore,
  SerialInterface_SIDevices,
  ShaderCompilationMode,
  StereoMode,
  TextureFilteringMode,
  TriState,
  WiimoteSource
};

using ErasedProperty = void*;
struct Property
{
  ErasedProperty info;
  PropertyType type;
  const Config::Location* location;
};
using PropertyPair = std::pair<const std::string_view, Property>;

// clang-format off
#define PropertyEraseType(x) const_cast<ErasedProperty>(static_cast<const void*>(&x))
#define PropertyDeclare(name, type) { #name, { PropertyEraseType(Config::name), PropertyType::type, &Config::name.GetLocation() } }

static std::unordered_map<std::string_view, Property> g_properties
{
  // AchievementSettings
  PropertyDeclare(RA_ENABLED, Boolean),
  PropertyDeclare(RA_USERNAME, String),
  PropertyDeclare(RA_API_TOKEN, String),
  PropertyDeclare(RA_ACHIEVEMENTS_ENABLED, Boolean),
  PropertyDeclare(RA_LEADERBOARDS_ENABLED, Boolean),
  PropertyDeclare(RA_RICH_PRESENCE_ENABLED, Boolean),
  PropertyDeclare(RA_UNOFFICIAL_ENABLED, Boolean),
  PropertyDeclare(RA_ENCORE_ENABLED, Boolean),

  // FreeLookSettings
  PropertyDeclare(FREE_LOOK_ENABLED, Boolean),
  PropertyDeclare(FREE_LOOK_BACKGROUND_INPUT, Boolean),
  // FreeLook.Controller1
  PropertyDeclare(FL1_CONTROL_TYPE, FreeLook_ControlType),

  // GraphicsSettings
  // Graphics.Hardware
  PropertyDeclare(GFX_VSYNC, Boolean),
  PropertyDeclare(GFX_ADAPTER, Integer),
  // Graphics.Settings
  PropertyDeclare(GFX_WIDESCREEN_HACK, Boolean),
  PropertyDeclare(GFX_ASPECT_RATIO, AspectMode),
  PropertyDeclare(GFX_SUGGESTED_ASPECT_RATIO, AspectMode),
  PropertyDeclare(GFX_CROP, Boolean),
  PropertyDeclare(GFX_SAFE_TEXTURE_CACHE_COLOR_SAMPLES, Integer),
  PropertyDeclare(GFX_SHOW_FPS, Boolean),
  PropertyDeclare(GFX_SHOW_FTIMES, Boolean),
  PropertyDeclare(GFX_SHOW_VPS, Boolean),
  PropertyDeclare(GFX_SHOW_VTIMES, Boolean),
  PropertyDeclare(GFX_SHOW_GRAPHS, Boolean),
  PropertyDeclare(GFX_SHOW_SPEED, Boolean),
  PropertyDeclare(GFX_SHOW_SPEED_COLORS, Boolean),
  PropertyDeclare(GFX_PERF_SAMP_WINDOW, Integer),
  PropertyDeclare(GFX_SHOW_NETPLAY_PING, Boolean),
  PropertyDeclare(GFX_SHOW_NETPLAY_MESSAGES, Boolean),
  PropertyDeclare(GFX_LOG_RENDER_TIME_TO_FILE, Boolean),
  PropertyDeclare(GFX_OVERLAY_STATS, Boolean),
  PropertyDeclare(GFX_OVERLAY_PROJ_STATS, Boolean),
  PropertyDeclare(GFX_OVERLAY_SCISSOR_STATS, Boolean),
  PropertyDeclare(GFX_DUMP_TEXTURES, Boolean),
  PropertyDeclare(GFX_DUMP_MIP_TEXTURES, Boolean),
  PropertyDeclare(GFX_DUMP_BASE_TEXTURES, Boolean),
  PropertyDeclare(GFX_TEXTURE_PNG_COMPRESSION_LEVEL, Integer),
  PropertyDeclare(GFX_HIRES_TEXTURES, Boolean),
  PropertyDeclare(GFX_CACHE_HIRES_TEXTURES, Boolean),
  PropertyDeclare(GFX_DUMP_EFB_TARGET, Boolean),
  PropertyDeclare(GFX_DUMP_XFB_TARGET, Boolean),
  PropertyDeclare(GFX_DUMP_FRAMES_AS_IMAGES, Boolean),
  PropertyDeclare(GFX_USE_FFV1, Boolean),
  PropertyDeclare(GFX_DUMP_FORMAT, String),
  PropertyDeclare(GFX_DUMP_CODEC, String),
  PropertyDeclare(GFX_DUMP_PIXEL_FORMAT, String),
  PropertyDeclare(GFX_DUMP_ENCODER, String),
  PropertyDeclare(GFX_DUMP_PATH, String),
  PropertyDeclare(GFX_BITRATE_KBPS, Integer),
  PropertyDeclare(GFX_INTERNAL_RESOLUTION_FRAME_DUMPS, Boolean),
  PropertyDeclare(GFX_PNG_COMPRESSION_LEVEL, Integer),
  PropertyDeclare(GFX_ENABLE_GPU_TEXTURE_DECODING, Boolean),
  PropertyDeclare(GFX_ENABLE_PIXEL_LIGHTING, Boolean),
  PropertyDeclare(GFX_FAST_DEPTH_CALC, Boolean),
  PropertyDeclare(GFX_MSAA, Unsigned32),
  PropertyDeclare(GFX_SSAA, Boolean),
  PropertyDeclare(GFX_EFB_SCALE, Integer),
  PropertyDeclare(GFX_MAX_EFB_SCALE, Integer),
  PropertyDeclare(GFX_TEXFMT_OVERLAY_ENABLE, Boolean),
  PropertyDeclare(GFX_TEXFMT_OVERLAY_CENTER, Boolean),
  PropertyDeclare(GFX_ENABLE_WIREFRAME, Boolean),
  PropertyDeclare(GFX_DISABLE_FOG, Boolean),
  PropertyDeclare(GFX_BORDERLESS_FULLSCREEN, Boolean),
  PropertyDeclare(GFX_ENABLE_VALIDATION_LAYER, Boolean),
  PropertyDeclare(GFX_BACKEND_MULTITHREADING, Boolean),
  PropertyDeclare(GFX_COMMAND_BUFFER_EXECUTE_INTERVAL, Integer),
  PropertyDeclare(GFX_SHADER_CACHE, Boolean),
  PropertyDeclare(GFX_WAIT_FOR_SHADERS_BEFORE_STARTING, Boolean),
  PropertyDeclare(GFX_SHADER_COMPILATION_MODE, ShaderCompilationMode),
  PropertyDeclare(GFX_SHADER_COMPILER_THREADS, Integer),
  PropertyDeclare(GFX_SHADER_PRECOMPILER_THREADS, Integer),
  PropertyDeclare(GFX_SAVE_TEXTURE_CACHE_TO_STATE, Boolean),
  PropertyDeclare(GFX_PREFER_VS_FOR_LINE_POINT_EXPANSION, Boolean),
  PropertyDeclare(GFX_CPU_CULL, Boolean),
  PropertyDeclare(GFX_MTL_MANUALLY_UPLOAD_BUFFERS, TriState),
  PropertyDeclare(GFX_MTL_USE_PRESENT_DRAWABLE, TriState),
  PropertyDeclare(GFX_SW_DUMP_OBJECTS, Boolean),
  PropertyDeclare(GFX_SW_DUMP_TEV_STAGES, Boolean),
  PropertyDeclare(GFX_SW_DUMP_TEV_TEX_FETCHES, Boolean),
  PropertyDeclare(GFX_PREFER_GLES, Boolean),
  PropertyDeclare(GFX_MODS_ENABLE, Boolean),
  // Graphics.Enhancements
  PropertyDeclare(GFX_ENHANCE_FORCE_TEXTURE_FILTERING, TextureFilteringMode),
  PropertyDeclare(GFX_ENHANCE_MAX_ANISOTROPY, Integer),
  PropertyDeclare(GFX_ENHANCE_POST_SHADER, String),
  PropertyDeclare(GFX_ENHANCE_FORCE_TRUE_COLOR, Boolean),
  PropertyDeclare(GFX_ENHANCE_DISABLE_COPY_FILTER, Boolean),
  PropertyDeclare(GFX_ENHANCE_ARBITRARY_MIPMAP_DETECTION, Boolean),
  PropertyDeclare(GFX_ENHANCE_ARBITRARY_MIPMAP_DETECTION_THRESHOLD, Float),
  PropertyDeclare(GFX_ENHANCE_HDR_OUTPUT, Boolean),
  // Color.Correction
  PropertyDeclare(GFX_CC_CORRECT_COLOR_SPACE, Boolean),
  PropertyDeclare(GFX_CC_GAME_COLOR_SPACE, ColorCorrectionRegion),
  PropertyDeclare(GFX_CC_CORRECT_GAMMA, Boolean),
  PropertyDeclare(GFX_CC_GAME_GAMMA, Float),
  PropertyDeclare(GFX_CC_SDR_DISPLAY_GAMMA_SRGB, Boolean),
  PropertyDeclare(GFX_CC_SDR_DISPLAY_CUSTOM_GAMMA, Float),
  PropertyDeclare(GFX_CC_HDR_PAPER_WHITE_NITS, Float),
  // Graphics.Stereoscopy
  PropertyDeclare(GFX_STEREO_MODE, StereoMode),
  PropertyDeclare(GFX_STEREO_DEPTH, Integer),
  PropertyDeclare(GFX_STEREO_CONVERGENCE_PERCENTAGE, Integer),
  PropertyDeclare(GFX_STEREO_SWAP_EYES, Boolean),
  PropertyDeclare(GFX_STEREO_CONVERGENCE, Integer),
  PropertyDeclare(GFX_STEREO_EFB_MONO_DEPTH, Boolean),
  PropertyDeclare(GFX_STEREO_DEPTH_PERCENTAGE, Integer),
  // Graphics.Hacks
  PropertyDeclare(GFX_HACK_EFB_ACCESS_ENABLE, Boolean),
  PropertyDeclare(GFX_HACK_EFB_DEFER_INVALIDATION, Boolean),
  PropertyDeclare(GFX_HACK_EFB_ACCESS_TILE_SIZE, Integer),
  PropertyDeclare(GFX_HACK_BBOX_ENABLE, Boolean),
  PropertyDeclare(GFX_HACK_FORCE_PROGRESSIVE, Boolean),
  PropertyDeclare(GFX_HACK_SKIP_EFB_COPY_TO_RAM, Boolean),
  PropertyDeclare(GFX_HACK_SKIP_XFB_COPY_TO_RAM, Boolean),
  PropertyDeclare(GFX_HACK_DISABLE_COPY_TO_VRAM, Boolean),
  PropertyDeclare(GFX_HACK_DEFER_EFB_COPIES, Boolean),
  PropertyDeclare(GFX_HACK_IMMEDIATE_XFB, Boolean),
  PropertyDeclare(GFX_HACK_SKIP_DUPLICATE_XFBS, Boolean),
  PropertyDeclare(GFX_HACK_EARLY_XFB_OUTPUT, Boolean),
  PropertyDeclare(GFX_HACK_COPY_EFB_SCALED, Boolean),
  PropertyDeclare(GFX_HACK_EFB_EMULATE_FORMAT_CHANGES, Boolean),
  PropertyDeclare(GFX_HACK_VERTEX_ROUNDING, Boolean),
  PropertyDeclare(GFX_HACK_VI_SKIP, Boolean),
  PropertyDeclare(GFX_HACK_MISSING_COLOR_VALUE, Unsigned32),
  PropertyDeclare(GFX_HACK_FAST_TEXTURE_SAMPLING, Boolean),
#ifdef __APPLE__
  PropertyDeclare(GFX_HACK_NO_MIPMAPPING, Boolean),
#endif
  // Graphics.GameSpecific
  PropertyDeclare(GFX_PERF_QUERIES_ENABLE, Boolean),
  // Android custom GPU drivers
  PropertyDeclare(GFX_DRIVER_LIB_NAME, String),

  // MainSettings
  // Main.Core
  PropertyDeclare(MAIN_SKIP_IPL, Boolean),
  PropertyDeclare(MAIN_CPU_CORE, PowerPC_CPUCore),
  PropertyDeclare(MAIN_JIT_FOLLOW_BRANCH, Boolean),
  PropertyDeclare(MAIN_FASTMEM, Boolean),
  PropertyDeclare(MAIN_ACCURATE_CPU_CACHE, Boolean),
  PropertyDeclare(MAIN_DSP_HLE, Boolean),
  PropertyDeclare(MAIN_MAX_FALLBACK, Integer),
  PropertyDeclare(MAIN_TIMING_VARIANCE, Integer),
  PropertyDeclare(MAIN_CPU_THREAD, Boolean),
  PropertyDeclare(MAIN_SYNC_ON_SKIP_IDLE, Boolean),
  PropertyDeclare(MAIN_DEFAULT_ISO, String),
  PropertyDeclare(MAIN_ENABLE_CHEATS, Boolean),
  PropertyDeclare(MAIN_GC_LANGUAGE, Integer),
  PropertyDeclare(MAIN_OVERRIDE_REGION_SETTINGS, Boolean),
  PropertyDeclare(MAIN_DPL2_DECODER, Boolean),
  PropertyDeclare(MAIN_DPL2_QUALITY, AudioCommon_DPL2Quality),
  PropertyDeclare(MAIN_AUDIO_LATENCY, Integer),
  PropertyDeclare(MAIN_AUDIO_STRETCH, Boolean),
  PropertyDeclare(MAIN_AUDIO_STRETCH_LATENCY, Integer),
  PropertyDeclare(MAIN_MEMCARD_A_PATH, String),
  PropertyDeclare(MAIN_MEMCARD_B_PATH, String),
  PropertyDeclare(MAIN_AGP_CART_A_PATH, String),
  PropertyDeclare(MAIN_AGP_CART_B_PATH, String),
  PropertyDeclare(MAIN_GCI_FOLDER_A_PATH, String),
  PropertyDeclare(MAIN_GCI_FOLDER_B_PATH, String),
  PropertyDeclare(MAIN_GCI_FOLDER_A_PATH_OVERRIDE, String),
  PropertyDeclare(MAIN_GCI_FOLDER_B_PATH_OVERRIDE, String),
  PropertyDeclare(MAIN_MEMORY_CARD_SIZE, Integer),
  PropertyDeclare(MAIN_SLOT_A, ExpansionInterface_EXIDeviceType),
  PropertyDeclare(MAIN_SLOT_B, ExpansionInterface_EXIDeviceType),
  PropertyDeclare(MAIN_SERIAL_PORT_1, ExpansionInterface_EXIDeviceType),
  PropertyDeclare(MAIN_BBA_MAC, String),
  PropertyDeclare(MAIN_BBA_XLINK_IP, String),
  PropertyDeclare(MAIN_BBA_XLINK_CHAT_OSD, Boolean),
  PropertyDeclare(MAIN_BBA_BUILTIN_DNS, String),
  PropertyDeclare(MAIN_BBA_BUILTIN_IP, String),
  PropertyDeclare(MAIN_WII_SD_CARD, Boolean),
  PropertyDeclare(MAIN_WII_SD_CARD_ENABLE_FOLDER_SYNC, Boolean),
  PropertyDeclare(MAIN_WII_KEYBOARD, Boolean),
  PropertyDeclare(MAIN_WIIMOTE_CONTINUOUS_SCANNING, Boolean),
  PropertyDeclare(MAIN_WIIMOTE_ENABLE_SPEAKER, Boolean),
  PropertyDeclare(MAIN_CONNECT_WIIMOTES_FOR_CONTROLLER_INTERFACE, Boolean),
  PropertyDeclare(MAIN_MMU, Boolean),
  PropertyDeclare(MAIN_PAUSE_ON_PANIC, Boolean),
  PropertyDeclare(MAIN_BB_DUMP_PORT, Integer),
  PropertyDeclare(MAIN_SYNC_GPU, Boolean),
  PropertyDeclare(MAIN_SYNC_GPU_MAX_DISTANCE, Integer),
  PropertyDeclare(MAIN_SYNC_GPU_MIN_DISTANCE, Integer),
  PropertyDeclare(MAIN_SYNC_GPU_OVERCLOCK, Float),
  PropertyDeclare(MAIN_FAST_DISC_SPEED, Boolean),
  PropertyDeclare(MAIN_LOW_DCBZ_HACK, Boolean),
  PropertyDeclare(MAIN_FLOAT_EXCEPTIONS, Boolean),
  PropertyDeclare(MAIN_DIVIDE_BY_ZERO_EXCEPTIONS, Boolean),
  PropertyDeclare(MAIN_FPRF, Boolean),
  PropertyDeclare(MAIN_ACCURATE_NANS, Boolean),
  PropertyDeclare(MAIN_DISABLE_ICACHE, Boolean),
  PropertyDeclare(MAIN_EMULATION_SPEED, Float),
  PropertyDeclare(MAIN_OVERCLOCK, Float),
  PropertyDeclare(MAIN_OVERCLOCK_ENABLE, Boolean),
  PropertyDeclare(MAIN_RAM_OVERRIDE_ENABLE, Boolean),
  PropertyDeclare(MAIN_MEM1_SIZE, Unsigned32),
  PropertyDeclare(MAIN_MEM2_SIZE, Unsigned32),
  PropertyDeclare(MAIN_GFX_BACKEND, String),
  PropertyDeclare(MAIN_HSP_DEVICE, HSP_HSPDeviceType),
  PropertyDeclare(MAIN_ARAM_EXPANSION_SIZE, Unsigned32),
  PropertyDeclare(MAIN_GPU_DETERMINISM_MODE, String),
  PropertyDeclare(MAIN_PERF_MAP_DIR, String),
  PropertyDeclare(MAIN_CUSTOM_RTC_ENABLE, Boolean),
  PropertyDeclare(MAIN_CUSTOM_RTC_VALUE, Unsigned32),
  PropertyDeclare(MAIN_AUTO_DISC_CHANGE, Boolean),
  PropertyDeclare(MAIN_ALLOW_SD_WRITES, Boolean),
  PropertyDeclare(MAIN_ENABLE_SAVESTATES, Boolean),
  PropertyDeclare(MAIN_FALLBACK_REGION, DiscIO_Region),
  PropertyDeclare(MAIN_REAL_WII_REMOTE_REPEAT_REPORTS, Boolean),
  PropertyDeclare(MAIN_OVERRIDE_BOOT_IOS, Unsigned32),
  PropertyDeclare(MAIN_WII_NUS_SHOP_URL, String),
  PropertyDeclare(MAIN_WII_WIILINK_ENABLE, Boolean),
  // Main.DSP
  PropertyDeclare(MAIN_DSP_THREAD, Boolean),
  PropertyDeclare(MAIN_DSP_CAPTURE_LOG, Boolean),
  PropertyDeclare(MAIN_DSP_JIT, Boolean),
  PropertyDeclare(MAIN_DUMP_AUDIO, Boolean),
  PropertyDeclare(MAIN_DUMP_AUDIO_SILENT, Boolean),
  PropertyDeclare(MAIN_DUMP_UCODE, Boolean),
  PropertyDeclare(MAIN_AUDIO_BACKEND, String),
  PropertyDeclare(MAIN_AUDIO_VOLUME, Integer),
  PropertyDeclare(MAIN_AUDIO_MUTED, Boolean),
#ifdef _WIN32
  PropertyDeclare(MAIN_WASAPI_DEVICE, String),
#endif
  // Main.Display
  PropertyDeclare(MAIN_FULLSCREEN_DISPLAY_RES, String),
  PropertyDeclare(MAIN_FULLSCREEN, Boolean),
  PropertyDeclare(MAIN_RENDER_TO_MAIN, Boolean),
  PropertyDeclare(MAIN_RENDER_WINDOW_XPOS, Integer),
  PropertyDeclare(MAIN_RENDER_WINDOW_YPOS, Integer),
  PropertyDeclare(MAIN_RENDER_WINDOW_WIDTH, Integer),
  PropertyDeclare(MAIN_RENDER_WINDOW_HEIGHT, Integer),
  PropertyDeclare(MAIN_RENDER_WINDOW_AUTOSIZE, Boolean),
  PropertyDeclare(MAIN_KEEP_WINDOW_ON_TOP, Boolean),
  PropertyDeclare(MAIN_DISABLE_SCREENSAVER, Boolean),
  // Main.General
  PropertyDeclare(MAIN_DUMP_PATH, String),
  PropertyDeclare(MAIN_LOAD_PATH, String),
  PropertyDeclare(MAIN_RESOURCEPACK_PATH, String),
  PropertyDeclare(MAIN_FS_PATH, String),
  PropertyDeclare(MAIN_WII_SD_CARD_IMAGE_PATH, String),
  PropertyDeclare(MAIN_WII_SD_CARD_SYNC_FOLDER_PATH, String),
  PropertyDeclare(MAIN_WFS_PATH, String),
  PropertyDeclare(MAIN_SHOW_LAG, Boolean),
  PropertyDeclare(MAIN_SHOW_FRAME_COUNT, Boolean),
  PropertyDeclare(MAIN_WIRELESS_MAC, String),
  PropertyDeclare(MAIN_GDB_SOCKET, String),
  PropertyDeclare(MAIN_GDB_PORT, Integer),
  PropertyDeclare(MAIN_ISO_PATH_COUNT, Integer),
  PropertyDeclare(MAIN_SKYLANDERS_PATH, String),
  // Main.GBA
#ifdef HAS_LIBMGBA
  PropertyDeclare(MAIN_GBA_BIOS_PATH, String),
  PropertyDeclare(MAIN_GBA_ROM_PATHS[0], String),
  PropertyDeclare(MAIN_GBA_ROM_PATHS[1], String),
  PropertyDeclare(MAIN_GBA_ROM_PATHS[2], String),
  PropertyDeclare(MAIN_GBA_ROM_PATHS[3], String),
  PropertyDeclare(MAIN_GBA_SAVES_PATH, String),
  PropertyDeclare(MAIN_GBA_SAVES_IN_ROM_PATH, Boolean),
  PropertyDeclare(MAIN_GBA_THREADS, Boolean),
#endif
  // Main.Network
  PropertyDeclare(MAIN_NETWORK_SSL_DUMP_READ, Boolean),
  PropertyDeclare(MAIN_NETWORK_SSL_DUMP_WRITE, Boolean),
  PropertyDeclare(MAIN_NETWORK_SSL_VERIFY_CERTIFICATES, Boolean),
  PropertyDeclare(MAIN_NETWORK_SSL_DUMP_ROOT_CA, Boolean),
  PropertyDeclare(MAIN_NETWORK_SSL_DUMP_PEER_CERT, Boolean),
  PropertyDeclare(MAIN_NETWORK_DUMP_BBA, Boolean),
  PropertyDeclare(MAIN_NETWORK_DUMP_AS_PCAP, Boolean),
  PropertyDeclare(MAIN_NETWORK_TIMEOUT, Integer),
  // Main.Interface
  PropertyDeclare(MAIN_USE_HIGH_CONTRAST_TOOLTIPS, Boolean),
  PropertyDeclare(MAIN_USE_PANIC_HANDLERS, Boolean),
  PropertyDeclare(MAIN_ABORT_ON_PANIC_ALERT, Boolean),
  PropertyDeclare(MAIN_OSD_MESSAGES, Boolean),
  PropertyDeclare(MAIN_SKIP_NKIT_WARNING, Boolean),
  PropertyDeclare(MAIN_CONFIRM_ON_STOP, Boolean),
  PropertyDeclare(MAIN_SHOW_CURSOR, Config_ShowCursor),
  PropertyDeclare(MAIN_LOCK_CURSOR, Boolean),
  PropertyDeclare(MAIN_INTERFACE_LANGUAGE, String),
  PropertyDeclare(MAIN_SHOW_ACTIVE_TITLE, Boolean),
  PropertyDeclare(MAIN_USE_BUILT_IN_TITLE_DATABASE, Boolean),
  PropertyDeclare(MAIN_THEME_NAME, String),
  PropertyDeclare(MAIN_PAUSE_ON_FOCUS_LOST, Boolean),
  PropertyDeclare(MAIN_ENABLE_DEBUGGING, Boolean),
  // Main.Analytics
  PropertyDeclare(MAIN_ANALYTICS_ID, String),
  PropertyDeclare(MAIN_ANALYTICS_ENABLED, Boolean),
  PropertyDeclare(MAIN_ANALYTICS_PERMISSION_ASKED, Boolean),
  // Main.GameList
  PropertyDeclare(MAIN_GAMELIST_LIST_DRIVES, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_WAD, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_ELF_DOL, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_WII, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_GC, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_JPN, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_PAL, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_USA, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_AUSTRALIA, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_FRANCE, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_GERMANY, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_ITALY, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_KOREA, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_NETHERLANDS, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_RUSSIA, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_SPAIN, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_TAIWAN, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_WORLD, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_UNKNOWN, Boolean),
  PropertyDeclare(MAIN_GAMELIST_LIST_SORT, Integer),
  PropertyDeclare(MAIN_GAMELIST_LIST_SORT_SECONDARY, Integer),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_PLATFORM, Boolean),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_DESCRIPTION, Boolean),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_BANNER, Boolean),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_TITLE, Boolean),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_MAKER, Boolean),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_FILE_NAME, Boolean),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_FILE_PATH, Boolean),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_GAME_ID, Boolean),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_REGION, Boolean),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_FILE_SIZE, Boolean),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_FILE_FORMAT, Boolean),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_BLOCK_SIZE, Boolean),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_COMPRESSION, Boolean),
  PropertyDeclare(MAIN_GAMELIST_COLUMN_TAGS, Boolean),
  // Main.FifoPlayer
  PropertyDeclare(MAIN_FIFOPLAYER_LOOP_REPLAY, Boolean),
  PropertyDeclare(MAIN_FIFOPLAYER_EARLY_MEMORY_UPDATES, Boolean),
  // Main.AutoUpdate
  PropertyDeclare(MAIN_AUTOUPDATE_UPDATE_TRACK, String),
  PropertyDeclare(MAIN_AUTOUPDATE_HASH_OVERRIDE, String),
  // Main.Movie
  PropertyDeclare(MAIN_MOVIE_PAUSE_MOVIE, Boolean),
  PropertyDeclare(MAIN_MOVIE_MOVIE_AUTHOR, String),
  PropertyDeclare(MAIN_MOVIE_DUMP_FRAMES, Boolean),
  PropertyDeclare(MAIN_MOVIE_DUMP_FRAMES_SILENT, Boolean),
  PropertyDeclare(MAIN_MOVIE_SHOW_INPUT_DISPLAY, Boolean),
  PropertyDeclare(MAIN_MOVIE_SHOW_RTC, Boolean),
  PropertyDeclare(MAIN_MOVIE_SHOW_RERECORD, Boolean),
  // Main.Input
  PropertyDeclare(MAIN_INPUT_BACKGROUND_INPUT, Boolean),
  // Main.Debug
  PropertyDeclare(MAIN_DEBUG_JIT_OFF, Boolean),
  PropertyDeclare(MAIN_DEBUG_JIT_LOAD_STORE_OFF, Boolean),
  PropertyDeclare(MAIN_DEBUG_JIT_LOAD_STORE_LXZ_OFF, Boolean),
  PropertyDeclare(MAIN_DEBUG_JIT_LOAD_STORE_LWZ_OFF, Boolean),
  PropertyDeclare(MAIN_DEBUG_JIT_LOAD_STORE_LBZX_OFF, Boolean),
  PropertyDeclare(MAIN_DEBUG_JIT_LOAD_STORE_FLOATING_OFF, Boolean),
  PropertyDeclare(MAIN_DEBUG_JIT_LOAD_STORE_PAIRED_OFF, Boolean),
  PropertyDeclare(MAIN_DEBUG_JIT_FLOATING_POINT_OFF, Boolean),
  PropertyDeclare(MAIN_DEBUG_JIT_INTEGER_OFF, Boolean),
  PropertyDeclare(MAIN_DEBUG_JIT_PAIRED_OFF, Boolean),
  PropertyDeclare(MAIN_DEBUG_JIT_SYSTEM_REGISTERS_OFF, Boolean),
  PropertyDeclare(MAIN_DEBUG_JIT_BRANCH_OFF, Boolean),
  PropertyDeclare(MAIN_DEBUG_JIT_REGISTER_CACHE_OFF, Boolean),
  // Main.BluetoothPassthrough
  PropertyDeclare(MAIN_BLUETOOTH_PASSTHROUGH_ENABLED, Boolean),
  PropertyDeclare(MAIN_BLUETOOTH_PASSTHROUGH_VID, Integer),
  PropertyDeclare(MAIN_BLUETOOTH_PASSTHROUGH_PID, Integer),
  PropertyDeclare(MAIN_BLUETOOTH_PASSTHROUGH_LINK_KEYS, String),
  // Main.USBPassthrough
  PropertyDeclare(MAIN_USB_PASSTHROUGH_DEVICES, String),
  // Main.EmulatedUSBDevices
  PropertyDeclare(MAIN_EMULATE_SKYLANDER_PORTAL, Boolean),
  PropertyDeclare(MAIN_EMULATE_INFINITY_BASE, Boolean),

  // NetplaySettings
  // Main.NetPlay
  PropertyDeclare(NETPLAY_TRAVERSAL_SERVER, String),
  PropertyDeclare(NETPLAY_TRAVERSAL_PORT, Unsigned16),
  PropertyDeclare(NETPLAY_TRAVERSAL_CHOICE, String),
  PropertyDeclare(NETPLAY_HOST_CODE, String),
  PropertyDeclare(NETPLAY_INDEX_URL, String),
  PropertyDeclare(NETPLAY_HOST_PORT, Unsigned16),
  PropertyDeclare(NETPLAY_ADDRESS, String),
  PropertyDeclare(NETPLAY_CONNECT_PORT, Unsigned16),
  PropertyDeclare(NETPLAY_LISTEN_PORT, Unsigned16),
  PropertyDeclare(NETPLAY_NICKNAME, String),
  PropertyDeclare(NETPLAY_USE_UPNP, Boolean),
  PropertyDeclare(NETPLAY_ENABLE_QOS, Boolean),
  PropertyDeclare(NETPLAY_USE_INDEX, Boolean),
  PropertyDeclare(NETPLAY_INDEX_REGION, String),
  PropertyDeclare(NETPLAY_INDEX_NAME, String),
  PropertyDeclare(NETPLAY_INDEX_PASSWORD, String),
  PropertyDeclare(NETPLAY_ENABLE_CHUNKED_UPLOAD_LIMIT, Boolean),
  PropertyDeclare(NETPLAY_CHUNKED_UPLOAD_LIMIT, Unsigned32),
  PropertyDeclare(NETPLAY_BUFFER_SIZE, Unsigned32),
  PropertyDeclare(NETPLAY_CLIENT_BUFFER_SIZE, Unsigned32),
  PropertyDeclare(NETPLAY_SAVEDATA_LOAD, Boolean),
  PropertyDeclare(NETPLAY_SAVEDATA_WRITE, Boolean),
  PropertyDeclare(NETPLAY_SAVEDATA_SYNC_ALL_WII, Boolean),
  PropertyDeclare(NETPLAY_SYNC_CODES, Boolean),
  PropertyDeclare(NETPLAY_RECORD_INPUTS, Boolean),
  PropertyDeclare(NETPLAY_STRICT_SETTINGS_SYNC, Boolean),
  PropertyDeclare(NETPLAY_NETWORK_MODE, String),
  PropertyDeclare(NETPLAY_GOLF_MODE_OVERLAY, Boolean),
  PropertyDeclare(NETPLAY_HIDE_REMOTE_GBAS, Boolean),

  // SessionSettings
  PropertyDeclare(SESSION_USE_FMA, Boolean),
  PropertyDeclare(SESSION_LOAD_IPL_DUMP, Boolean),
  PropertyDeclare(SESSION_GCI_FOLDER_CURRENT_GAME_ONLY, Boolean),
  PropertyDeclare(SESSION_CODE_SYNC_OVERRIDE, Boolean),
  PropertyDeclare(SESSION_SAVE_DATA_WRITABLE, Boolean),
  PropertyDeclare(SESSION_SHOULD_FAKE_ERROR_001, Boolean),

  // SYSCONFSettings
  // SYSCONF.IPL
  PropertyDeclare(SYSCONF_SCREENSAVER, Boolean),
  PropertyDeclare(SYSCONF_LANGUAGE, Unsigned32),
  PropertyDeclare(SYSCONF_COUNTRY, Unsigned32),
  PropertyDeclare(SYSCONF_WIDESCREEN, Boolean),
  PropertyDeclare(SYSCONF_PROGRESSIVE_SCAN, Boolean),
  PropertyDeclare(SYSCONF_PAL60, Boolean),
  PropertyDeclare(SYSCONF_SOUND_MODE, Unsigned32),
  // SYSCONF.BT
  PropertyDeclare(SYSCONF_SENSOR_BAR_POSITION, Unsigned32),
  PropertyDeclare(SYSCONF_SENSOR_BAR_SENSITIVITY, Unsigned32),
  PropertyDeclare(SYSCONF_SPEAKER_VOLUME, Unsigned32),
  PropertyDeclare(SYSCONF_WIIMOTE_MOTOR, Boolean),

  // UISettings
  // UI.General
  PropertyDeclare(MAIN_USE_DISCORD_PRESENCE, Boolean),
  PropertyDeclare(MAIN_USE_GAME_COVERS, Boolean),
  PropertyDeclare(MAIN_FOCUSED_HOTKEYS, Boolean),
  PropertyDeclare(MAIN_RECURSIVE_ISO_PATHS, Boolean),

  // WiimoteSettings
  PropertyDeclare(WIIMOTE_1_SOURCE, WiimoteSource),
  PropertyDeclare(WIIMOTE_2_SOURCE, WiimoteSource),
  PropertyDeclare(WIIMOTE_3_SOURCE, WiimoteSource),
  PropertyDeclare(WIIMOTE_4_SOURCE, WiimoteSource),
  PropertyDeclare(WIIMOTE_BB_SOURCE, WiimoteSource)
};

static thread_local Property g_temp_property;

#define SetCallableProperty(call, type) \
  const auto& info = call; \
  g_temp_property = { PropertyEraseType(info), PropertyType::type,  &info.GetLocation() }; \
  return &g_temp_property
// clang-format on

static std::string str_toupper(std::string s)
{
  std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::toupper(c); });
  return s;
}

static bool str_iequals(const std::string& a, const std::string& b)
{
  return std::equal(a.begin(), a.end(), b.begin(), b.end(),
                    [](char a, char b) { return toupper(a) == toupper(b); });
}

EXPORT Property* config_find_info_by_name(const char* name)
{
  const auto it = g_properties.find(str_toupper(name));
  return it != g_properties.end() ? &it->second : nullptr;
}

EXPORT Property* config_find_info_by_location(int system, const char* section, const char* key)
{
  // clang-format off
  const auto it = std::find_if(g_properties.begin(), g_properties.end(),
    [system, section, key](PropertyPair& i) {
      const auto location = i.second.location;
      return (system < 0 && str_iequals(location->section, section) && str_iequals(location->key, key)) ||
        (system == static_cast<int>(location->system) && str_iequals(location->section, section) && str_iequals(location->key, key));
    });
  // clang-format on
  return it != g_properties.end() ? &it->second : nullptr;
}

template <PropertyType type, class T>
static T get_typed(Property* property, bool uncached)
{
  if (property->type == type)
  {
    const auto& info = *static_cast<Config::Info<T>*>(property->info);
    return uncached ? Config::GetUncached(info) : Config::GetBase(info);
  }
  return {};
}

static int get_enum(Property* property, bool uncached)
{
  if (property->type >= PropertyType::AspectMode && property->type <= PropertyType::WiimoteSource)
  {
    const auto& info = *static_cast<Config::Info<int>*>(property->info);
    return uncached ? Config::GetUncached(info) : Config::GetBase(info);
  }
  return {};
}

EXPORT bool config_get_boolean(Property* property, bool uncached)
{
  return get_typed<PropertyType::Boolean, bool>(property, uncached);
}

EXPORT int config_get_integer(Property* property, bool uncached)
{
  return get_typed<PropertyType::Integer, int>(property, uncached);
}

EXPORT u16 config_get_unsigned16(Property* property, bool uncached)
{
  return get_typed<PropertyType::Unsigned16, u16>(property, uncached);
}

EXPORT u32 config_get_unsigned32(Property* property, bool uncached)
{
  return get_typed<PropertyType::Unsigned32, u32>(property, uncached);
}

EXPORT float config_get_float(Property* property, bool uncached)
{
  return get_typed<PropertyType::Float, float>(property, uncached);
}

EXPORT char* config_get_string(Property* property, bool uncached)
{
  return dup_std_string(get_typed<PropertyType::String, std::string>(property, uncached));
}

EXPORT int config_get_enum(Property* property, bool uncached)
{
  return get_enum(property, uncached);
}

template <PropertyType type, class T>
static void set_typed(Property* property, bool uncached, T value)
{
  if (property->type == type)
  {
    const auto& info = *static_cast<Config::Info<T>*>(property->info);
    if (uncached)
      Config::SetCurrent(info, value);
    else
      Config::SetBase(info, value);
  }
}

static void set_enum(Property* property, bool uncached, int value)
{
  if (property->type >= PropertyType::AspectMode && property->type <= PropertyType::WiimoteSource)
  {
    const auto& info = *static_cast<Config::Info<int>*>(property->info);
    if (uncached)
      Config::SetCurrent(info, value);
    else
      Config::SetBase(info, value);
  }
}

EXPORT void config_set_boolean(Property* property, bool uncached, bool value)
{
  set_typed<PropertyType::Boolean, bool>(property, uncached, value);
}

EXPORT void config_set_integer(Property* property, bool uncached, int value)
{
  set_typed<PropertyType::Integer, int>(property, uncached, value);
}

EXPORT void config_set_unsigned16(Property* property, bool uncached, u16 value)
{
  set_typed<PropertyType::Unsigned16, u16>(property, uncached, value);
}

EXPORT void config_set_unsigned32(Property* property, bool uncached, u32 value)
{
  set_typed<PropertyType::Unsigned32, u32>(property, uncached, value);
}

EXPORT void config_set_float(Property* property, bool uncached, float value)
{
  set_typed<PropertyType::Float, float>(property, uncached, value);
}

EXPORT void config_set_string(Property* property, bool uncached, const char* value)
{
  set_typed<PropertyType::String, std::string>(property, uncached, value);
}

EXPORT void config_set_enum(Property* property, bool uncached, int value)
{
  set_enum(property, uncached, value);
}

EXPORT Property* config_get_info_for_memcard_path(int slot)
{
  SetCallableProperty(Config::GetInfoForMemcardPath(static_cast<ExpansionInterface::Slot>(slot)),
                      String);
}

EXPORT Property* config_get_info_for_agp_cart_path(int slot)
{
  SetCallableProperty(Config::GetInfoForAGPCartPath(static_cast<ExpansionInterface::Slot>(slot)),
                      String);
}

EXPORT Property* config_get_info_for_gci_path(int slot)
{
  SetCallableProperty(Config::GetInfoForGCIPath(static_cast<ExpansionInterface::Slot>(slot)),
                      String);
}

EXPORT Property* config_get_info_for_gci_path_override(int slot)
{
  SetCallableProperty(
      Config::GetInfoForGCIPathOverride(static_cast<ExpansionInterface::Slot>(slot)), String);
}

EXPORT Property* config_get_info_for_exi_device(int slot)
{
  SetCallableProperty(Config::GetInfoForEXIDevice(static_cast<ExpansionInterface::Slot>(slot)),
                      ExpansionInterface_EXIDeviceType);
}

EXPORT Property* config_get_info_for_si_device(int channel)
{
  SetCallableProperty(Config::GetInfoForSIDevice(channel), SerialInterface_SIDevices);
}

EXPORT Property* config_get_info_for_adapter_rumble(int channel)
{
  SetCallableProperty(Config::GetInfoForAdapterRumble(channel), Boolean);
}

EXPORT Property* config_get_info_for_simulate_konga(int channel)
{
  SetCallableProperty(Config::GetInfoForSimulateKonga(channel), Boolean);
}

EXPORT Property* config_get_info_for_wiimote_source(int index)
{
  SetCallableProperty(Config::GetInfoForWiimoteSource(index), WiimoteSource);
}
