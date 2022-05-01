#pragma once
#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <graphics.h>
#include <easyx.h>
#include <Eigen/Dense>
#include "../camera/camera.h"

/**
 * @brief 窗口
*/
class window {
private:
	int _width;
	int _height;
	//世界坐标系基
	Eigen::Matrix<double, 3, 3> _world_base;
	/**
	* @brief 初始化窗口
	*/
	void init_window(int console);
public:
	window(int width,int height,int console);

	/**
	* @brief 获取窗口宽度
	* @return
	*/
	int get_width();

	/**
	* @brief 获取窗口高度
	* @return
	*/
	int get_height();

	/**
	* @brief 设置划线颜色
	* @param r 红
	* @param g 蓝
	* @param b 绿
	*/
	void set_linecolor(unsigned char r, unsigned char g, unsigned char  b);

	/**
	* @brief 获取世界坐标系基
	* @return
	*/
	Eigen::Matrix<double, 3, 3> get_world_base();


	/**
	 * @brief 
	 * 此处的x，y为相机坐标系，原点在屏幕中心，右为x，上为y
	 * esayx 坐标原点在设备的左上角，X 轴向右为正，Y 轴向下为正，度量单位是像素
	 * 相机坐标系到图像坐标系
	 * @param x 相机坐标系x
	 * @param y 相机坐标系y
	 * @param z 相机坐标系z
	 * @return 
	*/
	Eigen::Matrix<double, 3, 1> to_xy(double x, double y, double z,camera m_camera);

	/**
	 * @brief 画直线
	 * @param dot1 向量1
	 * @param dot2 向量2
	*/
	void draw_t_line(Eigen::Matrix<double, 3, 1> dot1, Eigen::Matrix<double, 3, 1> dot2);

	/**
	 * @brief 清除窗口
	*/
	void clear();

	/**
	 * @brief sleep 毫秒
	*/
	void sleep(int mseconds);

	/**
	 * @brief 获得窗口操控信息
	*/
	bool get_message(ExMessage* message);
};
#endif // !__WINDOW_H__