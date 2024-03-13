# generated from rosidl_generator_py/resource/_idl.py.em
# with input from sdv_msgs:msg/ThrustControl.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ThrustControl(type):
    """Metaclass of message 'ThrustControl'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('sdv_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'sdv_msgs.msg.ThrustControl')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__thrust_control
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__thrust_control
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__thrust_control
            cls._TYPE_SUPPORT = module.type_support_msg__msg__thrust_control
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__thrust_control

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ThrustControl(metaclass=Metaclass_ThrustControl):
    """Message class 'ThrustControl'."""

    __slots__ = [
        '_tau_x',
        '_tau_y',
        '_tau_z',
        '_tau_phi',
        '_tau_theta',
        '_tau_psi',
    ]

    _fields_and_field_types = {
        'tau_x': 'float',
        'tau_y': 'float',
        'tau_z': 'float',
        'tau_phi': 'float',
        'tau_theta': 'float',
        'tau_psi': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.tau_x = kwargs.get('tau_x', float())
        self.tau_y = kwargs.get('tau_y', float())
        self.tau_z = kwargs.get('tau_z', float())
        self.tau_phi = kwargs.get('tau_phi', float())
        self.tau_theta = kwargs.get('tau_theta', float())
        self.tau_psi = kwargs.get('tau_psi', float())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.tau_x != other.tau_x:
            return False
        if self.tau_y != other.tau_y:
            return False
        if self.tau_z != other.tau_z:
            return False
        if self.tau_phi != other.tau_phi:
            return False
        if self.tau_theta != other.tau_theta:
            return False
        if self.tau_psi != other.tau_psi:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def tau_x(self):
        """Message field 'tau_x'."""
        return self._tau_x

    @tau_x.setter
    def tau_x(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'tau_x' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'tau_x' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._tau_x = value

    @builtins.property
    def tau_y(self):
        """Message field 'tau_y'."""
        return self._tau_y

    @tau_y.setter
    def tau_y(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'tau_y' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'tau_y' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._tau_y = value

    @builtins.property
    def tau_z(self):
        """Message field 'tau_z'."""
        return self._tau_z

    @tau_z.setter
    def tau_z(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'tau_z' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'tau_z' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._tau_z = value

    @builtins.property
    def tau_phi(self):
        """Message field 'tau_phi'."""
        return self._tau_phi

    @tau_phi.setter
    def tau_phi(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'tau_phi' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'tau_phi' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._tau_phi = value

    @builtins.property
    def tau_theta(self):
        """Message field 'tau_theta'."""
        return self._tau_theta

    @tau_theta.setter
    def tau_theta(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'tau_theta' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'tau_theta' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._tau_theta = value

    @builtins.property
    def tau_psi(self):
        """Message field 'tau_psi'."""
        return self._tau_psi

    @tau_psi.setter
    def tau_psi(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'tau_psi' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'tau_psi' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._tau_psi = value
