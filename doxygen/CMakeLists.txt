find_package(
        Doxygen
        COMPONENTS dot
)

if (Doxygen_FOUND)
    include(definitions.cmake)

    if (${CMAKE_SYSTEM_NAME} STREQUAL Darwin)
        set(DOXYGEN_CASE_SENSE_NAMES NO)
    endif ()

    doxygen_add_docs(
            doxygen
            ${SRCS}
    )
endif ()
