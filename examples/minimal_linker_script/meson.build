project('minimal-linker-script', 'c',
  default_options : [
    'b_pie=false',
    'default_library=static',
  ],
)

src = files('startup.S', 'main.c')

ldscript = join_paths(meson.current_source_dir(), 'script.ld')

executable('minimal_linker_script', src,
  link_args : [
    '-Wl,-T' + ldscript,
    '-lgcc',    
  ],
  install : false
)
