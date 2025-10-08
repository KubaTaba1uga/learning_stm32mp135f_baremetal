project('linker-script', 'c',
  default_options : [
    'b_pie=false',
    'default_library=static',
  ],
)

src = files('main.c')

executable('linker_script', src,
  link_args : [
    '-Wl,--script=../../examples/linker_script/linker.ld',
    '-lgcc',    
  ],
  install : false
)
