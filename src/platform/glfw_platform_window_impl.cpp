#include "platform_window.h"
#include <GLFW/glfw3.h>
#include <utility>

namespace Mar::Platform {
struct PlatformWindow::Impl {
  GLFWwindow *window;

  using ImplResult = Result<std::unique_ptr<Impl>, WindowErrorDetail>;

  static ImplResult create(uint32_t width, uint32_t height,
                           const std::string &title) {
    if (!glfwInit()) {
      return ImplResult::err(
          {WindowError::InitFailed, "Failed to initialize GLFW"});
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow *win =
        glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!win) {
      glfwTerminate();
      return ImplResult::err(
          {WindowError::CreationFailed, "Failed to create GLFW window"});
    }

    return ImplResult::ok(std::unique_ptr<Impl>(new Impl(win)));
  }

  ~Impl() {
    if (window) {
      glfwDestroyWindow(window);
    }
    glfwTerminate();
  }

private:
  explicit Impl(GLFWwindow *w) : window(w) {}
};


PlatformWindow::PlatformWindow(PlatformWindow &&) noexcept = default;
PlatformWindow &PlatformWindow::operator=(PlatformWindow &&) noexcept = default;
PlatformWindow::~PlatformWindow() = default;

PlatformWindow::PlatformWindow(std::unique_ptr<Impl> impl)
    : impl_(std::move(impl)) {}

PlatformWindow::WindowResult PlatformWindow::create(uint32_t width,
                                                    uint32_t height,
                                                    const std::string &title) {
  auto impl_result = Impl::create(width, height, title);

  if (impl_result.is_err()) {
    return Result<PlatformWindow, WindowErrorDetail>::err(
        std::move(impl_result.error()));
  }

  return Result<PlatformWindow, WindowErrorDetail>::ok(
      PlatformWindow(std::move(impl_result.unwrap())));
}

void PlatformWindow::poll_events() const { glfwPollEvents(); }

bool PlatformWindow::should_close() const {
  return glfwWindowShouldClose(impl_->window);
}

} // namespace Mar::Platform
