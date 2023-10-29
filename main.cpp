#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include"shader.h"
#include"object.h"
#include"Project.h"
#include"SpriteRenderer.h"
#include"Texture.h"
#include"stb_image.h"
#include"source.h"
class object
{
private:
    int top;
    int width;
    int height;
    int left;

    
public:
    Texture2D* texture;
    object(const char* texture, int top, int left);
    void Draw(SpriteRenderer& render);

};
float ForceToAc(float force);
float Drag(float dt, float velocity);
float magnus(float verticalVel, float spinning);
class Ball :public object
{
    float radius;
public:
    Ball(const char* Texture, float y, float z, float radius, float sideSpinning, float topSpinning, float leftSpinning, float x_vel, float y_vel, float z_vel);
    float x;
    float y;
    float z;
    float sideSpining;
    float topspinning;
    float leftSpinning;
    float x_vel;
    float y_vel;
    float z_vel;
    bool net;
    void change(float dt);
    void Draw(SpriteRenderer& render);

};
Ball::Ball(const char* Texture, float y, float z,float radius, float sideSpinning, float topSpinning, float leftSpinning, float x_vel, float y_vel, float z_vel) :
    object(Texture, y - radius, z - radius), net{ false }, x{ 0.0f }, y{ y }, z{ z }, radius{ radius }, sideSpining{ sideSpinning }, topspinning{ topSpinning }, leftSpinning{ leftSpinning }, x_vel{ x_vel }, y_vel{ y_vel }, z_vel{ z_vel }
{
}
int changetoin(float distance) {

    return (int)(distance / 2.74 * 376);
}
void Ball::change(float dt)
{
    x_vel = Drag(dt, x_vel);
    y_vel = Drag(dt, y_vel);
    z_vel = Drag(dt, z_vel);
    z_vel -= 9.8 * dt;
    //std::cout <<std::endl<< "dt: " << dt<<std::endl;
    z_vel += magnus(x_vel, topspinning)*dt;
    y_vel -= magnus(x_vel, leftSpinning)*dt;

    x += x_vel * dt;
    y += y_vel * dt;
    z += z_vel * dt;

    if (z <= 0.04) {
        
        if (sideSpining > 0) {
            y_vel += 2 * (1 / (3.1415 / (-0.034 * z_vel + 0.76)) * 0.6 * z_vel);
        }
        z_vel = -0.925 * z_vel;
        z = 0.04;
    }

    if (x >= 1.35 && x <= 1.39) {
        if (z<=0.155) {
            if (!net) {
                std::cout << "net";
                net = true;
            }
            
        }
    }
    


    
}

void Ball::Draw(SpriteRenderer& render)
{
    render.DrawSprite(*this->texture, glm::vec2(changetoin(x ) + 200, changetoin(y) + 50-radius), glm::vec2(this->radius*2, this->radius*2));
    if(550 - changetoin(z) - radius>=250)render.DrawSprite(*this->texture, glm::vec2(changetoin(x )+200,550-changetoin(z)-radius), glm::vec2(this->radius*2, this->radius*2));
    //render.DrawSprite(*this->texture, glm::vec2(200, 50), glm::vec2(3, 3));
}

float magnus(float verticalVel, float spinning) {
    float MF = 0.0000315 * verticalVel * spinning;
    return ForceToAc(MF);
}
;

float Drag(float dt,float velocity) {
    float Drag;
    float original = velocity;
    if (velocity != 0) {
        Drag = 0.00000686 * velocity;
    }
    else Drag = 0;
    velocity -= ForceToAc(Drag) * 0.0003;
    if (velocity * original < 0) return 0;
    else return velocity;
    

}

float ForceToAc(float force) {
    float accleration = force / 0.0027;
    return accleration;
}


object::object(const char* texture1, int top, int left) :top{ top }, left{ left }
{
    this->texture = new Texture2D ();
    int width, height, nrChannels;
    unsigned char* data = stbi_load(texture1, &width, &height, &nrChannels, 0);
    this->width = width;
    this->height = height;
    
    texture->Generate(width, height, data);
    stbi_image_free(data);
    std::cout << texture->ID;


}

void object::Draw(SpriteRenderer& render)
{
    render.DrawSprite(*this->texture, glm::vec2(left, top), glm::vec2(width, height));
}


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //object tabletennisside("table tennis table.jpg",0,0);
    
    //std::cout << ID;
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glm::mat4 trans = glm::ortho(0.0f, 800.0f,  600.0f, 0.0f, -1.0f, 1.0f);
    Project project("vertex.txt", "fragment.txt");
    
    project.shader->Use();
    project.spriteRender->shader.SetMatrix4("projection", trans);
    object tabletennisTable("table tennis table.jpg",50,200);
    object tabletennisside("table tennis side.jpg", 550, 200);
    object net("net.jpg", 529, (376 / 2 + 200 - 1));
    Ball ball("ball.png",0.2,0,3,1,1,1,1,0.1,10);
    float Time = 0;
    float dt = 0;
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.8f, 0.9f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        tabletennisTable.Draw(*project.spriteRender);
        tabletennisside.Draw(*project.spriteRender);

        ball.Draw(*project.spriteRender);
        dt = glfwGetTime()-Time;
        Time = dt + Time;
        //std::cout <<std::endl<< dt << std::endl;
        ball.change(dt);

        net.Draw(*project.spriteRender);
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
