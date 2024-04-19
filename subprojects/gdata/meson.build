project('gdata', 'cpp',
        default_options : ['cpp_std=c++20'],
        version : run_command('git', 'describe', '--tags', '--abbrev=0', check : true).stdout().strip()
)
project_description = 'GData framework: events and data collections'

lib_sources = files([
                        'event/gDigitizedData.cc',
                        'event/gTrueInfoData.cc',
                        'event/gDataCollection.cc',
                        'event/gEventDataCollectionHeader.cc',
                        'event/gEventDataCollection.cc',
                        'frame/gIntegralPayload.cc',
                        'frame/gFrameDataCollectionHeader.cc',
                        'frame/gFrameDataCollection.cc'
                    ])
lib_headers = files([
                        'gdataConventions.h',
                        'event/gDigitizedData.h',
                        'event/gTrueInfoData.h',
                        'event/gDataCollection.h',
                        'event/gEventDataCollectionHeader.h',
                        'event/gEventDataCollection.h',
                        'frame/gIntegralPayload.h',
                        'frame/gFrameDataCollectionHeader.h',
                        'frame/gFrameDataCollection.h'
                    ])

# dependencies. assuming PKG_CONFIG_PATH is set to the directory containing the .pc files
this_library_depends_on = [dependency('goptions'), dependency('ghit')]

# compile the source files to a library
this_library = static_library(meson.project_name(), lib_sources, install : true, dependencies : this_library_depends_on)
install_headers(lib_headers)

# declare goptions dependencies
gdata_dep = declare_dependency(
    link_with : this_library,
    dependencies : this_library_depends_on
)

# examples sources and arguments
examples = {
    'event_data' : [files(['examples/event_data.cc']), ['']],
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
