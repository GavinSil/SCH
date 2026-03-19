project(CFS_SCH C)

include_directories(fsw/public_inc)
include_directories(fsw/mission_inc)
include_directories(fsw/platform_inc)
include_directories(fsw/src)

# Get all source files from fsw/src, excluding stepping (which is stepping-specific)
file(GLOB APP_SRC_FILES CONFIGURE_DEPENDS fsw/src/*.c)
list(REMOVE_ITEM APP_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/fsw/src/sch_stepping.c")

# When stepping is enabled, include the stepping hook implementation
if (CFE_SIM_STEPPING)
    list(APPEND APP_SRC_FILES fsw/src/sch_stepping.c)
endif()

# Create the app module
add_cfe_app(sch ${APP_SRC_FILES})

# Add tables
add_cfe_tables(sch fsw/tables/sch_def_schtbl.c fsw/tables/sch_def_msgtbl.c)

# When stepping is enabled, expose ESA headers via target include directories
if (CFE_SIM_STEPPING)
    # Use the INTERFACE includes from esa_public_api target
    target_include_directories(sch PRIVATE 
        $<TARGET_PROPERTY:esa_public_api,INTERFACE_INCLUDE_DIRECTORIES>
    )
endif()

# If UT is enabled, then add the tests from the subdirectory
# Note that this is an app, and therefore does not provide
# stub functions, as other entities would not typically make
# direct function calls into this application.
if (ENABLE_UNIT_TESTS AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/unit-test/CMakeLists.txt")
  add_subdirectory(unit-test)
endif ()
