/* Copyright Joyent, Inc. and other Node contributors. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "uv.h"
#include "task.h"


static uv_timer_t timer_handle;
static uv_idle_t idle_handle;

static int idle_cb_called = 0;
static int timer_cb_called = 0;
static int close_cb_called = 0;


static void close_cb(uv_handle_t* handle) {
  close_cb_called++;
}


static void timer_cb(uv_timer_t* handle, int status) {
  ASSERT(handle == &timer_handle);
  ASSERT(status == 0);

  uv_close((uv_handle_t*) &idle_handle, close_cb);
  uv_close((uv_handle_t*) &timer_handle, close_cb);

  timer_cb_called++;
  LOGF("timer_cb %d\n", timer_cb_called);
}


static void idle_cb(uv_idle_t* handle, int status) {
  ASSERT(handle == &idle_handle);
  ASSERT(status == 0);

  idle_cb_called++;
  LOGF("idle_cb %d\n", idle_cb_called);
}


TEST_IMPL(idle_starvation) {
  int r;

  r = uv_idle_init(uv_default_loop(), &idle_handle);
  ASSERT(r == 0);
  r = uv_idle_start(&idle_handle, idle_cb);
  ASSERT(r == 0);

  r = uv_timer_init(uv_default_loop(), &timer_handle);
  ASSERT(r == 0);
  r = uv_timer_start(&timer_handle, timer_cb, 50, 0);
  ASSERT(r == 0);

  r = uv_run(uv_default_loop());
  ASSERT(r == 0);

  ASSERT(idle_cb_called > 0);
  ASSERT(timer_cb_called == 1);
  ASSERT(close_cb_called == 2);

  MAKE_VALGRIND_HAPPY();
  return 0;
}
