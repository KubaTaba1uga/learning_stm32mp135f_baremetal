project('baremetal-uart', 'c',
  default_options : [
    'b_pie=false',
    'default_library=static',
  ],
)

# Your single-file “firmware”
src = files('org.c')

executable('example.bin', src,
  # Bare-metal entry + placement; use a real linker script if you have one
  link_args : [
    '-Wl,-e,_start',
    '-Wl,-Ttext=0xC0000000',
    '-Wl,--build-id=none',
    '-lgcc',
  ],
  install : false
)
