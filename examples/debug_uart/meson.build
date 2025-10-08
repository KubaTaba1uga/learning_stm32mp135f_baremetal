project('baremetal-uart', 'c',
  default_options : [
    'b_pie=false',
    'default_library=static',
  ],
)

ldscript = join_paths(meson.current_source_dir(), 'script.ld')

executable('debug_uart', files('main.c'),
  link_args : [
    # '-Wl,-e,_Reset',
    '-Wl,-T' + ldscript,
    '-Wl,--build-id=none',
    '-lgcc',
  ],
  install : false
)

