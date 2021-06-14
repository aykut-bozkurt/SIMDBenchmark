function(set_fastest_available_x86archs ARCH_LIST_VAR)

    set(FOUND_ARCH false)
    # avx2 subsets
    set(AVX2_RUNNABLE_ARCHS ${RUNNABLE_ARCHS})
    set(AVX_RUNNABLE_ARCHS ${RUNNABLE_ARCHS})
    set(SSSE3_RUNNABLE_ARCHS ${RUNNABLE_ARCHS})
    set(SSE3_RUNNABLE_ARCHS ${RUNNABLE_ARCHS})
    set(SSE2_RUNNABLE_ARCHS ${RUNNABLE_ARCHS})

    list(FILTER AVX2_RUNNABLE_ARCHS INCLUDE REGEX ".*X86_AVX2.*")
    list(LENGTH AVX2_RUNNABLE_ARCHS AVX2_TOTAL_ARCH)

    list(FILTER AVX_RUNNABLE_ARCHS INCLUDE REGEX ".*X86_AVX.*")
    list(LENGTH AVX_RUNNABLE_ARCHS AVX_TOTAL_ARCH)

    list(FILTER SSSE3_RUNNABLE_ARCHS INCLUDE REGEX ".*X86_SSSE3.*")
    list(LENGTH SSSE3_RUNNABLE_ARCHS SSSE3_TOTAL_ARCH)

    list(FILTER SSE3_RUNNABLE_ARCHS INCLUDE REGEX ".*X86_SSE3.*")
    list(LENGTH SSE3_RUNNABLE_ARCHS SSE3_TOTAL_ARCH)

    list(FILTER SSE2_RUNNABLE_ARCHS INCLUDE REGEX ".*X86_SSE2.*")
    list(LENGTH SSE2_RUNNABLE_ARCHS SSE2_TOTAL_ARCH)

    if(${AVX2_TOTAL_ARCH} GREATER 0)
        message("AVX2 instructions will be used.")
        set(FOUND_ARCH true)
        add_definitions(-DSIMDPP_ARCH_X86_AVX2)
    elseif(${AVX_TOTAL_ARCH} GREATER 0)
        message("AVX instructions will be used.")
        set(FOUND_ARCH true)
        add_definitions(-DSIMDPP_ARCH_X86_AVX)
    elseif(${SSSE3_TOTAL_ARCH} GREATER 0)
        message("SSSE3 instructions will be used.")
        set(FOUND_ARCH true)
        add_definitions(-DSIMDPP_ARCH_X86_SSE3)
    elseif(${SSE3_TOTAL_ARCH} GREATER 0)
        message("SSE3 instructions will be used.")
        set(FOUND_ARCH true)
        add_definitions(-DSIMDPP_ARCH_X86_SSE3)
    elseif(${SSE2_TOTAL_ARCH} GREATER 0)
        message("SSE2 instructions will be used.")
        set(FOUND_ARCH true)
        add_definitions(-DSIMDPP_ARCH_X86_SSE2)
    endif()

    # sse_4.1 subsets
    set(SSE4.1_RUNNABLE_ARCHS ${RUNNABLE_ARCHS})

    list(FILTER SSE4_1_RUNNABLE_ARCHS INCLUDE REGEX ".*X86_SSE4_1.*")
    list(LENGTH SSE4_1_RUNNABLE_ARCHS SSE4_1_TOTAL_ARCH)

    if(${SSE4_1_TOTAL_ARCH} GREATER 0)
        message("SSE_4_1 instructions will be used.")
        set(FOUND_ARCH true)
        add_definitions(-DSIMDPP_ARCH_X86_SSE_4_1)
    endif()

    # fma subsets
    set(FMA3_RUNNABLE_ARCHS ${RUNNABLE_ARCHS})
    set(FMA4_RUNNABLE_ARCHS ${RUNNABLE_ARCHS})

    list(FILTER FMA3_RUNNABLE_ARCHS INCLUDE REGEX ".*X86_FMA3.*")
    list(LENGTH FMA3_RUNNABLE_ARCHS FMA3_TOTAL_ARCH)

    list(FILTER FMA4_RUNNABLE_ARCHS INCLUDE REGEX ".*X86_FMA4.*")
    list(LENGTH FMA4_RUNNABLE_ARCHS FMA4_TOTAL_ARCH)

    if(${FMA4_TOTAL_ARCH} GREATER 0)
        message("FMA4 instructions will be used.")
        set(FOUND_ARCH true)
        add_definitions(-DSIMDPP_ARCH_X86_FMA4)
    elseif(${FMA3_TOTAL_ARCH} GREATER 0)
        message("FMA3 instructions will be used.")
        set(FOUND_ARCH true)
        add_definitions(-DSIMDPP_ARCH_X86_FMA3)
    endif()

    # xop subset
    set(XOP_RUNNABLE_ARCHS ${RUNNABLE_ARCHS})

    list(FILTER XOP_RUNNABLE_ARCHS INCLUDE REGEX ".*X86_XOP.*")
    list(LENGTH XOP_RUNNABLE_ARCHS XOP_TOTAL_ARCH)

    if(${XOP_TOTAL_ARCH} GREATER 0)
        message("XOP instructions will be used.")
        set(FOUND_ARCH true)
        add_definitions(-DSIMDPP_ARCH_X86_XOP)
    endif()

    if(NOT ${FOUND_ARCH})
        message("No instruction set is found.")
    endif()
endfunction()