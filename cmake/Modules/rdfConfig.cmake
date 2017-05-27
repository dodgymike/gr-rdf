INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_RDF rdf)

FIND_PATH(
    RDF_INCLUDE_DIRS
    NAMES rdf/api.h
    HINTS $ENV{RDF_DIR}/include
        ${PC_RDF_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    RDF_LIBRARIES
    NAMES gnuradio-rdf
    HINTS $ENV{RDF_DIR}/lib
        ${PC_RDF_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(RDF DEFAULT_MSG RDF_LIBRARIES RDF_INCLUDE_DIRS)
MARK_AS_ADVANCED(RDF_LIBRARIES RDF_INCLUDE_DIRS)

