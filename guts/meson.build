sub_dir_name = meson.current_source_dir().split('/').get(-1)
LD += {
    'name' :sub_dir_name,
    'sources' : files([
                          'gutilities.cc',
                          'gutsConventions.cc'
                      ]),
    'headers' : files([
                          'gutilities.h',
                          'gutsConventions.h'
                      ]),
    'dependencies' : [dependency('clhep', version : '>=2.4.7.1', required : true)],
    'include_directories' : [],
    'examples' : {
        'string_vector_from_string' : [files(['examples/string_vector_from_string.cc']), ['akasha enkil marius']]
    }
}





#
## examples sources and arguments
#examples = {
#    'string_vector_from_string' : [files(['examples/string_vector_from_string.cc']), ['akasha enkil marius']]
#}
#
#
#
#
#
#
#
## examples compilation  and tests
