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
moc_sources = []

empty_dict = { 'na' : [''] }
# obtained by not specifying modules
# notice: these give a -I path containing QtWidgets, a binary. So we have to use #include <Headers/QtWidgets> instead of #include <QtWidgets>
geant4 = dependency('Geant4', version : '>=11.2.0',
                    modules : ['Geant4::G4zlib', 'Geant4::G4tools', 'Geant4::G4ptl', 'Geant4::G4analysis', 'Geant4::G4digits_hits', 'Geant4::G4error_propagation', 'Geant4::G4event', 'Geant4::G4geometry', 'Geant4::G4global', 'Geant4::G4graphics_reps', 'Geant4::G4intercoms', 'Geant4::G4interfaces', 'Geant4::G4materials', 'Geant4::G4parmodels', 'Geant4::G4particles', 'Geant4::G4geomtext', 'Geant4::G4mctruth', 'Geant4::G4gdml', 'Geant4::G4physicslists', 'Geant4::G4processes', 'Geant4::G4readout', 'Geant4::G4run', 'Geant4::G4track', 'Geant4::G4tracking', 'Geant4::G4FR', 'Geant4::G4visHepRep', 'Geant4::G4RayTracer', 'Geant4::G4Tree', 'Geant4::G4VRML', 'Geant4::G4GMocren', 'Geant4::G4vis_management', 'Geant4::G4modeling', 'Geant4::G4ToolsSG', 'Geant4::G4OpenGL', 'Geant4::G4visQt3D'],
                    required : true)

#GL = dependency('', required: false)
#darwin = host_machine.system() == 'darwin'
#win32 = host_machine.system() == 'cygwin' or host_machine.system() == 'windows'
#posix = not win32
#if darwin
#    GL = dependency('appleframeworks', modules: 'OpenGL')
##    GL = dependency('appleframeworks', modules: 'OpenGL', required: get_option('gl-cocoa'))
#elif features['win32-desktop']
#    GL = dependency('GL', required: get_option('gl-win32'))
#elif features['x11']
#    GL = dependency('GL', required: get_option('gl-x11'))
#endif

subdir('guts')
subdir('goptions')
#subdir('gfactory')
#subdir('textProgressBar')
#subdir('gtouchable')
#subdir('ghit')
#subdir('gtranslationTable')
#subdir('gdata')
#subdir('gdynamicDigitization')
#subdir('eventDispenser')
subdir('g4display')

# qt: https://mesonbuild.com/Qt5-module.html
qt5 = import('qt5')
qt5_dep = dependency('qt5', modules : ['Core', 'Gui', 'Widgets'])

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
                                       dependencies : qt5_dep)
    endif

    if not sources.contains('')
        this_library = static_library(
            this_lib_name,
            sources + moc_sources,
            install : true,
            dependencies : this_deps + qt5_dep,
            include_directories : all_includes + additional_includes
        )
        all_libs += this_library
        all_deps += this_deps
    endif

    # header files
    install_headers(L['headers'])

    #    # plugins
    if plugins != empty_dict
        foreach name, sources : plugins
            shared_library(
                name,
                sources[0],
                install : sources[1],
                dependencies : this_deps + qt5_dep,
                include_directories : all_includes + this_lib_name,
                link_with : all_libs + this_library,
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
            dependencies : this_deps + qt5_dep,
            include_directories : all_includes + this_lib_name,
            link_with : all_libs + this_library
        )
        test(' ## ' + this_lib_name + ' test ##  >>  ' + name,
             exe,
             args : sources_and_arguments[1])
    endforeach

    all_includes +=  additional_includes
    all_includes += this_lib_name # notice: non commutative!
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
