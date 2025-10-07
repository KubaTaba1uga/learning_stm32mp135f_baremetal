project('baremetal-uart', 'c',
  default_options : [
    'b_pie=false',
    'default_library=static',
  ],
)

src = files('main.c')

executable('debug_uart', src,
  link_args : [
    '-Wl,-e,_start',
    '-Wl,-Ttext=0xC0000000',
    '-Wl,--build-id=none',
    '-lgcc',
  ],
  install : false
)
