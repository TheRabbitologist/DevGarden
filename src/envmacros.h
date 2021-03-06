#define DG_NAME "DevGarden"
#define DG_VERSION_MAJOR 0
#define DG_VERSION_MINOR 0
#define DG_VERSION_PATCH 0

#if defined(__linux__)
	#define DG_ENV_LINUX
	#define DG_ENV_UNIX
	#define DG_ENV_POSIX
#elif defined (__APPLE__) & defined (__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_OS_MAC == 1
		#define DG_ENV_MACOS
		#define DG_ENV_UNIX
		#define DG_ENV_POSIX
	#endif
#elif defined(__unix__) || defined(__unix)
	#define DG_ENV_UNIX
	#define DG_ENV_POSIX
	#include <sys/param.h>
	#ifdef(BSD)
		#define DG_ENV_BSD
	#endif
#elif defined(__CYGWIN__)
	#define DG_ENV_WINDOZE
	#define DG_ENV_CYGWIN
	#define DG_ENV_POSIX
#elif defined(_WIN32)
	#define DG_ENV_WINDOZE
#elif defined(_POSIX_VERSION)
	#define DG_ENV_POSIX
#endif

#if defined(DG_ENV_LINUX)
	#define DG_ENV "Linux"
#elif defined(DG_ENV_MACOS)
	#define DG_ENV "Mac OS"
#elif defined(DG_ENV_CYGWIN)
	#define DG_ENV "Windows (Cygwin)"
#elif defined(DG_ENV_WINDOZE)
	#define DG_ENV "Windows"
#elif defined(DG_ENV_BSD)
	#define DG_ENV "BSD"
#elif defined(DG_ENV_IOS)
	#define DG_ENV "Apple iOS"
#elif defined(DG_ENV_UNIX)
	#define DG_ENV "Unknown (UNIX)"
#elif defined(DG_ENV_POSIX)
	#define DG_ENV "Unknown (POSIX)"
#else
	#define DG_ENV "Unknown"
#endif

#if defined(DG_ENV_MACOS)
	#define DG_CONFIG_PREFIX_GLOBAL "/Library/Application Support/"
	#define DG_CONFIG_PREFIX_LOCAL  "Library/Application Support/"
#elif defined(DG_ENV_WINDOZE)
	#define DG_CONFIG_PREFIX_GLOBAL "ProgramData/"
	#define DG_CONFIG_PREFIX_LOCAL  "AppData/Roaming/"
#elif defined(DG_ENV_UNIX)
	#define DG_CONFIG_PREFIX_GLOBAL "/usr/share/"
#if defined(DG_ENV_LINUX)
	#define DG_CONFIG_PREFIX_LOCAL  ".local/share/"
#else
	#define DG_CONFIG_PREFIX_LOCAL  "."
	#define DG_CONFIG_PREFIX_LOCAL_NOCD
#endif
#else
	#define DG_CONFIG_PREFIX_GLOBAL "/"
	#define DG_CONFIG_PREFIX_LOCAL  ""
	#define DG_CONFIG_PREFIX_LOCAL_NOCD
#endif
