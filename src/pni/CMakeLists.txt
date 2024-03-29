set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/column_info.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/data_reader.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/deprecation_warning.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/image_channel_info.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/image_info.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/image_reader.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/spreadsheet_reader.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/strutils.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/exceptions.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/parsers.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/formatters.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/container_io_config.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/windows.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/nexus.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/types.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/error.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/utilities.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/arrays.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/algorithms.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/type_erasures.hpp
                 # ${CMAKE_CURRENT_SOURCE_DIR}/configuration.hpp
                 )

set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/column_info.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/data_reader.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/image_info.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/image_reader.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/spreadsheet_reader.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/exceptions.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/container_io_config.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/strutils.cpp)
                 
# ============================================================================
# setting up the global lists for source and header files
# ============================================================================                
set(PNINEXUS_HEADER_FILES )
set(PNINEXUS_SOURCE_FILES )
                 
# ============================================================================
# install header files
# ============================================================================                
install(FILES ${HEADER_FILES}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni)


add_subdirectory("cbf")
add_subdirectory("fio")
add_subdirectory("parsers")
add_subdirectory("formatters")
add_subdirectory("tiff")
add_subdirectory("nexus")
add_subdirectory("types")
add_subdirectory("error")
add_subdirectory("utilities")
add_subdirectory("arrays")
add_subdirectory("algorithms")
add_subdirectory("type_erasures")
# add_subdirectory("configuration")

# ============================================================================
# assemble list of header and source files used in the build 
# ============================================================================

set(PNINEXUS_HEADER_FILES ${PNINEXUS_HEADER_FILES} ${HEADER_FILES})
set(PNINEXUS_SOURCE_FILES ${PNINEXUS_SOURCE_FILES} ${SOURCE_FILES})

# ============================================================================
# adding header files to the doxygen build dependencies
# ============================================================================
if(PNINEXUS_BUILD_DOC)
  add_doxygen_source_deps(${PNINEXUS_HEADER_FILES})
endif()

# ============================================================================
# building the library
# ============================================================================ 
foreach(SRC ${PNINEXUS_SOURCE_FILES})
    message(INFO ${SRC})
endforeach()

foreach(HSRC ${PNINEXUS_HEADER_FILES})
    message(INFO ${HSRC})
endforeach()

add_library(pninexus SHARED ${PNINEXUS_SOURCE_FILES} ${PNINEXUS_HEADER_FILES})

target_include_directories(pninexus
PRIVATE ${PROJECT_SOURCE_DIR}/src
INTERFACE
$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
#add_dependencies(pninexus config.hpp)
set_target_properties(pninexus PROPERTIES VERSION "${LIBRARY_VERSION}"
                                       SOVERSION "${SO_VERSION}")

target_link_libraries(pninexus                      
 PUBLIC h5cpp::h5cpp
 ${HDF5_LIBRARIES}
#  Boost::filesystem
 Boost::regex
 Boost::date_time
 )
target_compile_definitions(pninexus PUBLIC BOOST_ALL_DYN_LINK)
target_compile_definitions(pninexus PRIVATE DLL_BUILD) 

if ((NOT DEFINED HDF5_LIBRARY_DIRS) OR
    (NOT HDF5_LIBRARY_DIRS) OR
    ("${HDF5_LIBRARY_DIRS}" STREQUAL ""))
  list(GET HDF5_LIBRARIES 0 TEMP_HDF5_LIB)
  get_filename_component(HDF5_LIBRARY_DIRS ${TEMP_HDF5_LIB} DIRECTORY)
  unset(TEMP_HDF5_LIB)
endif()

# ============================================================================
# install the library binaries and targets 
# ============================================================================
configure_file(pninexus.pc.cmake pninexus.pc @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/pninexus.pc"
        DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}/pkgconfig")
# 
# export the targets which are latter used by the CMAKE package
# 
install(TARGETS pninexus
        EXPORT pninexus_targets
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        COMPONENT libraries
        )

#
# install the binaries
#
install(EXPORT pninexus_targets
        DESTINATION ${CMAKE_INSTALL_PACKAGEDIR}
        COMPONENT development)
