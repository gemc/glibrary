project('glibrary', 'cpp',
        default_options : ['cpp_std=c++20'],
        version : run_command('git', 'describe', '--tags', '--abbrev=0', check : true).stdout().strip()
)
project_description = 'Various C++ libraries'



# Library Description is an array (mutable) of dictionaries (immutable)
LD = []
all_dependencies = []

subdir('guts')

foreach L : LD
    this_library = static_library(
        L['name'],
        L['sources'],
        dependencies : L['dependencies'],
        install : true,
        include_directories : L['include_directories'],
    )
    install_headers(L['headers'])
    foreach name, sources_and_arguments : L['examples']
        exe = executable(
            name,
            sources_and_arguments[0],
            link_with : this_library,
            install : true,
            include_directories : L['include_directories'] + L['name'],
        )
        test(L['name'] + ' test >  ' + name,
             exe,
             args : sources_and_arguments[1])
    endforeach

endforeach








## generate pkg-config file
#pkg = import('pkgconfig')
#pkg.generate(
#        name : meson.project_name(),
#        description : project_description,
#        requires : this_library_depends_on, # pkg-config dependencies only
#        version : meson.project_version(),
#        libraries : this_library,
#)
