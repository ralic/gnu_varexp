/*
 * Copyright (c) 2002-2010 Peter Simons <simons@cryp.to>
 * Copyright (c) 2001 The OSSP Project <http://www.ossp.org/>
 * Copyright (c) 2001 Cable & Wireless Deutschland <http://www.cw.com/de/>
 *
 * Permission to use, copy, modify, and distribute this software for
 * any purpose with or without fee is hereby granted, provided that
 * the above copyright notice and this permission notice appear in all
 * copies.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHORS AND COPYRIGHT HOLDERS AND THEIR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include "../varexp.hpp"

using namespace varexp;
using namespace std;

struct env_lookup : public callback_t
{
  virtual void operator()(const string& name, string& data)
  {
    const char* p = getenv(name.c_str());
    if (p == NULL)
      throw undefined_variable();
    else
      data = p;
  }
  virtual void operator()(const string& name, int idx, string& data)
  {
    throw array_lookups_are_unsupported();
  }
};

int main(int argc, char** argv)
{
  const char* input1 = "${HOME:o88,}";
  const char* input2 = "${HOME:o88-90}";
  const char* input3 = "${HOME:o8-90}";
  const char* input4 = "${HOME:o8,90}";
  const char* input5 = "${HOME:o8,4}";

  string tmp;
  env_lookup lookup;

  if (setenv("HOME", "/home/regression-tests", 1) !=0)
  {
    printf("Failed to set the environment: %s.\n", strerror(errno));
    return 1;
  }

#define fail_test(input, exception)            \
    try                                        \
    {                                          \
      expand(input, tmp, lookup);              \
      return 1;                                \
    }                                          \
    catch(exception const &)                   \
    {                                          \
    }                                          \
    while(false)

  fail_test(input1, offset_out_of_bounds);
  fail_test(input2, offset_out_of_bounds);
  fail_test(input3, range_out_of_bounds);
  fail_test(input4, range_out_of_bounds);
  fail_test(input5, offset_logic);

  return 0;
}
