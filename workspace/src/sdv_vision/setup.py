from setuptools import find_packages, setup

package_name = 'yolov8_lane_detection'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='lolo',
    maintainer_email='lolo@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            #executable name
            'video_publisher = yolov8_lane_detection.video_pub:main',
            'lane_detection = yolov8_lane_detection.lane_detection:main'  
        ],
    },
)
