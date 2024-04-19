sub_dir_name = meson.current_source_dir().split('/').get(-1)
LD += {
    'name' : sub_dir_name,
    'sources' : files([
                          'goption.cc',
                          'goptions.cc'
                      ]),
    'headers' : files([
                          'json.hpp',
                          'goptions.h',
                          'goptionsConventions.h'
                      ]),
    'dependencies' : [],
    'plugins' : {},
    'examples' : {
        'basic_option' : [files(['examples/simple.cc']), [meson.current_source_dir() + '/examples/simple.jcard']],
        'structured' : [files(['examples/structured.cc']), [meson.current_source_dir() + '/examples/structured.jcard']]
    }
}
