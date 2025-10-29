project('uart-poll-rx', 'c',
  default_options : [
    'b_pie=false',
    'default_library=static',
  ],
)

tests = [
  {'src': 'test_rcc'},
  {'src': 'test_uart'},
  {'src': 'test_str'},
  {'src': 'test_tim'},      
]

unity_subproject = subproject('unity')

unity_dependency = unity_subproject.get_variable('unity_dep')

test_runner = unity_subproject.get_variable('gen_test_runner')

foreach test : tests
  name = test['src']

  exe = executable(name,
    sources: [name + '.c', test_runner.process(name + '.c')],
    dependencies: unity_dependency,
    include_directories: include_directories('../shared'),
  )

  test(name, exe)
endforeach
