project('textProgressBar', 'cpp',
        default_options : ['cpp_std=c++20'],
        version : run_command('git', 'describe', '--tags', '--abbrev=0', check : true).stdout().strip()
)
project_description = 'Text Progress Bar Library'

lib_sources = files([
                        'textProgressBar.cc'
                    ])
lib_headers = files([
                        'textProgressBar.h',
                        'textProgressBarConventions.h'
                    ])

# compile the source files to a library
this_library = static_library(meson.project_name(), lib_sources, install : true)
install_headers(lib_headers)

# declare goptions dependencies
textProgressBar_dep = declare_dependency(
    link_with : this_library
)

# examples sources and arguments
examples = {
    'bar' : [files(['examples/bar.cc']), ['']]
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
    version : meson.project_version(),
    libraries : this_library,
)
