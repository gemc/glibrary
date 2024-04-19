project('gdynamicDigitization', 'cpp',
        default_options : ['cpp_std=c++20'],
        version : run_command('git', 'describe', '--tags', '--abbrev=0', check : true).stdout().strip()
)
project_description = 'gdynamicDigitization framework'

lib_sources = files([
                        'gdynamicdigitization.cc',
                        'gFluxDigitization.cc',
                        'gParticleCounterDigitization.cc',
                        'gDosimeterDigitization.cc',
                    ])
lib_headers = files([
                        'ginternalDigitization.h',
                        'greadoutSpecs.h'
                    ])

# dependencies. assuming PKG_CONFIG_PATH is set to the directory containing the .pc files
this_library_depends_on = [dependency('ghit'), dependency('gdata'), dependency('gtranslationTable'), dependency('gtouchable')]

# compile the source files to a library
this_library = static_library(meson.project_name(), lib_sources, install : true, dependencies : this_library_depends_on)
install_headers(lib_headers)

# declare goptions dependencies
gdynamicDigitization_dep = declare_dependency(
    link_with : this_library,
    dependencies : this_library_depends_on
)

# dynamic plugins sources and arguments
shared_libs = {
    'ctofRoutinesExample' : [files(['examples/ctofRoutinesExample.cc'])],
}

# shared_libs compilation
foreach name, sources : shared_libs
    this_dlls = shared_library(name, sources, install : false, dependencies : this_library_depends_on, name_suffix: 'gplugin', name_prefix: '', link_with : this_library)
endforeach


# examples sources and arguments
examples = {
    'plugin_load_example' : [files(['examples/plugin_load_example.cc'])]
}

# examples compilation  and tests
foreach name, sources : examples
    exe = executable(name, sources, link_with : this_library, install : true, dependencies : this_library_depends_on)
    test(name + 'test', exe)
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
