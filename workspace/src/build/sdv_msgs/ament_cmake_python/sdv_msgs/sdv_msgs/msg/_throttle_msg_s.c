// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from sdv_msgs:msg/ThrottleMsg.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "sdv_msgs/msg/detail/throttle_msg__struct.h"
#include "sdv_msgs/msg/detail/throttle_msg__functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__float64__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__float64__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__float64__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__float64__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__int16__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__int16__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__int16__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__int16__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__int16__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__int16__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__int16__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__int16__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool sdv_msgs__msg__throttle_msg__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[39];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("sdv_msgs.msg._throttle_msg.ThrottleMsg", full_classname_dest, 38) == 0);
  }
  sdv_msgs__msg__ThrottleMsg * ros_message = _ros_message;
  {  // maxvel
    PyObject * field = PyObject_GetAttrString(_pymsg, "maxvel");
    if (!field) {
      return false;
    }
    if (!std_msgs__msg__float64__convert_from_py(field, &ros_message->maxvel)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // pot
    PyObject * field = PyObject_GetAttrString(_pymsg, "pot");
    if (!field) {
      return false;
    }
    if (!std_msgs__msg__float64__convert_from_py(field, &ros_message->pot)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // increase_maxvel
    PyObject * field = PyObject_GetAttrString(_pymsg, "increase_maxvel");
    if (!field) {
      return false;
    }
    if (!std_msgs__msg__int16__convert_from_py(field, &ros_message->increase_maxvel)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // decrease_maxvel
    PyObject * field = PyObject_GetAttrString(_pymsg, "decrease_maxvel");
    if (!field) {
      return false;
    }
    if (!std_msgs__msg__int16__convert_from_py(field, &ros_message->decrease_maxvel)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // car_mode
    PyObject * field = PyObject_GetAttrString(_pymsg, "car_mode");
    if (!field) {
      return false;
    }
    if (!std_msgs__msg__int16__convert_from_py(field, &ros_message->car_mode)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // pot_mode
    PyObject * field = PyObject_GetAttrString(_pymsg, "pot_mode");
    if (!field) {
      return false;
    }
    if (!std_msgs__msg__int16__convert_from_py(field, &ros_message->pot_mode)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * sdv_msgs__msg__throttle_msg__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of ThrottleMsg */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("sdv_msgs.msg._throttle_msg");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "ThrottleMsg");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  sdv_msgs__msg__ThrottleMsg * ros_message = (sdv_msgs__msg__ThrottleMsg *)raw_ros_message;
  {  // maxvel
    PyObject * field = NULL;
    field = std_msgs__msg__float64__convert_to_py(&ros_message->maxvel);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "maxvel", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // pot
    PyObject * field = NULL;
    field = std_msgs__msg__float64__convert_to_py(&ros_message->pot);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "pot", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // increase_maxvel
    PyObject * field = NULL;
    field = std_msgs__msg__int16__convert_to_py(&ros_message->increase_maxvel);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "increase_maxvel", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // decrease_maxvel
    PyObject * field = NULL;
    field = std_msgs__msg__int16__convert_to_py(&ros_message->decrease_maxvel);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "decrease_maxvel", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // car_mode
    PyObject * field = NULL;
    field = std_msgs__msg__int16__convert_to_py(&ros_message->car_mode);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "car_mode", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // pot_mode
    PyObject * field = NULL;
    field = std_msgs__msg__int16__convert_to_py(&ros_message->pot_mode);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "pot_mode", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
