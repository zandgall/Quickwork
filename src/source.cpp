#include "qw/quickwork.h"
#include "qw/quickwork_io.h"
#include "qw/quickwork_gl.h"
#include "qw/quickwork_ui.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

int main(int args, char** argv) {
    if (qw::start("Quickwork Example", 1280, 720))// If startup fails, exit with return code -1
        return -1;

    qwio::load_shader_as("res/shaders/shader.shader", "default shader");
    qwio::load_texture_as("res/image.png", "default image");
    qwio::load_font_as("res/fonts/robotomono.ttf", "roboto", 96);

    // Idea? // qwgl::create_texture_2D();

    glUseProgram(qwio::get_loaded_shader("default shader"));

    qwui::text txt = qwui::text("Text Element", "roboto", 24.f);
    txt.setRelativePos(-10, -40);
    txt.setAnchor(qwui::Anchor::right | qwui::Anchor::bottom);
    txt.setScreenAnchor(qwui::Anchor::right | qwui::Anchor::bottom);

    while(!qw::should_close) {
        glViewport(0, 0, qw::width, qw::height);
        glClearColor(0.5, 0.8, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);

        // Print the frame rate of a variety of calculations
        // std::cout << "FPS " << qw::frames_last_second << " : " << qw::one_over_delta_time << " : " << qw::average_frame_rate << " (volatility " << qw::frame_volatility << ")" << std::endl;
    
        // Set the far plane past width*2, so our spinning text doesn't clip
        qwgl::uniform("screenspace", glm::ortho<float>(0.f, qw::width, qw::height, 0.f, 0.f, qw::width*2));

        // Draw "image.png" covering the right-half of the window
        glBindTexture(GL_TEXTURE_2D, qwio::get_loaded_texture("default image"));
        qwgl::uniform("transform", qwgl::rectangle(qw::width / 2.f, 0, qw::width, qw::height));
        qwgl::uniform("transform", qwgl::rectangle(qw::width / 2.f-5.f, 5.f, qw::width/2.f-10.f, qw::height-10.f));
        qwgl::uniform("textured", true);
        qw::draw_square();

        // Draw a line moving along with the mouse, with a changing color using current time
        qwgl::uniform("textured", false);
        double pi = 3.14159265359;
        qwgl::uniform("color", glm::vec4(sin(fmod(glfwGetTime(), pi)), sin(fmod(glfwGetTime()+pi/3, pi)), sin(fmod(glfwGetTime()+2*pi/3, pi)), 1));
        qwgl::uniform("transform", qwgl::line_2d(qw::mouse_position-qw::mouse_velocity, qw::mouse_position, 10.f));
        qw::draw_square();

        // Draw some text, one with right-alignment
        qw::draw_string(qw::last_typed_key, "roboto", 24, qw::width-12, qw::height-12, qw::text::ALIGN_RIGHT);
        qw::draw_string(std::string("MouseLeft: ") + (qw::mouse_left ? "true" : "false"), "roboto", 24, 0, qw::height-60);
        qw::draw_string(std::string("MouseMiddle: ") + (qw::mouse_middle ? "true" : "false"), "roboto", 24, 0, qw::height-36);
        qw::draw_string(std::string("MouseRight: ") + (qw::mouse_right ? "true" : "false"), "roboto", 24, 0, qw::height-12);

        // Create a surface to draw text on. We create a rectangle from (width/4, 24), to (+width/4, +24)
        glm::mat4 spinning_text_surface = qwgl::rectangle(qw::width / 4.f, 24, qw::width / 2.f, 48);
        // We then rotate the surface about the y axis, using the current time as our radians
        spinning_text_surface = glm::rotate<float>(spinning_text_surface, glfwGetTime(), glm::vec3(0, 1, 0));
        // Draw the string "Quickwork Template" on the surface we just created
        qw::draw_string_on("Quickwork Template", "roboto", spinning_text_surface);

        txt.render();

        qw::poll();
    }
}