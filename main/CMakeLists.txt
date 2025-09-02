add_executable(main)

target_sources(main PRIVATE 
    main.c
    hooks.c
    syscalls.c
    callbacks.c
    sysmem.c
)

target_link_libraries(main PRIVATE
    stm32cubemx
    drv8825
    as5600
    ina226
    step_motor
    pid_regulator
    motor_driver
)

target_compile_options(main PUBLIC
    -std=c23
    -Wall
    -Wextra
    -Wconversion
    -Wshadow
    -Wpedantic
    -Wnarrowing
    -Waddress
    -pedantic
    -Wdeprecated
    -Wsign-conversion
    -Wduplicated-cond
    -Wduplicated-branches
    -Wlogical-op
    -Wnull-dereference
    -Wdouble-promotion
    -Wimplicit-fallthrough
    -Wcast-align
    -Wformat=2
    -Wformat-security
    -Wmissing-prototypes
    -Wmissing-declarations
    -Wstrict-prototypes
    -Wold-style-definition
    -Wundef
    -Wvla
    -Wpointer-arith
    -Wstrict-aliasing=2
)
