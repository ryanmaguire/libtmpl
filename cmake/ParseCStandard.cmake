include(CMakePrintHelpers)

function(set_c_standard targetName STDVER)
    # Parse STDVER
    # Strip off the "-std=" flag and leading/trailing whitespace
    string(STRIP "${STDVER}" C_STANDARD_CHOICE)
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
    if(C_STANDARD_CHOICE IN_LIST C90_FLAGS)
        set_property(TARGET ${targetName} PROPERTY C_STANDARD 90)
    elseif(C_STANDARD_CHOICE IN_LIST C99_FLAGS)
        set_property(TARGET ${targetName} PROPERTY C_STANDARD 99)
    elseif(C_STANDARD_CHOICE IN_LIST C11_FLAGS)
        set_property(TARGET ${targetName} PROPERTY C_STANDARD 11)
    elseif(C_STANDARD_CHOICE IN_LIST C17_FLAGS)
        set_property(TARGET ${targetName} PROPERTY C_STANDARD 17)
    else()
        message(
            WARNING
            "Unrecognized STDVER value: ${STDVER}. Defaulting to c90"
        )
        set_property(TARGET tmpl PROPERTY C_STANDARD 90)
    endif()

    cmake_print_properties(
        TARGETS ${targetName}
        PROPERTIES C_STANDARD C_EXTENSION
    )
endfunction()
