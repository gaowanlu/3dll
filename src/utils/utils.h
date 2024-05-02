#pragma once
#ifndef __UTILS_H__
#define __UTILS_H__
#include <Eigen/Dense>
/**
 * @brief 常用工具方法
 */
class utils
{
public:
	static constexpr double PI = 3.14159265;

	/**
	 * @brief 生成3*3旋转矩阵绕x轴
	 * @param angle 旋转角度
	 * @return 旋转矩阵
	 */
	static Eigen::Matrix<double, 3, 3> roate_x(double angle)
	{
		angle = angle * PI / 180.;
		Eigen::Matrix<double, 3, 3> m;
		m << 1., 0., 0., 0., cos(angle), -sin(angle), 0., sin(angle), cos(angle);
		return m;
	}
	/**
	 * @brief 生成3*3旋转矩阵绕y轴
	 * @param angle 旋转角度
	 * @return 旋转矩阵
	 */
	static Eigen::Matrix<double, 3, 3> roate_y(double angle)
	{
		angle = angle * PI / 180.;
		Eigen::Matrix<double, 3, 3> m;
		m << cos(angle), 0., sin(angle), 0., 1., 0., -sin(angle), 0., cos(angle);
		return m;
	}

	/**
	 * @brief 生成3*3旋转矩阵绕z轴
	 * @param angle 旋转角度
	 * @return 旋转矩阵
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