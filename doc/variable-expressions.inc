<!--
   Copyright (c) 2002-2010 Peter Simons <simons@cryp.to>
   Copyright (c) 2001 The OSSP Project <http://www.ossp.org/>
   Copyright (c) 2001 Cable & Wireless Deutschland <http://www.cw.com/de/>

   Permission to use, copy, modify, and distribute this software for any purpose
   with or without fee is hereby granted, provided that the above copyright
   notice and this permission notice appear in all copies.

   THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED WARRANTIES,
   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
   FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
   AUTHORS AND COPYRIGHT HOLDERS AND THEIR CONTRIBUTORS BE LIABLE FOR ANY
   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
-->

  <para>&varexp; distinguishes variables into simple and complex
expressions. A simple expression has the form <quote>$NAME</quote> and will
basically only replace the variable in the text buffer with its contents.
Complex expressions have the form
<quote>${NAME:operation1:operation2:&hellip;}</quote> and may perform various
operations on the variable's contents before inserting it into the text
buffer.</para>

  <para>Please note that due to the way simple expressions are parsed, it may
not always be possible to use the simple-expression form even though you do not
want to perform any operations. If your input text was <quote>This is a
$FOObar</quote>, but the last <quote>bar</quote> part is meant to be a literal
string, you'd have use <quote>This is a ${FOO}bar</quote>, because the parser
will interpret any valid variable-name character following the dollar as part of
the variable name; it will not recognize that <quote>$FOO</quote> would exist
while <quote>$FOObar</quote> would not.</para>

  <para>Also, &varexp; does not distinguish case in any way. For the library,
<quote>$FoObAr</quote> and <quote>$fOoBaR</quote> are just strings -- whether
they refer to the same variable or not is entirely up to the application that
provides the callback used to resolve variables to their contents.</para>

  <para>If you want to enter a text like <quote>$foo</quote> literally, you'll
have to escape the <quote>$</quote> sign by prefacing it with a backslash:
<quote>\$foo</quote>. Then &varexp; won't interpret this expression as a
variable.</para>

<!--
Local Variables:
mode: xml
fill-column:80
End:
-->
