#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

/**
 * @brief 窗口大小改变回调函数
 * @param window 窗口对象 
 * @param width 窗口的最新宽度
 * @param height 窗口的最新高度
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);//更新viewport
}
/**
 * @brief 检测窗口按键与功能处理
 * @param window 
*/
void processInput(GLFWwindow* window) {
	//现在esc键正在被按压
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window,true);//关闭窗口即设置WindowShouldClose
		//当下次glfwWindowShouldClose检测时则会返回true即窗口已经关闭的状态
	}
}

void hiwindow() {
	glfwInit();//初始化GLFW
	//使用glfwWindowHint函数来配置GLFW
	//glfwWindowHint函数的第一个参数代表选项的名称
	//我们可以从很多以GLFW_开头的枚举值中选择；第二个参数接受一个整型
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//创建一个窗口对象
	GLFWwindow* window = glfwCreateWindow(800, 600, "LEARNOPENGL", NULL, NULL);
	//glfwCreateWindow前两个参数为窗口的宽和高，第三个为窗口的名字，后两个先不管
	if (window == nullptr) {//如果窗口创建失败
		std::cout << "window create failed" << std::endl;
		glfwTerminate();
		return;
	}
	//创建好窗口对象后，通知glfw将我们的窗口的上下文设置为
	//当前线程的主上下文
	glfwMakeContextCurrent(window);
	//在使用OPENGL的函数之前要初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "failed to initialize glad" << std::endl;
		return;
	}
	//视口配置告诉OPENGL我们的渲染窗口大小是多少
	glViewport(0, 0, 800, 600);
	//OPENGL会根据这个大小来转换2d坐标
	//但是我们应该在用户改变窗口大小是给予视图大小的改变
	//对窗口注册回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//循环渲染
	while (!glfwWindowShouldClose(window)) {//如果此窗口没有被关闭
		//在每一帧都会检测按键
		processInput(window);
		//清空窗口现在的内容
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//清屏颜色
		glClear(GL_COLOR_BUFFER_BIT);//缓冲位有GL_COLOR_BUFFER_BIT，GL_DEPTH_BUFFER_BIT和GL_STENCIL_BUFFER_BIT

		glfwSwapBuffers(window);//交换颜色缓冲是一个存放着GLFW窗口每个像素的大缓冲，调用它将缓冲内容绘制
		glfwPollEvents();//检测有没有触发事件如键盘输入、鼠标移动、窗口状态等
	}//当窗口关闭时将会退出循环
	//这是我们的主进程要做的任务将会结束，要释放GLFW的资源，这需要我们调用glfwTerminate
	glfwTerminate();
}