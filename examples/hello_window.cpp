#include <cstdlib>
#include <platform/platform_window.h>

int main() {
  auto result =
      Mar::Platform::PlatformWindow::create(800, 600, "Hello Window!");

  if (result.is_err()) {
    return EXIT_FAILURE;
  }

  auto window = std::move(result.unwrap());

  while (!window.should_close()) {
    window.poll_events();
  }

  return EXIT_SUCCESS;
}
