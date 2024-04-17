project('goptions', 'cpp',
        default_options : ['cpp_std=c++20'],
        version : run_command('git', 'describe', '--tags', '--abbrev=0', check : true).stdout().strip()
)
project_description = 'gfactory framework: dynamically define and load a plugin'

lib_headers = files([
                        'gdl.h',
                        'gfactory.h'
                    ])

# dependencies. assuming PKG_CONFIG_PATH is set to the directory containing the .pc files
this_library_depends_on = [dependency('guts')]

# install headers
install_headers(lib_headers)

# declare goptions dependencies
gfactory_dep = declare_dependency(
    dependencies : this_library_depends_on
)


# dynamic plugins sources and arguments
shared_libs = {
    'fordFactory' : [files(['examples/FordFactory.cc'])],
    'teslaFactory' : [files(['examples/TeslaFactory.cc'])]
}

# shared_libs compilation
foreach name, sources : shared_libs
    this_library = shared_library(name, sources, install : true, dependencies : this_library_depends_on, name_suffix: 'gplugin', name_prefix: '')
endforeach



# examples sources and arguments
examples = {
    'static_and_dynamic_example' : [files(['examples/static_and_dynamic_example.cc', 'examples/ShapeFactory.cc'])]
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
