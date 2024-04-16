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

# dependencies. assuming PKG_CONFIG_PATH is set to the directory containing the .pc files
this_library_depends_on = [dependency('clhep', version : '>=2.4.7.1', required : true)]

# compile the source files to a library
this_library = static_library(meson.project_name(), lib_sources, install : true, dependencies : this_library_depends_on)
install_headers(lib_headers)

# declare guts dependencies
guts_dep = declare_dependency(
    link_with : this_library,
    dependencies : this_library_depends_on
)

# examples sources and arguments
examples = {
    'string_vector_from_string' : [files(['examples/string_vector_from_string.cc']), ['akasha enkil marius']]
}







# examples compilation  and tests
foreach name, sources_and_arguments : examples
    exe = executable(name, sources_and_arguments[0], link_with : this_library, install : true)
    test(name + 'test', exe, args : sources_and_arguments[1])
endforeach


# generate pkg-config file
pkg = import('pkgconfig')
pkg.generate(
    name : meson.project_name(),
    description : project_description,
    requires : this_library_depends_on, # pkg-config dependencies only
    version : meson.project_version(),
    libraries : this_library,
)
