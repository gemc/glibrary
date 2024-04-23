project('glibrary', 'cpp',
        default_options : ['cpp_std=c++20'],
        version : run_command('git', 'describe', '--tags', '--abbrev=0', check : true).stdout().strip()
)
project_description = 'Various C++ libraries'

# dependencies
##############




# qt: https://mesonbuild.com/Qt5-module.html
qt5 = import('qt5')
qt5_deps = dependency('qt5', modules : ['Core', 'Gui', 'Widgets'], required : true)

clhep_deps = dependency('clhep', version : '>=2.4.7.1', required : true)

# geant4 notice: the cmake dependency include clhep and a lot of stuff that is not working
# geant4_deps = dependency('Geant4', version : '>=11.2.0',
#                         modules : ['Geant4::G4zlib', 'Geant4::G4tools', 'Geant4::G4ptl', 'Geant4::G4analysis', 'Geant4::G4digits_hits', 'Geant4::G4error_propagation', 'Geant4::G4event', 'Geant4::G4geometry', 'Geant4::G4global', 'Geant4::G4graphics_reps', 'Geant4::G4intercoms', 'Geant4::G4interfaces', 'Geant4::G4materials', 'Geant4::G4parmodels', 'Geant4::G4particles', 'Geant4::G4geomtext', 'Geant4::G4mctruth', 'Geant4::G4gdml', 'Geant4::G4physicslists', 'Geant4::G4processes', 'Geant4::G4readout', 'Geant4::G4run', 'Geant4::G4track', 'Geant4::G4tracking', 'Geant4::G4FR', 'Geant4::G4visHepRep', 'Geant4::G4RayTracer', 'Geant4::G4Tree', 'Geant4::G4VRML', 'Geant4::G4GMocren', 'Geant4::G4vis_management', 'Geant4::G4modeling', 'Geant4::G4ToolsSG', 'Geant4::G4OpenGL', 'Geant4::G4visQt3D'],
#                         required : true)

# setting things up manually instead
Geant4_inc_dirs = []
Geant4_flags = []
g4_cflags = run_command('geant4-config', '--cflags', check : true).stdout().strip().split()
# keep only the geant4 include directories
foreach cflag : g4_cflags
    if cflag.contains('geant4') or cflag.contains('/OpenGL')
        Geant4_inc_dirs += include_directories(cflag.strip('-I'))
    elif cflag.contains('-D') or cflag.contains('-W')
        Geant4_flags += cflag
    endif
endforeach
Geant4_link_args = run_command('geant4-config', '--libs', check : true).stdout().strip().split()
geant4_deps = declare_dependency(
    include_directories : Geant4_inc_dirs,
    link_args : Geant4_link_args,
    compile_args : Geant4_flags
)



# init lists
############
LD = []
all_libs = []
all_deps = []
all_includes = []
moc_sources = []
empty_dict = { 'na' : [''] }


# Fill dictionary
#################
subdir('guts')
subdir('goptions')
subdir('gfactory')
subdir('textProgressBar')
subdir('gtouchable')
subdir('ghit')
subdir('gtranslationTable')
subdir('gdata')
subdir('gdynamicDigitization')
subdir('eventDispenser')
subdir('g4display')


# compilation loop
foreach L : LD
    this_lib_name = L['name'] # key name must be present

    sources = L.get('sources', [''])
    this_deps = L.get('dependencies', [])
    plugins = L.get('plugins', empty_dict)
    additional_includes = L.get('additional_includes', [''])
    moc_headers = L.get('moc_headers', [''])

    if not moc_headers.contains('')
        moc_sources += qt5.compile_moc(headers : moc_headers,
                                       dependencies : this_deps)
    endif

    if not sources.contains('')
        this_library = static_library(
            this_lib_name,
            sources + moc_sources,
            install : true,
            dependencies : this_deps,
            include_directories : all_includes + additional_includes
        )
        if not all_libs.contains(this_library)
            all_libs += this_library
        endif

        foreach dep : this_deps
            if not all_deps.contains(dep)
                all_deps += dep
            endif
        endforeach
    endif

    # header files
    install_headers(L['headers'])

    #  plugins
    if plugins != empty_dict
        foreach name, sources : plugins
            shared_library(
                name,
                sources[0],
                install : sources[1],
                dependencies : this_deps,
                include_directories : all_includes + this_lib_name,
                link_with : all_libs,
                name_suffix : 'gplugin',
                name_prefix : ''
            )
        endforeach
    endif

    # examples
    foreach name, sources_and_arguments : L['examples']
        exe = executable(
            name,
            sources_and_arguments[0],
            install : true,
            dependencies : this_deps,
            include_directories : all_includes + this_lib_name,
            link_with : all_libs
        )
        test(' ## ' + this_lib_name + ' test ##  >>  ' + name,
             exe,
             args : sources_and_arguments[1])
    endforeach

    foreach include_dir : additional_includes
        if not all_includes.contains(include_dir)
            all_includes += include_dir
        endif
    endforeach
    if not all_includes.contains(this_lib_name)
        all_includes += this_lib_name
    endif
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
