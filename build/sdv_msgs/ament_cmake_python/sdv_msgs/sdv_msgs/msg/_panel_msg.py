# generated from rosidl_generator_py/resource/_idl.py.em
# with input from sdv_msgs:msg/PanelMsg.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_PanelMsg(type):
    """Metaclass of message 'PanelMsg'."""

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
                'sdv_msgs.msg.PanelMsg')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__panel_msg
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__panel_msg
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__panel_msg
            cls._TYPE_SUPPORT = module.type_support_msg__msg__panel_msg
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__panel_msg

            from std_msgs.msg import Bool
            if Bool.__class__._TYPE_SUPPORT is None:
                Bool.__class__.__import_type_support__()

            from std_msgs.msg import ByteMultiArray
            if ByteMultiArray.__class__._TYPE_SUPPORT is None:
                ByteMultiArray.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class PanelMsg(metaclass=Metaclass_PanelMsg):
    """Message class 'PanelMsg'."""

    __slots__ = [
        '_wiper',
        '_horn',
        '_right_upper_front_light',
        '_left_upper_front_light',
        '_right_down_front_light',
        '_left_down_front_light',
        '_back',
        '_xboxcontrol',
    ]

    _fields_and_field_types = {
        'wiper': 'std_msgs/Bool',
        'horn': 'std_msgs/Bool',
        'right_upper_front_light': 'std_msgs/Bool',
        'left_upper_front_light': 'std_msgs/Bool',
        'right_down_front_light': 'std_msgs/Bool',
        'left_down_front_light': 'std_msgs/Bool',
        'back': 'std_msgs/Bool',
        'xboxcontrol': 'std_msgs/ByteMultiArray',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Bool'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Bool'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Bool'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Bool'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Bool'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Bool'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Bool'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'ByteMultiArray'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Bool
        self.wiper = kwargs.get('wiper', Bool())
        from std_msgs.msg import Bool
        self.horn = kwargs.get('horn', Bool())
        from std_msgs.msg import Bool
        self.right_upper_front_light = kwargs.get('right_upper_front_light', Bool())
        from std_msgs.msg import Bool
        self.left_upper_front_light = kwargs.get('left_upper_front_light', Bool())
        from std_msgs.msg import Bool
        self.right_down_front_light = kwargs.get('right_down_front_light', Bool())
        from std_msgs.msg import Bool
        self.left_down_front_light = kwargs.get('left_down_front_light', Bool())
        from std_msgs.msg import Bool
        self.back = kwargs.get('back', Bool())
        from std_msgs.msg import ByteMultiArray
        self.xboxcontrol = kwargs.get('xboxcontrol', ByteMultiArray())

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
        if self.wiper != other.wiper:
            return False
        if self.horn != other.horn:
            return False
        if self.right_upper_front_light != other.right_upper_front_light:
            return False
        if self.left_upper_front_light != other.left_upper_front_light:
            return False
        if self.right_down_front_light != other.right_down_front_light:
            return False
        if self.left_down_front_light != other.left_down_front_light:
            return False
        if self.back != other.back:
            return False
        if self.xboxcontrol != other.xboxcontrol:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def wiper(self):
        """Message field 'wiper'."""
        return self._wiper

    @wiper.setter
    def wiper(self, value):
        if __debug__:
            from std_msgs.msg import Bool
            assert \
                isinstance(value, Bool), \
                "The 'wiper' field must be a sub message of type 'Bool'"
        self._wiper = value

    @builtins.property
    def horn(self):
        """Message field 'horn'."""
        return self._horn

    @horn.setter
    def horn(self, value):
        if __debug__:
            from std_msgs.msg import Bool
            assert \
                isinstance(value, Bool), \
                "The 'horn' field must be a sub message of type 'Bool'"
        self._horn = value

    @builtins.property
    def right_upper_front_light(self):
        """Message field 'right_upper_front_light'."""
        return self._right_upper_front_light

    @right_upper_front_light.setter
    def right_upper_front_light(self, value):
        if __debug__:
            from std_msgs.msg import Bool
            assert \
                isinstance(value, Bool), \
                "The 'right_upper_front_light' field must be a sub message of type 'Bool'"
        self._right_upper_front_light = value

    @builtins.property
    def left_upper_front_light(self):
        """Message field 'left_upper_front_light'."""
        return self._left_upper_front_light

    @left_upper_front_light.setter
    def left_upper_front_light(self, value):
        if __debug__:
            from std_msgs.msg import Bool
            assert \
                isinstance(value, Bool), \
                "The 'left_upper_front_light' field must be a sub message of type 'Bool'"
        self._left_upper_front_light = value

    @builtins.property
    def right_down_front_light(self):
        """Message field 'right_down_front_light'."""
        return self._right_down_front_light

    @right_down_front_light.setter
    def right_down_front_light(self, value):
        if __debug__:
            from std_msgs.msg import Bool
            assert \
                isinstance(value, Bool), \
                "The 'right_down_front_light' field must be a sub message of type 'Bool'"
        self._right_down_front_light = value

    @builtins.property
    def left_down_front_light(self):
        """Message field 'left_down_front_light'."""
        return self._left_down_front_light

    @left_down_front_light.setter
    def left_down_front_light(self, value):
        if __debug__:
            from std_msgs.msg import Bool
            assert \
                isinstance(value, Bool), \
                "The 'left_down_front_light' field must be a sub message of type 'Bool'"
        self._left_down_front_light = value

    @builtins.property
    def back(self):
        """Message field 'back'."""
        return self._back

    @back.setter
    def back(self, value):
        if __debug__:
            from std_msgs.msg import Bool
            assert \
                isinstance(value, Bool), \
                "The 'back' field must be a sub message of type 'Bool'"
        self._back = value

    @builtins.property
    def xboxcontrol(self):
        """Message field 'xboxcontrol'."""
        return self._xboxcontrol

    @xboxcontrol.setter
    def xboxcontrol(self, value):
        if __debug__:
            from std_msgs.msg import ByteMultiArray
            assert \
                isinstance(value, ByteMultiArray), \
                "The 'xboxcontrol' field must be a sub message of type 'ByteMultiArray'"
        self._xboxcontrol = value
