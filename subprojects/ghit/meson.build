project('ghit', 'cpp',
        default_options : ['cpp_std=c++20'],
        version : run_command('git', 'describe', '--tags', '--abbrev=0', check : true).stdout().strip()
)
project_description = 'GHit Library'

lib_sources = files([
                        'ghit.cc',
                        'calculations.cc',
                        'addHitInfos.cc'
                    ])
lib_headers = files([
                        'ghit.h',
                        'ghitConventions.h'
                    ])

# dependencies. assuming PKG_CONFIG_PATH is set to the directory containing the .pc files
this_library_depends_on = [dependency('Geant4', version : '>=11.2.0', required : true, modules : ['Geant4::G4digits_hits']),
                           dependency('gtouchable')]

# compile the source files to a library
this_library = static_library(meson.project_name(), lib_sources, install : true, dependencies : this_library_depends_on)
install_headers(lib_headers)

# declare goptions dependencies
ghit_dep = declare_dependency(
    link_with : this_library,
    dependencies : this_library_depends_on
)

# examples sources and arguments
examples = {
    'simple' : [files(['examples/simple.cc']), ['']]
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
    # requires : this_library_depends_on, # pkg-config dependencies only
    # looks like it does find Geant4 cmake but the pc is not there yet
    version : meson.project_version(),
    libraries : this_library,
)
