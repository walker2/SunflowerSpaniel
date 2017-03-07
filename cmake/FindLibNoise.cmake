# Locate libnoise.
# This module defines
# LIBNOISE_LIBRARY
# LIBNOISE_FOUND, if false, do not try to link to libnoise
# LIBNOISE_INCLUDE_DIR, where to find the headers

FIND_PATH(LIBNOISE_INCLUDE_DIR noise.h
        $ENV{LIBNOISE_DIR}
        NO_DEFAULT_PATH
        PATH_SUFFIXES include
        )

FIND_PATH(LIBNOISE_INCLUDE_DIR noise.h
        PATHS
        ~/Library/Frameworks/noise/Headers
        /Library/Frameworks/noise/Headers
        /usr/local/include/noise
        /usr/local/include/libnoise
        /usr/local/include
        /usr/include/noise
        /usr/include/libnoise
        /usr/include
        /sw/include/noise
        /sw/include/libnoise
        /sw/include # Fink
        /opt/local/include/noise
        /opt/local/include/libnoise
        /opt/local/include # DarwinPorts
        /opt/csw/include/noise
        /opt/csw/include/libnoise
        /opt/csw/include # Blastwave
        /opt/include/noise
        /opt/include/libnoise
        /opt/include
        )

FIND_LIBRARY(LIBNOISE_LIBRARY
        NAMES libnoise noise
        PATHS
        $ENV{LIBNOISE_DIR}
        NO_DEFAULT_PATH
        PATH_SUFFIXES lib64 lib
        )

FIND_LIBRARY(LIBNOISE_LIBRARY
        NAMES libnoise noise
        PATHS
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local
        /usr
        /sw
        /opt/local
        /opt/csw
        /opt
        /usr/freeware
        PATH_SUFFIXES lib64 lib
        )

SET(LIBNOISE_FOUND "NO")
IF(LIBNOISE_LIBRARY AND LIBNOISE_INCLUDE_DIR)
    SET(LIBNOISE_FOUND "YES")
ENDIF(LIBNOISE_LIBRARY AND LIBNOISE_INCLUDE_DIR)