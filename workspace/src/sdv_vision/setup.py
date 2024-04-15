from setuptools import find_packages, setup
import os
from glob import glob
package_name = 'sdv_vision'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name), glob(os.path.join('launch', '*.launch.py'))),
        (os.path.join('share', package_name), glob(os.path.join('Yolov8', 'weights', '*.pt'))),
        (os.path.join('share', package_name), glob(os.path.join('data', 'test_videos', '*.mp4'))),
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
            'lane_detection = yolov8_lane_detection.lane_detection:main', 
            'people_distance_detection = yolov8_object_detection.people_distance_detection:main',
            'video_writer = yolov8_object_detection.video_writer:main'   
        ],
    },
)
