# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "Localization: 1 messages, 0 services")

set(MSG_I_FLAGS "-ILocalization:/home/redbird-general/a_ws/src/localization/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(Localization_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/redbird-general/a_ws/src/localization/msg/Num.msg" NAME_WE)
add_custom_target(_Localization_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "Localization" "/home/redbird-general/a_ws/src/localization/msg/Num.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(Localization
  "/home/redbird-general/a_ws/src/localization/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/Localization
)

### Generating Services

### Generating Module File
_generate_module_cpp(Localization
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/Localization
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(Localization_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(Localization_generate_messages Localization_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/redbird-general/a_ws/src/localization/msg/Num.msg" NAME_WE)
add_dependencies(Localization_generate_messages_cpp _Localization_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(Localization_gencpp)
add_dependencies(Localization_gencpp Localization_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS Localization_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(Localization
  "/home/redbird-general/a_ws/src/localization/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/Localization
)

### Generating Services

### Generating Module File
_generate_module_eus(Localization
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/Localization
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(Localization_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(Localization_generate_messages Localization_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/redbird-general/a_ws/src/localization/msg/Num.msg" NAME_WE)
add_dependencies(Localization_generate_messages_eus _Localization_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(Localization_geneus)
add_dependencies(Localization_geneus Localization_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS Localization_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(Localization
  "/home/redbird-general/a_ws/src/localization/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/Localization
)

### Generating Services

### Generating Module File
_generate_module_lisp(Localization
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/Localization
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(Localization_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(Localization_generate_messages Localization_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/redbird-general/a_ws/src/localization/msg/Num.msg" NAME_WE)
add_dependencies(Localization_generate_messages_lisp _Localization_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(Localization_genlisp)
add_dependencies(Localization_genlisp Localization_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS Localization_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(Localization
  "/home/redbird-general/a_ws/src/localization/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/Localization
)

### Generating Services

### Generating Module File
_generate_module_nodejs(Localization
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/Localization
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(Localization_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(Localization_generate_messages Localization_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/redbird-general/a_ws/src/localization/msg/Num.msg" NAME_WE)
add_dependencies(Localization_generate_messages_nodejs _Localization_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(Localization_gennodejs)
add_dependencies(Localization_gennodejs Localization_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS Localization_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(Localization
  "/home/redbird-general/a_ws/src/localization/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/Localization
)

### Generating Services

### Generating Module File
_generate_module_py(Localization
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/Localization
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(Localization_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(Localization_generate_messages Localization_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/redbird-general/a_ws/src/localization/msg/Num.msg" NAME_WE)
add_dependencies(Localization_generate_messages_py _Localization_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(Localization_genpy)
add_dependencies(Localization_genpy Localization_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS Localization_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/Localization)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/Localization
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(Localization_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/Localization)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/Localization
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(Localization_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/Localization)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/Localization
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(Localization_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/Localization)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/Localization
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(Localization_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/Localization)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/Localization\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/Localization
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(Localization_generate_messages_py std_msgs_generate_messages_py)
endif()
