project('glibrary', 'cpp',
        default_options : ['cpp_std=c++20'],
        version : run_command('git', 'describe', '--tags', '--abbrev=0', check : true).stdout().strip()
)
project_description = 'Various C++ libraries'



# Library Description is an array (mutable) of dictionaries (immutable)
# each subdir adds its own name to the include directories and libraries
LD = []
all_libs = []
all_deps = []
all_includes = []

subdir('guts')
subdir('goptions')
subdir('gfactory')
subdir('textProgressBar')
subdir('gtouchable')
subdir('ghit')


# compilation loop
foreach L : LD
    this_deps = L['dependencies']
    this_lib_name = L['name']
    sources = L['sources']

    if sources.length() > 0
        this_library = static_library(
            this_lib_name,
            sources,
            install : true,
            dependencies : this_deps,
            include_directories : all_includes,
        )
        all_libs += this_library
        all_deps += this_deps

    endif

    # header files
    install_headers(L['headers'])

    # plugins
    foreach name, sources : L['plugins']
        shared_library(
            name,
            sources[0],
            install : sources[1],
            include_directories : all_includes + this_lib_name,
            link_with : all_libs + this_library,
            name_suffix : 'gplugin',
            name_prefix : ''
        )
    endforeach

    # examples
    foreach name, sources_and_arguments : L['examples']
        exe = executable(
            name,
            sources_and_arguments[0],
            install : true,
            dependencies : this_deps,
            include_directories : all_includes + this_lib_name,
            link_with : all_libs + this_library
        )
        test(' ## ' + this_lib_name + ' test ##  >>  ' + name,
             exe,
             args : sources_and_arguments[1])
    endforeach

    all_includes +=  this_lib_name
endforeach








# generate pkg-config file
pkg = import('pkgconfig')
pkg.generate(
    name : meson.project_name(),
    description : project_description,
    #requires : all_deps, # pkg-config dependencies only
    version : meson.project_version(),
    libraries : all_libs
)
