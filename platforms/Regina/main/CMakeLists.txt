file(GLOB_RECURSE APP_LAYER_SRCS
    ../../../app/*.c
    ../../../app/*.cc
    ../../../app/*.cpp
)

set(APP_LAYER_INCS
    ../../../app
)

file(GLOB_RECURSE MY_HAL_SRCS
    ./hal/*.c
    ./hal/*.cc
    ./hal/*.cpp
)

idf_component_register(
    SRCS
    ${APP_LAYER_SRCS}
    ${MY_HAL_SRCS}
    # "main.c"
    "app_main.cpp"
    # "main_hello_world.cpp"
    # "main_hw_cdc_hello_world.cpp"
    # "main_GetChipID.cpp"

    INCLUDE_DIRS
    "."
    ${APP_LAYER_INCS}
)
