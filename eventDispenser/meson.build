sub_dir_name = meson.current_source_dir().split('/').get(-1)
LD += {
    'name' : sub_dir_name,
    'sources' : files([
                          'eventDispenser.cc',
                          'eventDispenserOptions.cc'
                      ]),
    'headers' : files([
                          'eventDispenser.h',
                          'eventDispenserOptions.h',
                          'eventDispenserConventions.h'
                      ]),
    'dependencies' : [dependency('Geant4', version : '>=11.2.0', modules : ['Geant4::G4digits_hits'], required : true)],
    'examples' : {
        'basic_dispenser' : [files(['examples/simple.cc']), ['']]
    }
}
