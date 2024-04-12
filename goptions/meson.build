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




# dependencies. assuming PKG_CONFIG_PATH is set to the directory containing the .pc files
guts = dependency('guts', version : '>=1.2', required : true)


# compile the source files to a shared library
lib = static_library(meson.project_name(), lib_sources, install : true, dependencies : guts)
install_headers(lib_headers)
