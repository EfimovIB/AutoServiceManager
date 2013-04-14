QT                          +=  core gui xml sql
CONFIG                      +=  build_all debug_and_release warn_off plugin precompile_header
DEFINES                     +=  ASM_MAKE_DLL

CONFIG( debug, debug|release ) {
    __LIBS_DIR              =   debug
    OBJECTS_DIR             +=  tmp/obj/debug

} else {
    __LIBS_DIR              =   release
    OBJECTS_DIR             +=  tmp/obj/release
}

TEMPLATE                    =   app
DESTDIR                     =   $${__LIBS_DIR}/app
TARGET                      =   asm
MOC_DIR                     +=  tmp/moc
RCC_DIR                     +=  tmp/rcc
UI_DIR                      +=  tmp/uic
DEPENDPATH                  +=  .
VPATH                       +=  ../core
INCLUDEPATH                 +=  .                                    \
								tmp/moc                              \
								tmp/uic
								
LIBS                        +=  -L$${__LIBS_DIR}

#PRECOMPILED_HEADER  = ../../include/ues/stable.h

include(asm.pri)
#include(../../include/leakdetector/leakdetector.pri)