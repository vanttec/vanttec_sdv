# generated from rosidl_generator_py/resource/_idl.py.em
# with input from sdv_msgs:msg/ThrottleMsg.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ThrottleMsg(type):
    """Metaclass of message 'ThrottleMsg'."""

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
                'sdv_msgs.msg.ThrottleMsg')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__throttle_msg
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__throttle_msg
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__throttle_msg
            cls._TYPE_SUPPORT = module.type_support_msg__msg__throttle_msg
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__throttle_msg

            from std_msgs.msg import Float64
            if Float64.__class__._TYPE_SUPPORT is None:
                Float64.__class__.__import_type_support__()

            from std_msgs.msg import Int16
            if Int16.__class__._TYPE_SUPPORT is None:
                Int16.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ThrottleMsg(metaclass=Metaclass_ThrottleMsg):
    """Message class 'ThrottleMsg'."""

    __slots__ = [
        '_maxvel',
        '_pot',
        '_increase_maxvel',
        '_decrease_maxvel',
        '_car_mode',
        '_pot_mode',
    ]

    _fields_and_field_types = {
        'maxvel': 'std_msgs/Float64',
        'pot': 'std_msgs/Float64',
        'increase_maxvel': 'std_msgs/Int16',
        'decrease_maxvel': 'std_msgs/Int16',
        'car_mode': 'std_msgs/Int16',
        'pot_mode': 'std_msgs/Int16',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Float64'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Float64'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Int16'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Int16'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Int16'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Int16'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Float64
        self.maxvel = kwargs.get('maxvel', Float64())
        from std_msgs.msg import Float64
        self.pot = kwargs.get('pot', Float64())
        from std_msgs.msg import Int16
        self.increase_maxvel = kwargs.get('increase_maxvel', Int16())
        from std_msgs.msg import Int16
        self.decrease_maxvel = kwargs.get('decrease_maxvel', Int16())
        from std_msgs.msg import Int16
        self.car_mode = kwargs.get('car_mode', Int16())
        from std_msgs.msg import Int16
        self.pot_mode = kwargs.get('pot_mode', Int16())

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
        if self.maxvel != other.maxvel:
            return False
        if self.pot != other.pot:
            return False
        if self.increase_maxvel != other.increase_maxvel:
            return False
        if self.decrease_maxvel != other.decrease_maxvel:
            return False
        if self.car_mode != other.car_mode:
            return False
        if self.pot_mode != other.pot_mode:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def maxvel(self):
        """Message field 'maxvel'."""
        return self._maxvel

    @maxvel.setter
    def maxvel(self, value):
        if __debug__:
            from std_msgs.msg import Float64
            assert \
                isinstance(value, Float64), \
                "The 'maxvel' field must be a sub message of type 'Float64'"
        self._maxvel = value

    @builtins.property
    def pot(self):
        """Message field 'pot'."""
        return self._pot

    @pot.setter
    def pot(self, value):
        if __debug__:
            from std_msgs.msg import Float64
            assert \
                isinstance(value, Float64), \
                "The 'pot' field must be a sub message of type 'Float64'"
        self._pot = value

    @builtins.property
    def increase_maxvel(self):
        """Message field 'increase_maxvel'."""
        return self._increase_maxvel

    @increase_maxvel.setter
    def increase_maxvel(self, value):
        if __debug__:
            from std_msgs.msg import Int16
            assert \
                isinstance(value, Int16), \
                "The 'increase_maxvel' field must be a sub message of type 'Int16'"
        self._increase_maxvel = value

    @builtins.property
    def decrease_maxvel(self):
        """Message field 'decrease_maxvel'."""
        return self._decrease_maxvel

    @decrease_maxvel.setter
    def decrease_maxvel(self, value):
        if __debug__:
            from std_msgs.msg import Int16
            assert \
                isinstance(value, Int16), \
                "The 'decrease_maxvel' field must be a sub message of type 'Int16'"
        self._decrease_maxvel = value

    @builtins.property
    def car_mode(self):
        """Message field 'car_mode'."""
        return self._car_mode

    @car_mode.setter
    def car_mode(self, value):
        if __debug__:
            from std_msgs.msg import Int16
            assert \
                isinstance(value, Int16), \
                "The 'car_mode' field must be a sub message of type 'Int16'"
        self._car_mode = value

    @builtins.property
    def pot_mode(self):
        """Message field 'pot_mode'."""
        return self._pot_mode

    @pot_mode.setter
    def pot_mode(self, value):
        if __debug__:
            from std_msgs.msg import Int16
            assert \
                isinstance(value, Int16), \
                "The 'pot_mode' field must be a sub message of type 'Int16'"
        self._pot_mode = value
