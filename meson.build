project(
    'ccom',
    'cpp',
    default_options: ['cpp_std=c++17'],
)

sources = [
    'src/main.cpp',
    'src/rasterizer.cpp',
    'src/geometry.cpp',
    'src/compositor.cpp',
    'src/objects/point.cpp',
    'src/objects/rectangle.cpp',
    'src/objects/triangle.cpp',
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
