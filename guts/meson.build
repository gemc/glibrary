project('guts', 'cpp',
        default_options : ['cpp_std=c++20'],
        version : run_command('git', 'describe', '--tags', '--abbrev=0', check : true).stdout().strip()
)
project_description = 'Various c++ conventions and string utilities'


lib_sources = files([
                        'gutilities.cc',
                        'gutsConventions.cc'
                    ])
lib_headers = files([
                        'gutilities.h',
                        'gutsConventions.h'
                    ])
#guts_dep = declare_dependency(
#    sources : lib_sources
#)

# dependencies. assuming PKG_CONFIG_PATH is set to the directory containing the .pc files
clhep = dependency('clhep', version : '>=2.4.7.1', required : true)


# compile the source files to a shared library
lib = static_library(meson.project_name(), lib_sources, install : true, dependencies : clhep)
install_headers(lib_headers)

# examples and tests
examples = {
    'string_vector_from_string': [files(['examples/string_vector_from_string.cc']), ['akasha enkil marius']]
}

foreach name, sources_and_arguments : examples
    exe = executable(name, sources_and_arguments[0], link_with : lib, install : true)
    test(name + 'test', exe, args : sources_and_arguments[1])
endforeach


# generate pkg-config file
pkg = import('pkgconfig')
pkg.generate(
    name : meson.project_name(),
    description : project_description,
    requires : [clhep], # pkg-config dependencies only
    version : meson.project_version(),
    libraries : lib,
)
