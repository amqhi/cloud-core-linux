subdir('core')
subdir('shared-core')
subdir('shared-core-linux')

# Vendored sqlite3.c uses undefined feature macros. Keep it out of
# consumers' -Werror=undef flags.
fs = import('fs')
shared_sources_without_sqlite = []
sqlite_sources = []
foreach src : shared_sources
  if fs.name(src) == 'sqlite3.c'
    sqlite_sources += [src]
  else
    shared_sources_without_sqlite += [src]
  endif
endforeach

# Force-include standard headers to avoid missing-declaration build errors across compilers/libcs
add_project_arguments(
    '-include', 'algorithm',
    '-include', 'cstdint',
    '-include', 'compare',
    '-include', 'functional',
    '-include', 'cstring',
    language: 'cpp',
)

sqlite_dep = declare_dependency(
  link_with: static_library(
    'sqlite3',
    sqlite_sources,
    c_args: ['-w'],
    include_directories: shared_include_dirs,
  ),
)

core_include_dirs = [
    cloud_include_dirs,
    shared_include_dirs,
    shared_linux_include_dirs,
    include_directories('src'),
]

core_gtk_include_dirs = core_include_dirs

core_gtk_sources = cloud_sources + shared_sources_without_sqlite + shared_linux_sources + shared_gtk_sources + files(
    'src/linux_platform_utils.cpp',
    'src/linux_platform_utils.h',
    'src/linux_secure_storage_provider.cpp',
    'src/linux_secure_storage_provider.h',
    'src/gtk_network_provider.cpp',
    'src/gtk_network_provider.h',
)

core_qt_sources = cloud_sources + shared_sources_without_sqlite + shared_linux_sources + shared_qt_sources + files(
    'src/linux_platform_utils.cpp',
    'src/linux_platform_utils.h',
    'src/linux_secure_storage_provider.cpp',
    'src/linux_secure_storage_provider.h',
    'src/qt_network_provider.cpp',
    'src/qt_network_provider.h',
)

core_gtk_deps = [
    sqlite_dep,
    dependency('boost'),
    dependency('openssl'),
    dependency('threads'),
]

host_system = host_machine.system()
if host_system == 'linux'
    core_gtk_deps += dependency('libsecret-1')
endif
