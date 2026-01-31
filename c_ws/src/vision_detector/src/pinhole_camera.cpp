#include "vision_detector/detector.hpp"

coordinate PinholeCamera::CoordinateDetector()
{
    coordinate target;
    target.z = target_depth_;
    target.x = ((target_x_-center_x_)*target_depth_)/focal_length_x_;
    target.y = ((target_y_-center_y_)*target_depth_)/focal_length_y_;

    return target;

}