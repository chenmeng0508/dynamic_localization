#ifndef ROBOT_PERCEPTION_H
#define ROBOT_PERCEPTION_H


#include <ros/ros.h>
#include <ros/package.h>
#include <nav_msgs/OccupancyGrid.h>
#include <map_server/image_loader.h>
#include <sensor_msgs/LaserScan.h>
#include <stdr_msgs/RfidSensorMeasurementMsg.h>
#include <stdr_msgs/RfidTagVector.h>
#include <stdr_msgs/RfidTag.h>
#include <std_msgs/Bool.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <dynamic_localization/DynamicObstacles.h> 
#include <dynamic_localization/DynamicCoordinates.h> 

#include <tf/tf.h>
#include <tf/transform_listener.h>

#include <fstream>
#include <sstream>
#include <iterator>
#include <yaml-cpp/yaml.h>


#define PI 3.14159265359


struct laser
{
	int laser_id;
	int x;
	int y;
	float laser_range;
};

struct dunamika
{
	int x;
	int y;
};




class RobotPerception
{
  private:
    ros::NodeHandle _n;
    std::string _map_topic_param;
    std::string _laser_topic_param;
    std::string _rfid_reader_topic_param;
    std::string _rfid_tags_topic_param;
    
    std::string _position_topic;
    std::string _target_topic;
    std::string _velocity_topic;
    ros::Timer _position_timer;
    ros::Timer _target_timer;
    tf::TransformListener _listener;
    ros::Subscriber _vel_sub;

    
    ros::Subscriber _map_sub;
    ros::Subscriber _laser_sub;
    ros::Subscriber _rfid_reader_sub;
    ros::Subscriber _rfid_tags_sub;
    
    ros::Publisher _dynamic_coor_pub;
    ros::Publisher _dynamic_obst_pub;
    ros::Publisher _marker_pub;
    ros::Publisher _dynamic_pub;
    
    unsigned int _map_width;
    unsigned int _map_height;
    float _map_resolution;
    int** _map_data; 
    std::vector<float> _laser_ranges;
    std::vector<float> _static_laser_ranges;
    std::vector<float> _static_id_ranges;
    std::vector<float> _ranges;
    
    
    
    float* _prohgoumeno_laser_ranges;
    int _counter;
    int _counter3;
    float _prev_linear;
	float _prev_angular;
	float _prev_target_x;
	float _prev_target_y;
	float _prev_target_yaw;
	float _prev_x;
	float _prev_y;
	float _prev_yaw;
	
    
    std::vector<laser> _dynamic_ranges;
    std::vector<laser> _static_ranges;
    std::vector<std::string> _rfid_ids;
    std::vector<std::string> _rfid_msgs;
    std::vector<std::vector<float> > _rfid_pose;
    std::vector<stdr_msgs::RfidTag> _rfid_tags;
    std::vector<std::string> _rfid_tags_id;
    std::vector<float> _rfid_tags_x;
    std::vector<float> _rfid_tags_y;
    float _max_range;
    float _increment;
    float _angle_min;

	int** _static_data; 
    int _static_width;
    int _static_height;
    float _static_resolution;
    //~ float* _ranges;
    float* _ranges1;
	
	
	float _x;
	float _y;
	float _yaw;
	float _target_x;
	float _target_y;
	float _target_yaw;
	float _dx;
	double _dy;
	float _dyaw;
	float _linear;
	float _angular;
	
	ros::Time _current_time;
	ros::Time _previous_time;
	ros::Duration _dt;
	ros::Duration _dt1;
	bool _time_flag;
	int _a;
	float _duration;	
	
	
  public:
    RobotPerception();
    void mapCallback(nav_msgs::OccupancyGrid occupancy_grid_msg);
    void laserRangesCallback(sensor_msgs::LaserScan laser_scan_msg);    
    void RfidReaderCallback (stdr_msgs::RfidSensorMeasurementMsg rfid_reader_msg);
    void RfidTagsCallback (stdr_msgs::RfidTagVector rfid_tag_msg);
    void RfidPose();
    unsigned int getMapWidth();
    unsigned int getMapHeight();
    float getMapResolution();
    int** getMapData();
    int getMapCell (int i, int j);
    std::vector<float> getLaserRanges();
    float getRangeMax();
    float getAngleIncrement();
    float getAngleMin();
    std::vector<std::string> getRfidIds();
    std::vector<std::string> getRfidMsgs();
    std::vector<std::vector<float> > getRfidPose();

    bool map_initialized;
    
    void findLaserXY();
    void findStaticLaser();

    void staticMap();
    int** getStaticData();
    std::vector <float> getStaticRanges();
    std::vector <float> getStaticIdRanges();
    void visual(float x, float y, float x1, float y1, int ii);
    void visual();
    void tooManyDynamic();
    void currentPosition(const ros::TimerEvent& e);
    

    
};

#endif
