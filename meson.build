project(
    'ccom',
    'cpp',
    default_options: ['cpp_std=c++17'],
)

sources = [
    'src/main.cpp',
    'src/draw_manager.cpp',
    'src/draw_loop_manager.cpp',
    'src/geometry.cpp',
]

includes = [
    'include/',
]

dependencies = [
    dependency('threads'),
]

executable(
    'main',
    sources,
    include_directories: include_directories(includes),
    dependencies: dependencies,
)
