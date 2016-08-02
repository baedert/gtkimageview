project('gtkimageview', 'c')

gtkdep = dependency('gtk+-3.0')

extra_libs  = ['-lm']

lib = library('gtkimageview',
              ['gtkimageview.c'],
               include_dirs: include_directories('.'),
               dependencies: [gtkdep],
               link_args : extra_libs)


demo = executable('demo',
          sources : ['demo.c'],
          link_with: lib,
          dependencies : [gtkdep]
          )


