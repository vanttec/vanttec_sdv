FROM rwthika/ros2-torch:jazzy-ros-base-torch2.5.0

# Set environment variables # Prevent BrokenPipeError in ROS CLI
ENV PYTHONUNBUFFERED=1 

# Install SO dependencies
RUN apt-get update -qq && \
    apt-get install -y --no-install-recommends \
        build-essential \
        nano \
        python3-pip \
        xboxdrv \
        libtool \
        libpcap-dev \
        terminator \
        wget \
        unzip \
        libopenblas-dev \
        libomp-dev
    && rm -rf /var/lib/apt/lists/*

# Install ROS dependencies
RUN apt-get update -qq && \
    apt-get install -y --no-install-recommends \
        ros-jazzy-controller-interface \
        ros-jazzy-realtime-tools \
        ros-jazzy-controller-manager \
        ros-jazzy-ackermann-msgs \
        ros-jazzy-joint-state-publisher \
        ros-jazzy-rqt-tf-tree \
        ros-jazzy-tf2-tools \
        ros-jazzy-ros2-control \
        ros-jazzy-robot-localization \
        ros-jazzy-foxglove-bridge \
        ros-jazzy-diagnostic-updater \
        ros-jazzy-rviz2 \
    && rm -rf /var/lib/apt/lists/*

# Install OpenGL libraries
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        libglx-mesa0 \
        libgl1-mesa-dri \
        mesa-utils \
    && rm -rf /var/lib/apt/lists/*

# Upgrade pip & Install Python dependencies
RUN python3 -m pip install --upgrade pip setuptools && \
    pip install --no-cache-dir python-can && \
    pip install gpytorch && \
    pip install pandas && \
    pip install matplotlib

# === Download & Install LibTorch for CPU ===
RUN wget -O libtorch-cpu.zip https://download.pytorch.org/libtorch/cpu/libtorch-cxx11-abi-shared-with-deps-2.6.0%2Bcpu.zip && \
    unzip libtorch-cpu.zip -d /usr/local/libtorch_cpu && \
    rm libtorch-cpu.zip

# === Download & Install LibTorch for GPU (CUDA 12.6) ===
RUN wget -O libtorch-gpu.zip https://download.pytorch.org/libtorch/cu126/libtorch-cxx11-abi-shared-with-deps-2.6.0%2Bcu126.zip && \
    unzip libtorch-gpu.zip -d /usr/local/libtorch_gpu && \
    rm libtorch-gpu.zip

# === Set environment variables ===
ENV CMAKE_PREFIX_PATH="/usr/local/libtorch_cpu/libtorch:/usr/local/libtorch_gpu/libtorch"
ENV PATH="$CMAKE_PREFIX_PATH/bin:$PATH"
ENV LD_LIBRARY_PATH="$CMAKE_PREFIX_PATH/lib:$LD_LIBRARY_PATH"

# Set CPU path as a fallback (commented out but can be used if needed)
# ENV CMAKE_PREFIX_PATH_CPU="/usr/local/libtorch_cpu"

# Ensure the environment variables persist inside the container
RUN echo 'export CMAKE_PREFIX_PATH="/usr/local/libtorch_cpu/libtorch:/usr/local/libtorch_gpu/libtorch"' >> ~/.bashrc && \
    echo 'export PATH="$CMAKE_PREFIX_PATH/bin:$PATH"' >> ~/.bashrc && \
    echo 'export LD_LIBRARY_PATH="$CMAKE_PREFIX_PATH/lib:$LD_LIBRARY_PATH"' >> ~/.bashrc

# Source ROS and workspace in shell
# RUN echo "source /opt/ros/jazzy/setup.bash" >> /root/.bashrc && \
#     echo "[[ -f /docker-ros/ws/install/setup.bash ]] && source /docker-ros/ws/install/setup.bash" >> /root/.bashrc

# Ensure sourcing happens on container start
# COPY entrypoint.sh /entrypoint.sh THE SAME AS BELOW
# COPY entrypoint.sh /root/entrypoint.sh

# RUN chmod +x /root/entrypoint.sh

# ENTRYPOINT ["/entrypoint.sh"]
CMD ["/bin/bash"]