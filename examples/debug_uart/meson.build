project('baremetal-uart', 'c',
  default_options : [
    'b_pie=false',
    'default_library=static',
  ],
)

executable('debug_uart_s', files('main.s'),
  link_args : [
    # '-Wl,-e,_Reset',
    '-Wl,-T../../examples/debug_uart/script.ld',
    '-Wl,--build-id=none',
    '-lgcc',
  ],
  install : false
)

executable('debug_uart_c', files('main.c'),
  link_args : [
    # '-Wl,-e,_Reset',
    '-Wl,-T../../examples/debug_uart/script.ld',
    '-Wl,--build-id=none',
    '-lgcc',
  ],
  install : false
)

