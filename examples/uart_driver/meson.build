project('uart-driver', 'c',
  default_options : [
    'b_pie=false',
    'default_library=static',
  ],
)

src = files('main.c')

ldscript = join_paths(meson.current_source_dir(), 'script.ld')

executable('linker_script', src,
  link_args : [
    '-Wl,-T' + ldscript,
    '-lgcc',    
  ],
  install : false
)
