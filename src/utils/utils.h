#pragma once
#ifndef __UTILS_H__
#define __UTILS_H__
#include <Eigen/Dense>
/**
 * @brief ���ù��߷���
 */
class utils
{
public:
	static constexpr double PI = 3.14159265;

	/**
	 * @brief ����3*3��ת������x��
	 * @param angle ��ת�Ƕ�
	 * @return ��ת����
	 */
	static Eigen::Matrix<double, 3, 3> roate_x(double angle)
	{
		angle = angle * PI / 180.;
		Eigen::Matrix<double, 3, 3> m;
		m << 1., 0., 0., 0., cos(angle), -sin(angle), 0., sin(angle), cos(angle);
		return m;
	}
	/**
	 * @brief ����3*3��ת������y��
	 * @param angle ��ת�Ƕ�
	 * @return ��ת����
	 */
	static Eigen::Matrix<double, 3, 3> roate_y(double angle)
	{
		angle = angle * PI / 180.;
		Eigen::Matrix<double, 3, 3> m;
		m << cos(angle), 0., sin(angle), 0., 1., 0., -sin(angle), 0., cos(angle);
		return m;
	}

	/**
	 * @brief ����3*3��ת������z��
	 * @param angle ��ת�Ƕ�
	 * @return ��ת����
	 */
	static Eigen::Matrix<double, 3, 3> roate_z(double angle)
	{
		angle = angle * PI / 180.;
		Eigen::Matrix<double, 3, 3> m;
		m << cos(angle), -sin(angle), 0., sin(angle), cos(angle), 0., 0., 0., 1.;
		return m;
	}
};
#endif // !__UTILS_H__