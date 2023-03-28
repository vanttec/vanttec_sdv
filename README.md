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
sudo 
sudo make sdv.up 
sudo make sdv.shell
cd /ws/src
git clone https://github.com/vanttec/sdv_embedded
cd ..
colcon build

```

Read more about the matching algorithm [here][vanttec-documentation].


[vanttec-documentation]: https://vanttec-documentation.readthedocs.io/
[tutorial]: contrib/perrito-carro.webp