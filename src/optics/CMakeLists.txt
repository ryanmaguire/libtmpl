set(sources
    tmpl_frequency_to_wavelength.c
    tmpl_fresnel_gap.c
    tmpl_left_straightedge_fresnel_diffraction.c
    tmpl_one_slit_fraunhofer_diffraction.c
    tmpl_resolution_inverse.c
    tmpl_right_straightedge_fresnel_diffraction.c
    tmpl_ringlet_fresnel_diffraction.c
    tmpl_ringlet_phase_fresnel_diffraction.c
    tmpl_square_wave_fresnel_diffraction.c
    tmpl_two_slit_fraunhofer_diffraction.c
    tmpl_wavelength_to_wavenumber.c
)

list(REMOVE_ITEM sources ${SOURCE_EXCLUSION_LIST})

target_sources(tmpl PRIVATE ${sources})
