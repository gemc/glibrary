project('goptions', 'cpp',
        default_options : ['cpp_std=c++20'],
        version : run_command('git', 'describe', '--tags', '--abbrev=0', check : true).stdout().strip()
)
project_description = 'GOptions framework'

lib_sources = files([
                        'goption.cc',
                        'goptions.cc'
                    ])
lib_headers = files([
                        'goptions.h',
                        'goptionsConventions.h'
                    ])

incs = include_directories('../guts')
guts = dependency('guts')

# compile the source files to a shared library
goptions_lib = static_library(meson.project_name(), lib_sources, install : true, include_directories : incs)
install_headers(lib_headers)

# declare goptions dependencies
goptions_dep = declare_dependency(
    link_with : goptions_lib
)

# examples sources and arguments
examples = {
    'simple' : [files(['examples/simple.cc']), [meson.current_source_dir() + '/examples/simple.jcard']],
    'structured' : [files(['examples/structured.cc']), [meson.current_source_dir() + '/examples/structured.jcard']]
}






# examples compilation  and tests
foreach name, sources_and_arguments : examples
    exe = executable(name, sources_and_arguments[0], link_with : goptions_lib, install : true, dependencies : [guts], include_directories : incs)
    test(name + 'test', exe, args : sources_and_arguments[1])
endforeach


# generate pkg-config file
pkg = import('pkgconfig')
pkg.generate(
    name : meson.project_name(),
    description : project_description,
    requires : 'guts', # pkg-config dependencies only
    version : meson.project_version(),
    libraries : goptions_lib,
)
