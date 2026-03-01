# generated from rosidl_generator_py/resource/_idl.py.em
# with input from sdv_msgs:msg/GuidanceWaypoints.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'waypoint_list_x'
# Member 'waypoint_list_y'
# Member 'waypoint_list_z'
import array  # noqa: E402, I100

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_GuidanceWaypoints(type):
    """Metaclass of message 'GuidanceWaypoints'."""

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
                'sdv_msgs.msg.GuidanceWaypoints')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__guidance_waypoints
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__guidance_waypoints
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__guidance_waypoints
            cls._TYPE_SUPPORT = module.type_support_msg__msg__guidance_waypoints
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__guidance_waypoints

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GuidanceWaypoints(metaclass=Metaclass_GuidanceWaypoints):
    """Message class 'GuidanceWaypoints'."""

    __slots__ = [
        '_guidance_law',
        '_waypoint_list_length',
        '_waypoint_list_x',
        '_waypoint_list_y',
        '_waypoint_list_z',
        '_depth_setpoint',
        '_heading_setpoint',
    ]

    _fields_and_field_types = {
        'guidance_law': 'uint8',
        'waypoint_list_length': 'uint8',
        'waypoint_list_x': 'sequence<float>',
        'waypoint_list_y': 'sequence<float>',
        'waypoint_list_z': 'sequence<float>',
        'depth_setpoint': 'float',
        'heading_setpoint': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.guidance_law = kwargs.get('guidance_law', int())
        self.waypoint_list_length = kwargs.get('waypoint_list_length', int())
        self.waypoint_list_x = array.array('f', kwargs.get('waypoint_list_x', []))
        self.waypoint_list_y = array.array('f', kwargs.get('waypoint_list_y', []))
        self.waypoint_list_z = array.array('f', kwargs.get('waypoint_list_z', []))
        self.depth_setpoint = kwargs.get('depth_setpoint', float())
        self.heading_setpoint = kwargs.get('heading_setpoint', float())

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
        if self.guidance_law != other.guidance_law:
            return False
        if self.waypoint_list_length != other.waypoint_list_length:
            return False
        if self.waypoint_list_x != other.waypoint_list_x:
            return False
        if self.waypoint_list_y != other.waypoint_list_y:
            return False
        if self.waypoint_list_z != other.waypoint_list_z:
            return False
        if self.depth_setpoint != other.depth_setpoint:
            return False
        if self.heading_setpoint != other.heading_setpoint:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def guidance_law(self):
        """Message field 'guidance_law'."""
        return self._guidance_law

    @guidance_law.setter
    def guidance_law(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'guidance_law' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'guidance_law' field must be an unsigned integer in [0, 255]"
        self._guidance_law = value

    @builtins.property
    def waypoint_list_length(self):
        """Message field 'waypoint_list_length'."""
        return self._waypoint_list_length

    @waypoint_list_length.setter
    def waypoint_list_length(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'waypoint_list_length' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'waypoint_list_length' field must be an unsigned integer in [0, 255]"
        self._waypoint_list_length = value

    @builtins.property
    def waypoint_list_x(self):
        """Message field 'waypoint_list_x'."""
        return self._waypoint_list_x

    @waypoint_list_x.setter
    def waypoint_list_x(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'waypoint_list_x' array.array() must have the type code of 'f'"
            self._waypoint_list_x = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'waypoint_list_x' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._waypoint_list_x = array.array('f', value)

    @builtins.property
    def waypoint_list_y(self):
        """Message field 'waypoint_list_y'."""
        return self._waypoint_list_y

    @waypoint_list_y.setter
    def waypoint_list_y(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'waypoint_list_y' array.array() must have the type code of 'f'"
            self._waypoint_list_y = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'waypoint_list_y' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._waypoint_list_y = array.array('f', value)

    @builtins.property
    def waypoint_list_z(self):
        """Message field 'waypoint_list_z'."""
        return self._waypoint_list_z

    @waypoint_list_z.setter
    def waypoint_list_z(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'waypoint_list_z' array.array() must have the type code of 'f'"
            self._waypoint_list_z = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'waypoint_list_z' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._waypoint_list_z = array.array('f', value)

    @builtins.property
    def depth_setpoint(self):
        """Message field 'depth_setpoint'."""
        return self._depth_setpoint

    @depth_setpoint.setter
    def depth_setpoint(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'depth_setpoint' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'depth_setpoint' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._depth_setpoint = value

    @builtins.property
    def heading_setpoint(self):
        """Message field 'heading_setpoint'."""
        return self._heading_setpoint

    @heading_setpoint.setter
    def heading_setpoint(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'heading_setpoint' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'heading_setpoint' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._heading_setpoint = value
