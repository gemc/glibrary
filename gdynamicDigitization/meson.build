sub_dir_name = meson.current_source_dir().split('/').get(-1)
LD += {
    'name' : sub_dir_name,
    'sources' : files([
                          'gdynamicdigitization.cc',
                          'gFluxDigitization.cc',
                          'gParticleCounterDigitization.cc',
                          'gDosimeterDigitization.cc',

                      ]),
    'headers' : files([
                          'ginternalDigitization.h',
                          'greadoutSpecs.h'
                      ]),
    'dependencies' : [dependency('Geant4', version : '>=11.2.0', modules : ['Geant4::G4digits_hits'], required : true)],
    'plugins' : {
        'CTofRoutineExample' : [files(['examples/ctofRoutinesExample.cc']), false],
    },
    'examples' : {
        'plugin_load_example' : [files(['examples/plugin_load_example.cc']), ['']]
    }
}
