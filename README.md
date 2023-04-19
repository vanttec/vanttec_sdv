<!-- markdownlint-configure-file {
  "MD013": {
    "code_blocks": false,
    "tables": false
  },
  "MD033": false,
  "MD041": false
} -->

<div align="center">

# SDV_EMBEDDED 


SDV EMBEDDED is the official respository for VANTTEC self driving vehicle

It includes code made for controlling the acceleartion, steering , braking and lights inside the car.<br />

[Getting started](#getting-started)

</div>

## Getting started

![Tutorial][tutorial]

```sh
sudo ./create_container_intel.bash
sudo make sdv.up 
sudo make sdv.shell
cd /ws/src
colcon build

```

Read more about the official documentation [here][vanttec-documentation].


[vanttec-documentation]: https://vanttec-documentation.readthedocs.io/
[tutorial]: contrib/perrito-carro.webp