FROM osrf/ros:humble-desktop
RUN apt-get update -y
RUN apt-get install python3-pip -y
RUN pip install python-can
RUN apt-get install xboxdrv -y
RUN pip install setuptools==58.2.0

RUN echo "source /opt/ros/humble/setup.bash" >> /root/.bashrc
RUN echo "source /home/ws/install/setup.bash" >> /root/.bashrc