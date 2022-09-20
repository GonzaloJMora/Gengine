#include "GraphicsManager.h"
#include "spdlog/spdlog.h"
#include "ResourceManager.h"

#define SOKOL_IMPL
#define SOKOL_GLCORE33
#include "sokol_gfx.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace glm;

Resource::ResourceManager r;

void Graphics::GraphicsManager::GStartup(int window_width, int window_height, Foo::string window_name, bool window_fullscreen) {
	glfwInit();
	// We'll use sokol_gfx's OpenGL backend
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	GLFWwindow* window = glfwCreateWindow( window_width, window_height, window_name.c_str(), window_fullscreen ? glfwGetPrimaryMonitor() : 0, 0 );
	glfwSetWindowAspectRatio( window, window_width, window_height );
	w = window;

	if( !window ) {
		spdlog::error("Failed to create a window.");
 		glfwTerminate();
	}

	glfwMakeContextCurrent( window );
	glfwSwapInterval(1);

	sg_setup(sg_desc{});

	const float vertices[] = {
		// positions      // texcoords
		-1.0f,  -1.0f,    0.0f,  0.0f,
		 1.0f,  -1.0f,    1.0f,  0.0f,
		-1.0f,   1.0f,    0.0f,  1.0f,
		 1.0f,   1.0f,    1.0f,  1.0f,
	};

	sg_buffer_desc buffer_desc{};
	buffer_desc.data = SG_RANGE(vertices);
	sg_buffer vertex_buffer = sg_make_buffer(buffer_desc);

	sg_pipeline_desc pipeline_desc{};
	pipeline_desc.primitive_type = SG_PRIMITIVETYPE_TRIANGLE_STRIP;
	pipeline_desc.colors[0].blend.enabled = true;
	pipeline_desc.colors[0].blend.src_factor_rgb = SG_BLENDFACTOR_SRC_ALPHA;
	pipeline_desc.colors[0].blend.dst_factor_rgb = SG_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
	pipeline_desc.depth.compare = SG_COMPAREFUNC_LESS_EQUAL;
	pipeline_desc.depth.write_enabled = true;
	pipeline_desc.layout.attrs[0].format = SG_VERTEXFORMAT_FLOAT2;
	pipeline_desc.layout.attrs[1].format = SG_VERTEXFORMAT_FLOAT2;

	sg_shader_desc shader_desc{};
	shader_desc.vs.source = R"(
    #version 330
    uniform mat4 projection;
    uniform mat4 transform;
    layout(location=0) in vec2 position;
    layout(location=1) in vec2 texcoords0;
    out vec2 texcoords;
    void main() {
        gl_Position = projection*transform*vec4( position, 0.0, 1.0 );
        texcoords = texcoords0;
    })";
	shader_desc.vs.uniform_blocks[0].size = sizeof(Uniforms);
	// The order of `.uniforms[0]` and `.uniforms[1]` must match the order in `Uniforms`
	shader_desc.vs.uniform_blocks[0].uniforms[0].name = "projection";
	shader_desc.vs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_MAT4;
	shader_desc.vs.uniform_blocks[0].uniforms[1].name = "transform";
	shader_desc.vs.uniform_blocks[0].uniforms[1].type = SG_UNIFORMTYPE_MAT4;

	shader_desc.fs.source = R"(
    #version 330
    uniform sampler2D tex;
    in vec2 texcoords;
    out vec4 frag_color;
    void main() {
        frag_color = texture( tex, texcoords );
        // If we're not drawing back to front, discard very transparent pixels so we
        // don't write to the depth buffer and prevent farther sprites from drawing.
        if( frag_color.a < 0.1 ) discard;
    }
)";
	shader_desc.fs.images[0].name = "tex"; // The name should match the shader source code.
	shader_desc.fs.images[0].image_type = SG_IMAGETYPE_2D;

	pipeline_desc.shader = sg_make_shader(shader_desc);
	sg_pipeline pipeline = sg_make_pipeline(pipeline_desc);

	sg_pass_action pass_action{};
	pass_action.colors[0].action = SG_ACTION_CLEAR;
	pass_action.colors[0].value = { /* red, green, blue, alpha floating point values for a color to fill the frame buffer with */ };

	sg_bindings bindings{};
	bindings.vertex_buffers[0] = vertex_buffer;

	Graphics::GraphicsManager::pass_act = pass_action;
	Graphics::GraphicsManager::pip = pipeline;
	Graphics::GraphicsManager::bindings = bindings;
	Graphics::GraphicsManager::wid = window_width;
	Graphics::GraphicsManager::hei = window_height;
}

void Graphics::GraphicsManager::GShutdown() {
	sg_shutdown();
	glfwTerminate();
}

void Graphics::GraphicsManager::Draw(const std::string& name) {
	glfwGetFramebufferSize(w, &wid, &hei);
	sg_begin_default_pass(pass_act, wid, hei);

	sg_apply_pipeline(pip);

	uniforms = Uniforms{};
	uniforms.projection = mat4{ 1 };
	uniforms.projection[0][0] = uniforms.projection[1][1] = 1. / 100.;

	int width = imageMap[name].width;
	int height = imageMap[name].height;

	if (wid < hei) {
		uniforms.projection[1][1] *= wid;
		uniforms.projection[1][1] /= hei;
	}
	else {
		uniforms.projection[0][0] *= hei;
		uniforms.projection[0][0] /= wid;
	}

	sg_image im = imageMap[name].image;

	uniforms.transform = translate(mat4{1}, vec3(0, 0, 0)) * rotate(mat4{ 1.0 }, glm::radians(180.0f), vec3(0, 0, 1)) * scale(mat4{1}, vec3(width / 6, height / 5, 1));
	if (wid < width) {
		uniforms.transform = uniforms.transform * scale(mat4{ 1 }, vec3(Foo::real(width) / height, 1.0, 1.0));
	}
	else {
		uniforms.transform = uniforms.transform * scale(mat4{ 1 }, vec3(1.0, Foo::real(height) / width, 1.0));
	}
	sg_apply_uniforms(SG_SHADERSTAGE_VS, 0, SG_RANGE(uniforms));

	bindings.fs_images[0] = imageMap[name].image;
	sg_apply_bindings(bindings);

	sg_draw(0, 4, 1);
	sg_end_pass();
	sg_commit();
	glfwSwapBuffers(w);
}

void Graphics::GraphicsManager::loadImage(const std::string& name, const std::string& path) {
	int width, height, channels;
	unsigned char* data = stbi_load(r.resolvePath(path).c_str(), &width, &height, &channels, 4);

	sg_image_desc image_desc{};
	image_desc.width = width;
	image_desc.height = height;
	image_desc.pixel_format = SG_PIXELFORMAT_RGBA8;
	image_desc.min_filter = SG_FILTER_LINEAR;
	image_desc.mag_filter = SG_FILTER_LINEAR;
	image_desc.wrap_u = SG_WRAP_CLAMP_TO_EDGE;
	image_desc.wrap_v = SG_WRAP_CLAMP_TO_EDGE;
	image_desc.data.subimage[0][0].ptr = data;
	image_desc.data.subimage[0][0].size = (size_t)(width * height * 4);

	sg_image image = sg_make_image(image_desc);

	Graphics::Image im{};
	im.width = width;
	im.height = height;
	im.image = image;
	imageMap[name] = im;

	stbi_image_free(data);
}

void Graphics::GraphicsManager::destroyImage(const std::string& name) {
	if (imageMap.count(name) != 0) {
		sg_destroy_image(imageMap[name].image);
		imageMap.erase(name);
	}
	else {
		spdlog::info("name to delete doesn't exist");
	}
}

