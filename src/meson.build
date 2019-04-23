
dl_dep = meson.get_compiler('cpp').find_library('dl', required : true)

mainlib = shared_library('mainlib',
    [
        'TestHarness.cpp',
        'Utils.cpp',
        'CppExecution.cpp',
    ],
    include_directories: inc,
    cpp_args : [
        '-Wl,--export-dynamic'
    ],
    dependencies: [
        dl_dep
    ])

executable('prog',
    [
        'main.cpp'
    ],
    include_directories: inc,
    link_with: [
        mainlib
    ])    

