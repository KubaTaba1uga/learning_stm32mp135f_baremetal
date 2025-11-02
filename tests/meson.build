project('tests', 'c',
  default_options : [
    'b_pie=false',
    'default_library=static',
  ],
)

tests = [
  # {'src': 'test_rcc'},
  # {'src': 'test_uart'},
    {'src': 'test_str'},
    {'src': 'test_tim'},
    {'src': 'test_console_app', 'includes': ['../examples/console_app', '../examples/console_app/cmd'], 'files': ['../examples/console_app/cli.c']},    
]

unity_subproject = subproject('unity')

unity_dependency = unity_subproject.get_variable('unity_dep')

test_runner = unity_subproject.get_variable('gen_test_runner')

foreach test : tests
  name = test['src']
  
  include = [include_directories('../shared')]
  if test.has_key('includes')
     include += include_directories(test.get('includes'))
  endif

  src_files = [name + '.c', test_runner.process(name + '.c')]
  if test.has_key('files')
     src_files += test.get('files')
  endif

  exe = executable(name,
    sources: src_files,
    dependencies: unity_dependency,
    include_directories: include,
  )

  test(name, exe)
endforeach
