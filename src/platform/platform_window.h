#pragma once

#include "core/result.h"
#include <cstdint>
#include <memory>
#include <string>

namespace Mar::Platform {

/**
 * @enum WindowError
 * @brief High‐level error codes for window creation and management.
 */
enum class WindowError {
  InitFailed,          ///< Failed to initialize the windowing backend
  BackendNotSupported, ///< Requested backend isn’t available on this platform
  CreationFailed,      ///< Failed to create the window
  UnknownError,        ///< An unknown error occurred
};

/**
 * @struct WindowErrorDetail
 * @brief Detailed error information, pairing an error code with a message.
 */
struct WindowErrorDetail {
  WindowError code;    ///< The high-level error code
  std::string message; ///< Human-readable error description
};

/**
 * @class PlatformWindow
 * @brief Cross-platform window abstraction (Pimpl + RAII).
 */
class PlatformWindow {
public:
  /// Result type returned by create(): either a valid window or an error.
  using WindowResult = Result<PlatformWindow, WindowErrorDetail>;

  /**
   * @brief Factory: create a new window.
   * @param width  Width in pixels.
   * @param height Height in pixels.
   * @param title  Window title string.
   * @return WindowResult containing either the constructed PlatformWindow or a
   * WindowErrorDetail.
   */
  static WindowResult create(uint32_t width, uint32_t height,
                             const std::string &title);

  /**
   * @brief Move‐constructor transfers ownership.
   */
  PlatformWindow(PlatformWindow &&) noexcept;

  /**
   * @brief Move‐assignment transfers ownership.
   */
  PlatformWindow &operator=(PlatformWindow &&) noexcept;

  /**
   * @brief Destructor — cleans up the underlying window and terminates backend.
   */
  ~PlatformWindow();

  PlatformWindow(const PlatformWindow &) = delete; ///< copy‐ctor deleted
  PlatformWindow &
  operator=(const PlatformWindow &) = delete; ///< copy-assign deleted

  /**
   * @brief Process pending windowing events.
   *
   * Typically called once per frame to pump the event loop.
   */
  void poll_events() const;

  /**
   * @brief Check whether the user has requested the window to close.
   * @return true if the window should close.
   */
  bool should_close() const;

private:
  struct Impl;
  std::unique_ptr<Impl> impl_; ///< Pimpl to hide backend implementation

  /**
   * @brief Private ctor used by create().
   * @param impl  Unique pointer to an initialized Impl.
   */
  explicit PlatformWindow(std::unique_ptr<Impl> impl);
};

} // namespace Mar::Platform
