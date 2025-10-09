project('baremetal-uart', 'c',
  default_options : [
    'b_pie=false',
    'default_library=static',
  ],
)

executable('debug_uart', files('main.c'),
  link_args : [
    '-Wl,-e,main',
    '-Wl,--build-id=none',
    '-lgcc',
  ],
  install : false
)

