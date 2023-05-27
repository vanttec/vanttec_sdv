<!-- markdownlint-configure-file {
  "MD013": {
    "code_blocks": false,
    "tables": false
  },
  "MD033": false,
  "MD041": false
} -->

<div align="center">

# SDV_ROS2


SDV ROS2 is the official respository for VANTTEC self driving vehicle

It includes code made for controlling the acceleartion, steering , braking and lights inside the car.<br />

[Getting started](#getting-started)

</div>

## Getting started

![Tutorial][tutorial]

```sh
sudo make sdv.build
sudo ./create_container_intel.bash
sudo make sdv.up 
sudo make sdv.shell
cd /home/ws/
git clone --recurse-submodules https://github.com/vanttec/sdv_ros.git
cd src/sdv_ros/can_devices/sdv_can/libs/vanttec_CANLib/
git checkout feature/sdv_can
cd /home/ws/
colcon build

```

Read more about the official documentation [here][vanttec-documentation].


[vanttec-documentation]: https://vanttec-documentation.readthedocs.io/
[tutorial]: contrib/perrito-carro.webp
