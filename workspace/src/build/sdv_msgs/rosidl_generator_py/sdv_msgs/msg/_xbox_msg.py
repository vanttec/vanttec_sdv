# generated from rosidl_generator_py/resource/_idl.py.em
# with input from sdv_msgs:msg/XboxMsg.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_XboxMsg(type):
    """Metaclass of message 'XboxMsg'."""

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
                'sdv_msgs.msg.XboxMsg')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__xbox_msg
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__xbox_msg
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__xbox_msg
            cls._TYPE_SUPPORT = module.type_support_msg__msg__xbox_msg
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__xbox_msg

            from std_msgs.msg import Bool
            if Bool.__class__._TYPE_SUPPORT is None:
                Bool.__class__.__import_type_support__()

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


class XboxMsg(metaclass=Metaclass_XboxMsg):
    """Message class 'XboxMsg'."""

    __slots__ = [
        '_connected',
        '_back',
        '_leftx',
        '_lefty',
        '_right_trigger',
        '_a',
        '_b',
        '_x',
        '_y',
        '_dpad_up',
        '_dpad_down',
        '_dpad_left',
        '_dpad_right',
    ]

    _fields_and_field_types = {
        'connected': 'std_msgs/Bool',
        'back': 'std_msgs/Int16',
        'leftx': 'std_msgs/Float64',
        'lefty': 'std_msgs/Float64',
        'right_trigger': 'std_msgs/Float64',
        'a': 'std_msgs/Int16',
        'b': 'std_msgs/Int16',
        'x': 'std_msgs/Int16',
        'y': 'std_msgs/Int16',
        'dpad_up': 'std_msgs/Int16',
        'dpad_down': 'std_msgs/Int16',
        'dpad_left': 'std_msgs/Int16',
        'dpad_right': 'std_msgs/Int16',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Bool'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Int16'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Float64'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Float64'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Float64'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Int16'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Int16'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Int16'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Int16'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Int16'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Int16'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Int16'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Int16'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Bool
        self.connected = kwargs.get('connected', Bool())
        from std_msgs.msg import Int16
        self.back = kwargs.get('back', Int16())
        from std_msgs.msg import Float64
        self.leftx = kwargs.get('leftx', Float64())
        from std_msgs.msg import Float64
        self.lefty = kwargs.get('lefty', Float64())
        from std_msgs.msg import Float64
        self.right_trigger = kwargs.get('right_trigger', Float64())
        from std_msgs.msg import Int16
        self.a = kwargs.get('a', Int16())
        from std_msgs.msg import Int16
        self.b = kwargs.get('b', Int16())
        from std_msgs.msg import Int16
        self.x = kwargs.get('x', Int16())
        from std_msgs.msg import Int16
        self.y = kwargs.get('y', Int16())
        from std_msgs.msg import Int16
        self.dpad_up = kwargs.get('dpad_up', Int16())
        from std_msgs.msg import Int16
        self.dpad_down = kwargs.get('dpad_down', Int16())
        from std_msgs.msg import Int16
        self.dpad_left = kwargs.get('dpad_left', Int16())
        from std_msgs.msg import Int16
        self.dpad_right = kwargs.get('dpad_right', Int16())

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
        if self.connected != other.connected:
            return False
        if self.back != other.back:
            return False
        if self.leftx != other.leftx:
            return False
        if self.lefty != other.lefty:
            return False
        if self.right_trigger != other.right_trigger:
            return False
        if self.a != other.a:
            return False
        if self.b != other.b:
            return False
        if self.x != other.x:
            return False
        if self.y != other.y:
            return False
        if self.dpad_up != other.dpad_up:
            return False
        if self.dpad_down != other.dpad_down:
            return False
        if self.dpad_left != other.dpad_left:
            return False
        if self.dpad_right != other.dpad_right:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def connected(self):
        """Message field 'connected'."""
        return self._connected

    @connected.setter
    def connected(self, value):
        if __debug__:
            from std_msgs.msg import Bool
            assert \
                isinstance(value, Bool), \
                "The 'connected' field must be a sub message of type 'Bool'"
        self._connected = value

    @builtins.property
    def back(self):
        """Message field 'back'."""
        return self._back

    @back.setter
    def back(self, value):
        if __debug__:
            from std_msgs.msg import Int16
            assert \
                isinstance(value, Int16), \
                "The 'back' field must be a sub message of type 'Int16'"
        self._back = value

    @builtins.property
    def leftx(self):
        """Message field 'leftx'."""
        return self._leftx

    @leftx.setter
    def leftx(self, value):
        if __debug__:
            from std_msgs.msg import Float64
            assert \
                isinstance(value, Float64), \
                "The 'leftx' field must be a sub message of type 'Float64'"
        self._leftx = value

    @builtins.property
    def lefty(self):
        """Message field 'lefty'."""
        return self._lefty

    @lefty.setter
    def lefty(self, value):
        if __debug__:
            from std_msgs.msg import Float64
            assert \
                isinstance(value, Float64), \
                "The 'lefty' field must be a sub message of type 'Float64'"
        self._lefty = value

    @builtins.property
    def right_trigger(self):
        """Message field 'right_trigger'."""
        return self._right_trigger

    @right_trigger.setter
    def right_trigger(self, value):
        if __debug__:
            from std_msgs.msg import Float64
            assert \
                isinstance(value, Float64), \
                "The 'right_trigger' field must be a sub message of type 'Float64'"
        self._right_trigger = value

    @builtins.property
    def a(self):
        """Message field 'a'."""
        return self._a

    @a.setter
    def a(self, value):
        if __debug__:
            from std_msgs.msg import Int16
            assert \
                isinstance(value, Int16), \
                "The 'a' field must be a sub message of type 'Int16'"
        self._a = value

    @builtins.property
    def b(self):
        """Message field 'b'."""
        return self._b

    @b.setter
    def b(self, value):
        if __debug__:
            from std_msgs.msg import Int16
            assert \
                isinstance(value, Int16), \
                "The 'b' field must be a sub message of type 'Int16'"
        self._b = value

    @builtins.property
    def x(self):
        """Message field 'x'."""
        return self._x

    @x.setter
    def x(self, value):
        if __debug__:
            from std_msgs.msg import Int16
            assert \
                isinstance(value, Int16), \
                "The 'x' field must be a sub message of type 'Int16'"
        self._x = value

    @builtins.property
    def y(self):
        """Message field 'y'."""
        return self._y

    @y.setter
    def y(self, value):
        if __debug__:
            from std_msgs.msg import Int16
            assert \
                isinstance(value, Int16), \
                "The 'y' field must be a sub message of type 'Int16'"
        self._y = value

    @builtins.property
    def dpad_up(self):
        """Message field 'dpad_up'."""
        return self._dpad_up

    @dpad_up.setter
    def dpad_up(self, value):
        if __debug__:
            from std_msgs.msg import Int16
            assert \
                isinstance(value, Int16), \
                "The 'dpad_up' field must be a sub message of type 'Int16'"
        self._dpad_up = value

    @builtins.property
    def dpad_down(self):
        """Message field 'dpad_down'."""
        return self._dpad_down

    @dpad_down.setter
    def dpad_down(self, value):
        if __debug__:
            from std_msgs.msg import Int16
            assert \
                isinstance(value, Int16), \
                "The 'dpad_down' field must be a sub message of type 'Int16'"
        self._dpad_down = value

    @builtins.property
    def dpad_left(self):
        """Message field 'dpad_left'."""
        return self._dpad_left

    @dpad_left.setter
    def dpad_left(self, value):
        if __debug__:
            from std_msgs.msg import Int16
            assert \
                isinstance(value, Int16), \
                "The 'dpad_left' field must be a sub message of type 'Int16'"
        self._dpad_left = value

    @builtins.property
    def dpad_right(self):
        """Message field 'dpad_right'."""
        return self._dpad_right

    @dpad_right.setter
    def dpad_right(self, value):
        if __debug__:
            from std_msgs.msg import Int16
            assert \
                isinstance(value, Int16), \
                "The 'dpad_right' field must be a sub message of type 'Int16'"
        self._dpad_right = value
