#include <iostream>
#include <graphics.h>
#include <easyx.h>
#include <cmath>
#include <vector>
#include <conio.h>
#include <Eigen/Dense>
#include "utils/utils.h"
#include "camera/camera.h"
#include "utils/window.h"
#include "model/model.h"
#include "camera/camera.h"

int main(int argc, char** argv) {
	window m_window(1000,700,1);
	m_window.set_linecolor(0,255,0);
	Model model_1({
		{2, 13, 0},
		{2, 15, 0},
		{14, 13, 0},
		{14, 15, 0},
		{2,	13, 7},
		{2, 15, 7},
		{14, 13, 7},
		{14, 15, 7}},'1');
	Model model_2({
		{7, -11, 0},
		{7, -5, 0},
		{9, -15, 0},
		{27, -5, 0},
		{7, -31, 2},
		{7, -5, 2},
		{9, -33, 2},
		{17, -5, 2} }, '2');

	Model model_3({
		{-2, -3, 0},
		{-2, -5, 0},
		{-4, -3, 0},
		{-4, -5, 0},
		{-2, -3, 20},
		{-2, -5, 20},
		{-4, -3, 20},
		{-4, -5, 20} }, '3');
	Model model_z({
		{0, 0, 0},
		{0, 0, 70} }, 'z');
	Model model_x({
		{0, 0, 0},
		{30, 0, 0} }, 'x');
	Model model_y({
		{0, 0, 0},
		{0, 30, 0} }, 'y');
	
	std::vector<Model>grid;//�ص�����
	for (int x = -30; x <= 30; x+=5) {
		for (int y = -30; y <= 30; y+=5) {
			Eigen::Matrix<double, 3, 1> v1(
				 x,y ,0);
			Eigen::Matrix<double, 3, 1> v2(
				x+5,y,0 );
			Eigen::Matrix<double, 3, 1> v3(
				x+5,y+5,0 );
			Eigen::Matrix<double, 3, 1> v4(
				x,y+5,0);
			std::vector<Eigen::Matrix<double, 3, 1>> ves{v1, v2, v3, v4};
			Model block(ves, ' ');
			grid.push_back(block);
		}
	}
	//����ģ��
	std::vector<Model>models{model_1,model_2,model_3};
	camera m_camera;

	//��¼��һ������λ��
	int last_x = 0, last_y = 0;
	double last_resize = 1.0;//���Ų���
	double x_angle = 0., y_angle = 0., z_angle = 0.;//�������ϵʵʱ��ת�Ƕ�

	Eigen::Matrix<double, 3, 3> camera_realtime=m_camera.trans(0,0,0);

	while (1) {
		m_window.set_linecolor(255, 0, 0);
		m_window.render_model(model_x, last_resize, m_camera, camera_realtime);
		m_window.render_model(model_y, last_resize, m_camera, camera_realtime);
		m_window.render_model(model_z, last_resize, m_camera, camera_realtime);
		//��Ⱦ����
		m_window.set_linecolor(155,155,155);
		for (size_t j = 0; j < grid.size(); j++) {
			std::vector<std::vector<int>> dots;
			std::vector<Eigen::Matrix<double, 3, 1>> block = grid[j].resize(last_resize).get_matrix();
			for (int i = 0; i <= block.size(); i++) {
				Eigen::Matrix<double, 3, 1> dot_realtime =  m_window.get_world_base() *camera_realtime.inverse() * block[i % block.size()];
				Eigen::Matrix<double, 3, 1> window_dot = m_window.to_xy(dot_realtime(0), dot_realtime(1), dot_realtime(2),m_camera);
				dots.push_back(std::vector<int>{ (int)window_dot(0), (int)window_dot(1) });
			}
			POINT pts[5] = {
				{dots[0][0],dots[0][1]},
				{dots[1][0],dots[1][1]},
				{dots[2][0],dots[2][1]},
				{dots[3][0],dots[3][1]},
				{dots[4][0],dots[4][1]} };
			polygon(pts, 5);
		}

		//ģ����Ⱦ
		m_window.set_linecolor(0, 255, 0);
		for (std::size_t k = 0; k < models.size();k++) {
			m_window.render_model(models[k],last_resize,m_camera,camera_realtime);
		}

		//�ٿز���
		ExMessage message;
		if (m_window.get_message(&message)) {
			if (message.message == WM_KEYDOWN) {
				if (message.vkcode == 'A') {
					m_camera.move(1, 0, 0);
				}
				else if (message.vkcode == 'S') {
					m_camera.move(0, 1, 0);
				}
				else if (message.vkcode == 'D') {
					m_camera.move(-1, 0, 0);
				}
				else if (message.vkcode == 'W') {
					m_camera.move(0, -1, 0);
				}
			}
			if (message.mbutton) {//����м�����
				x_angle = 0, y_angle = 0, z_angle = 0;
				camera_realtime = m_camera.trans(x_angle, y_angle, z_angle);//�����λ
				last_resize = 1.;//���Ź�λ
				m_camera.clear_move();//ƫ��������
			}
			if (message.lbutton) {//����������
				int dx = -(message.x - last_x);//������ x y��ƫ����
				int dy = -(message.y - last_y);
				last_x = message.x;
				last_y = message.y;
				if (fabs(dx) < 10 && fabs(dy) < 10) {
					x_angle = ((int)x_angle + dy) % 360, y_angle = ((int)y_angle + dx) % 360, z_angle += 0;
				}
				//������б任
				camera_realtime = m_camera.trans(x_angle, y_angle, z_angle);//�����������
			}
			if (message.wheel) {
				if (message.ctrl) {//z����ת
					double dz = message.wheel / 20.;
					z_angle = ((int)z_angle + (int)dz) % 360;
				}
				else {//�������Ų�������
					double dz = fabs(message.wheel) / 950.;//һ�ι���120
					if (message.wheel < 0 && (last_resize - dz)>0.1) {//��С
						last_resize = last_resize - dz;
						m_camera.dz=last_resize;
					}
					else if (last_resize + dz < 15) {//���
						last_resize = last_resize + dz;
						m_camera.dz = last_resize;
					}
				}
				//������б任
				camera_realtime = m_camera.trans(x_angle, y_angle, z_angle);//�����������
			}
			//��������
			RECT r = { 0, 0, 639, 479 };
			TCHAR s[512];
			_stprintf_s(s, _T("x_angle %.3lf y_angle %.3lf z_angle %.3lf resize %.3lf "),x_angle,y_angle,z_angle,last_resize);
			drawtext(s, & r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}

		m_window.sleep(50);//˯��
		m_window.clear();//����
	}
	return 0;
}