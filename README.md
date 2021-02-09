# matrix_transformation

## Brief

[![C++: solutions](https://img.shields.io/badge/C++-Solutions-blue.svg?style=flat&logo=c%2B%2B)](https://es.wikipedia.org/wiki/C%2B%2B) [![support level: community](https://img.shields.io/badge/support%20level-community-lightgray.png)](http://wiki.ros.org/Industrial)

>  Transform a point cloud using a 4x4 matrix (applying rotation and a translation).

## Input file structure

- **.pcd** or **.ply** file.

Check your .pcd/.ply file with: `head <pcd/ply file>`

## Output file structure

```
Method: using an Affine3f
 0.707107 -0.707107         0       2.5
 0.707107  0.707107         0         0
        0         0         1         0
        0         0         0         1

Point cloud colors :  white   = original point cloud
                       red    = transformed point cloud
```

## Dependency

- [pcl](https://pointclouds.org/downloads/) (Point Cloud Library)

You can install pcl using:

```
sudo apt install libpcl-dev
```

## Compile

You can use the following commands to compile the package:

```
git clone https://github.com/cristianrubioa/matrix_transformation.git
cd /matrix_transformation
mkdir build && cd build
cmake ../src/
make
```

## Run the package

Stand in the "build" folder and run:

```
cd ~/matrix_transformation/build
./matrix_transformation ../models/ply or pcd file>

./matrix_transform ../models/cube.ply   #e.g.
```

