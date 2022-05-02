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
#include "model/cuboid.h"

int main(int argc, char** argv) {
	window m_window(1000,700,1);
	m_window.set_linecolor(0,255,0);
	cuboid model_1({
		Model({//����
			{3, 3, 0 },
			{3, 6, 0},
			{6, 6, 0},
			{6, 3, 0}
		}),
		Model({//����
			{3, 3, 10 },
			{3, 6, 10},
			{6, 6, 10},
			{6, 3, 10}
		}),
		Model({//ǰ��
			{3, 3, 0 },
			{6, 3, 0},
			{6, 3, 10},
			{3, 3, 10}
		}),
		Model({//����
			{3, 6, 0 },
			{6, 6, 0},
			{6, 6, 10},
			{3, 6, 10}
		}),
		Model({//����
			{3, 3, 0 },
			{3, 6, 0},
			{3, 6, 10},
			{3, 3, 10}
		}),
		Model({//����
			{6, 3, 0 },
			{6, 6, 0},
			{6, 6, 10},
			{6, 3, 10}
		})
	});
	//����ģ��
	std::vector<cuboid>models;
	models.push_back(model_1);
	for (int i = 3; i <= 99; i+=3) {
		models.push_back(model_1.move(i, 0, 0));
		models.push_back(model_1.move(0, i, 0));
	}
	models.push_back(model_1.move(-10, -10, 10));

	Model model_z({
		{0, 0, 0},
		{0, 0, 70} }, 'z');
	Model model_x({
		{0, 0, 0},
		{30, 0, 0} }, 'x');
	Model model_y({
		{0, 0, 0},
		{0, 30, 0} }, 'y');
	
	cuboid grid;//�ص�����
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

	camera m_camera;

	//��¼��һ������λ��
	int last_x = 0, last_y = 0;
	double last_resize = 1.0;//���Ų���
	double x_angle = 0., y_angle = 0., z_angle = 0.;//�������ϵʵʱ��ת�Ƕ�

	Eigen::Matrix<double, 3, 3> camera_realtime=m_camera.trans(0,0,0);

	while (1) {
		//��Ⱦ����
		m_window.set_fillcolor(200, 200, 200);
		m_window.set_linecolor(155,155,155);
		m_window.render_cuboid(grid,last_resize, m_camera, camera_realtime);
		m_window.set_linecolor(255, 0, 0);
		m_window.render_model(model_x, last_resize, m_camera, camera_realtime);
		m_window.render_model(model_y, last_resize, m_camera, camera_realtime);
		m_window.render_model(model_z, last_resize, m_camera, camera_realtime);

		//ģ����Ⱦ
		m_window.set_linecolor(200, 134, 45);
		m_window.set_fillcolor(124, 23, 124);
		for (std::size_t k = 0; k < models.size();k++) {
			m_window.render_cuboid(models[k],last_resize,m_camera,camera_realtime);
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