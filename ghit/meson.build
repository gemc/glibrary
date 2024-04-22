sub_dir_name = meson.current_source_dir().split('/').get(-1)
LD += {
    'name' : sub_dir_name,
    'sources' : files([
                          'ghit.cc',
                          'calculations.cc',
                          'addHitInfos.cc'
                      ]),
    'headers' : files([
                          'ghit.h',
                          'ghitConventions.h'
                      ]),
    'dependencies' : [dependency('Geant4', version : '>=11.2.0', modules : ['Geant4::G4digits_hits'], required : true)],
    'plugins' : {},
    'examples' : {
        'basic_hit' : [files(['examples/simple.cc']), ['']]
    }
}
