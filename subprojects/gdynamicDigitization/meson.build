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
this_library_depends_on = [dependency('guts')]

# compile the source files to a library
this_library = static_library(meson.project_name(), lib_sources, install : true, dependencies : this_library_depends_on)
install_headers(lib_headers)

# declare goptions dependencies
goptions_dep = declare_dependency(
    link_with : this_library,
    dependencies : this_library_depends_on
)

# examples sources and arguments
examples = {
    'simple' : [files(['examples/simple.cc']), [meson.current_source_dir() + '/examples/simple.jcard']],
    'structured' : [files(['examples/structured.cc']), [meson.current_source_dir() + '/examples/structured.jcard']]
}






# examples compilation  and tests
foreach name, sources_and_arguments : examples
    exe = executable(name, sources_and_arguments[0], link_with : this_library, install : true, dependencies : this_library_depends_on)
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
