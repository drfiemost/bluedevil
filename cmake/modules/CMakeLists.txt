# install the cmake files

set(cmakeFiles PkgConfigGetVar.cmake)

set(module_install_dir ${DATA_INSTALL_DIR}/cmake/modules )

install( FILES  ${cmakeFiles} DESTINATION ${module_install_dir} )

