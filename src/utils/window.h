#pragma once
#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <graphics.h>
#include <easyx.h>
#include <Eigen/Dense>
#include "../camera/camera.h"

/**
 * @brief ����
*/
class window {
private:
	int _width;
	int _height;
	//��������ϵ��
	Eigen::Matrix<double, 3, 3> _world_base;
	/**
	* @brief ��ʼ������
	*/
	void init_window(int console);
public:
	window(int width,int height,int console);

	/**
	* @brief ��ȡ���ڿ��
	* @return
	*/
	int get_width();

	/**
	* @brief ��ȡ���ڸ߶�
	* @return
	*/
	int get_height();

	/**
	* @brief ���û�����ɫ
	* @param r ��
	* @param g ��
	* @param b ��
	*/
	void set_linecolor(unsigned char r, unsigned char g, unsigned char  b);

	/**
	* @brief ��ȡ��������ϵ��
	* @return
	*/
	Eigen::Matrix<double, 3, 3> get_world_base();


	/**
	 * @brief 
	 * �˴���x��yΪ�������ϵ��ԭ������Ļ���ģ���Ϊx����Ϊy
	 * esayx ����ԭ�����豸�����Ͻǣ�X ������Ϊ����Y ������Ϊ����������λ������
	 * �������ϵ��ͼ������ϵ
	 * @param x �������ϵx
	 * @param y �������ϵy
	 * @param z �������ϵz
	 * @return 
	*/
	Eigen::Matrix<double, 3, 1> to_xy(double x, double y, double z,camera m_camera);

	/**
	 * @brief ��ֱ��
	 * @param dot1 ����1
	 * @param dot2 ����2
	*/
	void draw_t_line(Eigen::Matrix<double, 3, 1> dot1, Eigen::Matrix<double, 3, 1> dot2);

	/**
	 * @brief �������
	*/
	void clear();

	/**
	 * @brief sleep ����
	*/
	void sleep(int mseconds);

	/**
	 * @brief ��ô��ڲٿ���Ϣ
	*/
	bool get_message(ExMessage* message);
};
#endif // !__WINDOW_H__