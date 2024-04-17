project('eventDispenser', 'cpp',
        default_options : ['cpp_std=c++20'],
        version : run_command('git', 'describe', '--tags', '--abbrev=0', check : true).stdout().strip()
)
project_description = 'Dispatches events to geant4, using buffering when necessary '

lib_sources = files([
                        'eventDispenser.cc',
                        'eventDispenserOptions.cc'
                    ])
lib_headers = files([
                        'eventDispenser.h',
                        'eventDispenserOptions.h',
                        'eventDispenserConventions.h'
                    ])

# dependencies. assuming PKG_CONFIG_PATH is set to the directory containing the .pc files
#clhep_dep = dependency('clhep', version : '>=2.4.7.1', required : true)
guts = dependency('guts')

geant4_dep = dependency('Geant4', version : '>=11.2.0', required : true, modules : ['Geant4::G4digits_hits'])

incs = include_directories([ '../gdynamicDigitization', '../ghit', ,
                            '../gtouchable', '../gdata', '../gtranslationTable', '../textProgressBar'])

# compile the source files to a shared library
eventDispenser_lib = static_library(meson.project_name(), lib_sources, install : true, include_directories : incs, dependencies : [geant4_dep])
install_headers(lib_headers)

# declare guts dependencies
eventDispenser_dep = declare_dependency(
    link_with : eventDispenser_lib
)

# examples sources and arguments
examples = {
    'simple' : [files(['examples/simple.cc']), [meson.current_source_dir() + '100']],
}







# examples compilation  and tests
foreach name, sources_and_arguments : examples
    exe = executable(name, sources_and_arguments[0], link_with : eventDispenser_lib, install : true, include_directories : incs, dependencies : [geant4_dep, guts])
    test(name + 'test', exe, args : sources_and_arguments[1])
endforeach


# generate pkg-config file
pkg = import('pkgconfig')
pkg.generate(
    name : meson.project_name(),
    description : project_description,
    # requires : [clhep_dep], # pkg-config dependencies only
    version : meson.project_version(),
    libraries : eventDispenser_lib,
)
