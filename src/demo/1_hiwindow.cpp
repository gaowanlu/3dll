#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

/**
 * @brief ���ڴ�С�ı�ص�����
 * @param window ���ڶ��� 
 * @param width ���ڵ����¿��
 * @param height ���ڵ����¸߶�
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);//����viewport
}
/**
 * @brief ��ⴰ�ڰ����빦�ܴ���
 * @param window 
*/
void processInput(GLFWwindow* window) {
	//����esc�����ڱ���ѹ
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window,true);//�رմ��ڼ�����WindowShouldClose
		//���´�glfwWindowShouldClose���ʱ��᷵��true�������Ѿ��رյ�״̬
	}
}

void hiwindow() {
	glfwInit();//��ʼ��GLFW
	//ʹ��glfwWindowHint����������GLFW
	//glfwWindowHint�����ĵ�һ����������ѡ�������
	//���ǿ��ԴӺܶ���GLFW_��ͷ��ö��ֵ��ѡ�񣻵ڶ�����������һ������
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//����һ�����ڶ���
	GLFWwindow* window = glfwCreateWindow(800, 600, "LEARNOPENGL", NULL, NULL);
	//glfwCreateWindowǰ��������Ϊ���ڵĿ�͸ߣ�������Ϊ���ڵ����֣��������Ȳ���
	if (window == nullptr) {//������ڴ���ʧ��
		std::cout << "window create failed" << std::endl;
		glfwTerminate();
		return;
	}
	//�����ô��ڶ����֪ͨglfw�����ǵĴ��ڵ�����������Ϊ
	//��ǰ�̵߳���������
	glfwMakeContextCurrent(window);
	//��ʹ��OPENGL�ĺ���֮ǰҪ��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "failed to initialize glad" << std::endl;
		return;
	}
	//�ӿ����ø���OPENGL���ǵ���Ⱦ���ڴ�С�Ƕ���
	glViewport(0, 0, 800, 600);
	//OPENGL����������С��ת��2d����
	//��������Ӧ�����û��ı䴰�ڴ�С�Ǹ�����ͼ��С�ĸı�
	//�Դ���ע��ص�����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//ѭ����Ⱦ
	while (!glfwWindowShouldClose(window)) {//����˴���û�б��ر�
		//��ÿһ֡�����ⰴ��
		processInput(window);
		//��մ������ڵ�����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//������ɫ
		glClear(GL_COLOR_BUFFER_BIT);//����λ��GL_COLOR_BUFFER_BIT��GL_DEPTH_BUFFER_BIT��GL_STENCIL_BUFFER_BIT

		glfwSwapBuffers(window);//������ɫ������һ�������GLFW����ÿ�����صĴ󻺳壬���������������ݻ���
		glfwPollEvents();//�����û�д����¼���������롢����ƶ�������״̬��
	}//�����ڹر�ʱ�����˳�ѭ��
	//�������ǵ�������Ҫ�������񽫻������Ҫ�ͷ�GLFW����Դ������Ҫ���ǵ���glfwTerminate
	glfwTerminate();
}