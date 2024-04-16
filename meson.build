project('glibrary', 'cpp',
        version : run_command('git', 'describe', '--tags', '--abbrev=0', check : true).stdout().strip()
)
project_description = 'Various c++ libraries'



guts     = dependency('guts',     fallback : ['guts',     'guts_dep'])
goptions = dependency('goptions', fallback : ['goptions', 'goptions_dep'])
