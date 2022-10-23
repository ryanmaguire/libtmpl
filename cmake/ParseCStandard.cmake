include(CMakePrintHelpers)

function(set_c_standard)
    set(prefix ARG)
    set(noValues "")
    set(singleValues TARGET STDVER ENABLE_VERBOSE)
    set(multiValues "")
    # parse function inputs
    cmake_parse_arguments(
        ${prefix}
        "${noValues}"
        "${singleValues}"
        "${multiValues}"
        ${ARGN}
    )

    if(${ARG_ENABLE_VERBOSE})
        message(
            STATUS
            "\n In set_c_standard():\n   TARGET: ${ARG_TARGET}\n   STDVER: ${ARG_STDVER}"
        )
    endif()
    # Parse STDVER
    # Strip off the "-std=" flag and leading/trailing whitespace
    string(STRIP "${ARG_STDVER}" C_STANDARD_CHOICE)
    string(
        REGEX REPLACE
        "-std[ \t\r\n]*=[ \t\r\n]*"
        ""
        C_STANDARD_CHOICE
        ${C_STANDARD_CHOICE}
    )
    string(STRIP "${C_STANDARD_CHOICE}" C_STANDARD_CHOICE)
    string(TOLOWER "${C_STANDARD_CHOICE}" C_STANDARD_CHOICE)

    set(C90_FLAGS "c90;c89;iso9899:1990")
    set(C99_FLAGS "c99;iso9899:1999;c9x;iso9899:199x")
    set(C11_FLAGS "c11;c1x;iso9899:2011")
    set(C17_FLAGS "c17;c18;iso9899:2017;iso9899:2018")
    set(C23_FLAGS "c2x;c23")

    if(C_STANDARD_CHOICE IN_LIST C90_FLAGS)
        set_property(TARGET ${ARG_TARGET} PROPERTY C_STANDARD 90)
    elseif(C_STANDARD_CHOICE IN_LIST C99_FLAGS)
        set_property(TARGET ${ARG_TARGET} PROPERTY C_STANDARD 99)
    elseif(C_STANDARD_CHOICE IN_LIST C11_FLAGS)
        set_property(TARGET ${ARG_TARGET} PROPERTY C_STANDARD 11)
    elseif(C_STANDARD_CHOICE IN_LIST C17_FLAGS)
        set_property(TARGET ${ARG_TARGET} PROPERTY C_STANDARD 17)
    elseif(C_STANDARD_CHOICE IN_LIST C23_FLAGS)
        set_property(TARGET ${ARG_TARGET} PROPERTY C_STANDARD 23)
    else()
        message(
            WARNING
            "Unrecognized STDVER value: \"${ARG_STDVER}\". Defaulting to c90"
        )
        set_property(TARGET ${ARG_TARGET} PROPERTY C_STANDARD 90)
    endif()
    if(${ARG_ENABLE_VERBOSE})
        cmake_print_properties(
            TARGETS ${ARG_TARGET}
            PROPERTIES C_STANDARD C_EXTENSION
        )
    endif()
endfunction()
