#include <iostream>

#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_cloud.h>
#include <pcl/console/parse.h>
#include <pcl/common/transforms.h>
#include <pcl/visualization/pcl_visualizer.h>

// This function displays the help
void showHelp(char *program_name)
{
  std::cout << std::endl;
  std::cout << "Usage: " << program_name << " cloud_filename.[pcd|ply]" << std::endl;
  std::cout << "-h:  Show this help." << std::endl;
}

// This is the main function
int main(int argc, char **argv)
{

  // Show help
  if (pcl::console::find_switch(argc, argv, "-h") || pcl::console::find_switch(argc, argv, "--help"))
  {
    showHelp(argv[0]);
    return 0;
  }

  // Fetch point cloud filename in arguments | Works with PCD and PLY files
  std::vector<int> filenames;
  bool file_is_pcd = false;

  filenames = pcl::console::parse_file_extension_argument(argc, argv, ".ply");

  if (filenames.size() != 1)
  {
    filenames = pcl::console::parse_file_extension_argument(argc, argv, ".pcd");

    if (filenames.size() != 1)
    {
      showHelp(argv[0]);
      return -1;
    }
    else
    {
      file_is_pcd = true;
    }
  }

  // Load file | Works with PCD and PLY files
  pcl::PointCloud<pcl::PointXYZ>::Ptr source_cloud(new pcl::PointCloud<pcl::PointXYZ>());

  if (file_is_pcd)
  {
    if (pcl::io::loadPCDFile(argv[filenames[0]], *source_cloud) < 0)
    {
      std::cout << "Error loading point cloud " << argv[filenames[0]] << std::endl
                << std::endl;
      showHelp(argv[0]);
      return -1;
    }
  }
  else
  {
    if (pcl::io::loadPLYFile(argv[filenames[0]], *source_cloud) < 0)
    {
      std::cout << "Error loading point cloud " << argv[filenames[0]] << std::endl
                << std::endl;
      showHelp(argv[0]);
      return -1;
    }
  }

  // The angles of rotation in radians
  float theta1 = M_PI / 2;
  float theta2 = 180 * M_PI / 180;

  Eigen::Affine3f transform = Eigen::Affine3f::Identity();

  // Define a translation of 0.08 meters on the x axis.
  //transform.translation() << 0.08, 0.0, 0.0;

  // The same rotation matrix as before; theta radians around X & Y axis
  transform.rotate(Eigen::AngleAxisf(theta1, Eigen::Vector3f::UnitY()));
  transform.rotate(Eigen::AngleAxisf(theta2, Eigen::Vector3f::UnitX()));

  // Print the transformation
  printf("\nMethod: using an Affine3f\n");
  std::cout << transform.matrix() << std::endl;

  // Executing the transformation
  pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_cloud(new pcl::PointCloud<pcl::PointXYZ>());
  pcl::transformPointCloud(*source_cloud, *transformed_cloud, transform);

  // Visualization
  printf("\nPoint cloud colors :  white  = original point cloud\n"
         "                        red  = transformed point cloud\n");
  pcl::visualization::PCLVisualizer viewer("Matrix transformation example");

  // Define R,G,B colors for the point cloud
  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> source_cloud_color_handler(source_cloud, 255, 255, 255);
  // We add the point cloud to the viewer and pass the color handler
  viewer.addPointCloud(source_cloud, source_cloud_color_handler, "original_cloud");

  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_handler(transformed_cloud, 230, 20, 20); // Red
  viewer.addPointCloud(transformed_cloud, transformed_cloud_color_handler, "transformed_cloud");

  viewer.addCoordinateSystem(1.0, "cloud", 0);
  viewer.setBackgroundColor(0.05, 0.05, 0.05, 0); // Setting background to a dark grey
  viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "original_cloud");
  viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloud");
  //viewer.setPosition(800, 400); // Setting visualiser window position

  while (!viewer.wasStopped())
  { // Display the visualiser until 'q' key is pressed
    viewer.spinOnce();
  }

  return 0;
}
