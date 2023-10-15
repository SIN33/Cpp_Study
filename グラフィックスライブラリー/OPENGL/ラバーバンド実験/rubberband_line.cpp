#include <GLFW/glfw3.h>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(500, 400, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    float st_pos_x = 0.0f;
    float st_pos_y = 0.0f;

    float pos_x = 0.0f;
    float pos_y = 0.0f;


   /* glDrawBuffer(GL_FRONT);

    glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_LOGIC_OP);
	glLogicOp(GL_XOR);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/

	// 「ビューポート 変換」 を 指定
		// 画面 左 下 からの 座標( X, Y) から、
		// (幅 x 高 さ) ピクセル の 領域 を 描画 領域 と する
	glViewport(0, 0, 500, 400);
	 //「投影 行列」 を 操作 対象 に する
	glMatrixMode(GL_PROJECTION);
	// 単位 行列 を 読み込む よう に 指示
	glLoadIdentity();

	// 正 投影 行列 を 作り、 現在 の 行列 に 掛け合わ せる 
	// glOrtho( 左 X 座標, 右 X 座標, 下 Y 座標, 上 Y 座標, // 手前 Z 座標, 奥 Z 座標)
	glOrtho(0.0f, 500.0f, 400.0f, 0.0f, -1.0f, 1.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {


        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            break;
        }

        if (glfwGetKey(window, 'A') == GLFW_PRESS)
        {
           pos_x -= 2.0f;
        }

        if (glfwGetKey(window, 'D') == GLFW_PRESS)
        {
            pos_x +=2.0f;
        }

        if (glfwGetKey(window, 'W') == GLFW_PRESS)
        {
            pos_y -=2.0f;
        }

        if (glfwGetKey(window, 'S') == GLFW_PRESS)
        {
            pos_y += 2.0f;
        }

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {

            double mouse_x, mouse_y;

            glfwGetCursorPos(window, &mouse_x, &mouse_y);

            // マウス の 座標( 0, 0)〜( 639, 479) を // スクリーン 座標(- 1, -1)〜( 1, 1) に 変換 
            st_pos_x = (int)mouse_x;
            st_pos_y = (int)mouse_y;

        }

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        {

            double mouse_x, mouse_y;

            glfwGetCursorPos(window, &mouse_x, &mouse_y);

            // マウス の 座標( 0, 0)〜( 639, 479) を // スクリーン 座標(- 1, -1)〜( 1, 1) に 変換 
            pos_x = (int)mouse_x;
            pos_y = (int)mouse_y;

        }

        //描画バッファ塗りつぶし
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        const GLfloat vtx[] = {
            st_pos_x,
            st_pos_y,
            pos_x,
            pos_y,
        };


		glVertexPointer(2, GL_FLOAT, 0, vtx);
		glPointSize(5.0f);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);


        glEnableClientState(GL_VERTEX_ARRAY);

        glDrawArrays(GL_LINES, 0, 2);

        // 描画 が 終わっ たら 描画 モード を 元 に 戻す
        glDisableClientState(GL_VERTEX_ARRAY);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}