# Initialize ######################################################################################

Include                     ( cotire OPTIONAL )
Include                     ( pedantic OPTIONAL )
Include                     ( strip_symbols OPTIONAL )

Include                     ( ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/options.cmake )

Set                         ( BUILD_SHARED_LIBS ${CPPMARIADB_BUILD_SHARED} )
Set                         ( CMAKE_CXX_STANDARD 17 )
Set                         ( CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   ${PEDANTIC_C_FLAGS}" )
Set                         ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PEDANTIC_CXX_FLAGS}" )

# Dependencies ####################################################################################

Find_Package                ( cpputils REQUIRED )
Find_Package                ( mariadb REQUIRED )

# Project: cppmariadb #############################################################################

# Build
Project                     ( cppmariadb VERSION 1.0.0.0 LANGUAGES CXX )
Set                         ( CPPMARIADB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../include )
File                        ( GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp )
Add_Library                 ( cppmariadb ${SOURCE_FILES} )
Target_Include_Directories  ( cppmariadb
                              PUBLIC ${CPPMARIADB_INCLUDE_DIR} )
Target_Link_Libraries       ( cppmariadb
                              cpputils
                              mariadb )

# Install
If                          ( BUILD_SHARED_LIBS OR CPPMARIADB_INSTALL_DEV_FILES )
    Install                     ( TARGETS cppmariadb DESTINATION lib )
EndIf                       ( )

If                          ( CPPMARIADB_INSTALL_DEV_FILES )
    Install                     ( FILES ${CPPMARIADB_INCLUDE_DIR}/cppmariadb.h DESTINATION include )
    Install                     ( DIRECTORY ${CPPMARIADB_INCLUDE_DIR}/cppmariadb DESTINATION include )
EndIf                       ( )

# Optimize
If                          ( __COTIRE_INCLUDED )
    Cotire                      ( cppmariadb )
EndIf                       ( )
If                          ( __STRIP_SYMBOLS_INCLUDED AND BUILD_SHARED_LIBS )
    Strip_Symbols               ( cppmariadb DBG_FILE )
EndIf                       ()