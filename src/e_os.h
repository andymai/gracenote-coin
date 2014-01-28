<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>e_os.h</title>
<style type="text/css">
.enscript-comment { font-style: italic; color: rgb(178,34,34); }
.enscript-function-name { font-weight: bold; color: rgb(0,0,255); }
.enscript-variable-name { font-weight: bold; color: rgb(184,134,11); }
.enscript-keyword { font-weight: bold; color: rgb(160,32,240); }
.enscript-reference { font-weight: bold; color: rgb(95,158,160); }
.enscript-string { font-weight: bold; color: rgb(188,143,143); }
.enscript-builtin { font-weight: bold; color: rgb(218,112,214); }
.enscript-type { font-weight: bold; color: rgb(34,139,34); }
.enscript-highlight { text-decoration: underline; color: 0; }
</style>
</head>
<body id="top">
<h1 style="margin:8px;" id="f1">e_os.h&nbsp;&nbsp;&nbsp;<span style="font-weight: normal; font-size: 0.5em;">[<a href="?txt">plain text</a>]</span></h1>
<hr/>
<div></div>
<pre>
<span class="enscript-comment">/* e_os.h */</span>
<span class="enscript-comment">/* Copyright (C) 1995-1998 Eric Young (<a href="mailto:eay@cryptsoft.com">eay@cryptsoft.com</a>)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (<a href="mailto:eay@cryptsoft.com">eay@cryptsoft.com</a>).
 * The implementation was written so as to conform with Netscapes SSL.
 * 
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (<a href="mailto:tjh@cryptsoft.com">tjh@cryptsoft.com</a>).
 * 
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    &quot;This product includes cryptographic software written by
 *     Eric Young (<a href="mailto:eay@cryptsoft.com">eay@cryptsoft.com</a>)&quot;
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from 
 *    the apps directory (application code) you must include an acknowledgement:
 *    &quot;This product includes software written by Tim Hudson (<a href="mailto:tjh@cryptsoft.com">tjh@cryptsoft.com</a>)&quot;
 * 
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * 
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */</span>

#<span class="enscript-reference">ifndef</span> <span class="enscript-variable-name">HEADER_E_OS_H</span>
#<span class="enscript-reference">define</span> <span class="enscript-variable-name">HEADER_E_OS_H</span>

#<span class="enscript-reference">include</span> <span class="enscript-string">&lt;openssl/opensslconf.h&gt;</span>

#<span class="enscript-reference">include</span> <span class="enscript-string">&lt;openssl/e_os2.h&gt;</span>
<span class="enscript-comment">/* &lt;openssl/e_os2.h&gt; contains what we can justify to make visible
 * to the outside; this file e_os.h is not part of the exported
 * interface. */</span>

#<span class="enscript-reference">ifdef</span>  <span class="enscript-variable-name">__cplusplus</span>
<span class="enscript-type">extern</span> <span class="enscript-string">&quot;C&quot;</span> {
#<span class="enscript-reference">endif</span>

<span class="enscript-comment">/* Used to checking reference counts, most while doing perl5 stuff :-) */</span>
#<span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">REF_PRINT</span>
#<span class="enscript-reference">undef</span> <span class="enscript-variable-name">REF_PRINT</span>
#<span class="enscript-reference">define</span> <span class="enscript-function-name">REF_PRINT</span>(a,b)	fprintf(stderr,<span class="enscript-string">&quot;%08X:%4d:%s\n&quot;</span>,(int)b,b-&gt;references,a)
#<span class="enscript-reference">endif</span>

#<span class="enscript-reference">ifndef</span> <span class="enscript-variable-name">DEVRANDOM</span>
<span class="enscript-comment">/* set this to your 'random' device if you have one.
 * My default, we will try to read this file */</span>
#<span class="enscript-reference">define</span> <span class="enscript-variable-name">DEVRANDOM</span> <span class="enscript-string">&quot;/dev/urandom&quot;</span>
#<span class="enscript-reference">endif</span>

#<span class="enscript-reference">if</span> <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">VXWORKS</span>)
#  <span class="enscript-reference">define</span> <span class="enscript-variable-name">NO_SYS_PARAM_H</span>
#  <span class="enscript-reference">define</span> <span class="enscript-variable-name">NO_CHMOD</span>
#  <span class="enscript-reference">define</span> <span class="enscript-variable-name">NO_SYSLOG</span>
#<span class="enscript-reference">endif</span>
  
#<span class="enscript-reference">if</span> <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">__MWERKS__</span>) &amp;&amp; <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">macintosh</span>)
# <span class="enscript-reference">if</span> <span class="enscript-variable-name">macintosh</span>==1
#  <span class="enscript-reference">ifndef</span> <span class="enscript-variable-name">MAC_OS_GUSI_SOURCE</span>
#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">MAC_OS_pre_X</span>
#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">NO_SYS_TYPES_H</span>
     <span class="enscript-type">typedef</span> <span class="enscript-type">long</span> ssize_t;
#  <span class="enscript-reference">endif</span>
#  <span class="enscript-reference">define</span> <span class="enscript-variable-name">NO_SYS_PARAM_H</span>
#  <span class="enscript-reference">define</span> <span class="enscript-variable-name">NO_CHMOD</span>
#  <span class="enscript-reference">define</span> <span class="enscript-variable-name">NO_SYSLOG</span>
#  <span class="enscript-reference">undef</span>  <span class="enscript-variable-name">DEVRANDOM</span>
#  <span class="enscript-reference">define</span> <span class="enscript-variable-name">GETPID_IS_MEANINGLESS</span>
# <span class="enscript-reference">endif</span>
#<span class="enscript-reference">endif</span>

<span class="enscript-comment">/********************************************************************
 The Microsoft section
 ********************************************************************/</span>
<span class="enscript-comment">/* The following is used becaue of the small stack in some
 * Microsoft operating systems */</span>
#<span class="enscript-reference">if</span> <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">WIN16</span>) || <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">MSDOS</span>)
#  <span class="enscript-reference">define</span> <span class="enscript-variable-name">MS_STATIC</span>	static
#<span class="enscript-reference">else</span>
#  <span class="enscript-reference">define</span> <span class="enscript-variable-name">MS_STATIC</span>
#<span class="enscript-reference">endif</span>

#<span class="enscript-reference">if</span> <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">_WIN32</span>) &amp;&amp; !<span class="enscript-reference">defined</span>(<span class="enscript-variable-name">WIN32</span>) &amp;&amp; !<span class="enscript-reference">defined</span>(<span class="enscript-variable-name">__CYGWIN32__</span>) &amp;&amp; !<span class="enscript-reference">defined</span>(<span class="enscript-variable-name">_UWIN</span>)
#  <span class="enscript-reference">define</span> <span class="enscript-variable-name">WIN32</span>
#<span class="enscript-reference">endif</span>

#<span class="enscript-reference">if</span> (<span class="enscript-reference">defined</span>(<span class="enscript-variable-name">WIN32</span>) || <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">WIN16</span>)) &amp;&amp; !<span class="enscript-reference">defined</span>(<span class="enscript-variable-name">__CYGWIN32__</span>) &amp;&amp; !<span class="enscript-reference">defined</span>(<span class="enscript-variable-name">_UWIN</span>)
#  <span class="enscript-reference">ifndef</span> <span class="enscript-variable-name">WINDOWS</span>
#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">WINDOWS</span>
#  <span class="enscript-reference">endif</span>
#  <span class="enscript-reference">ifndef</span> <span class="enscript-variable-name">MSDOS</span>
#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">MSDOS</span>
#  <span class="enscript-reference">endif</span>
#<span class="enscript-reference">endif</span>

#<span class="enscript-reference">if</span> <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">MSDOS</span>) &amp;&amp; !<span class="enscript-reference">defined</span>(<span class="enscript-variable-name">GETPID_IS_MEANINGLESS</span>)
#  <span class="enscript-reference">define</span> <span class="enscript-variable-name">GETPID_IS_MEANINGLESS</span>
#<span class="enscript-reference">endif</span>

#<span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">WIN32</span>
#<span class="enscript-reference">define</span> <span class="enscript-function-name">get_last_sys_error</span>()	GetLastError()
#<span class="enscript-reference">define</span> <span class="enscript-function-name">clear_sys_error</span>()	SetLastError(0)
#<span class="enscript-reference">if</span> !<span class="enscript-reference">defined</span>(<span class="enscript-variable-name">WINNT</span>)
#<span class="enscript-reference">define</span> <span class="enscript-variable-name">WIN_CONSOLE_BUG</span>
#<span class="enscript-reference">endif</span>
#<span class="enscript-reference">else</span>
#<span class="enscript-reference">define</span> <span class="enscript-function-name">get_last_sys_error</span>()	errno
#<span class="enscript-reference">define</span> <span class="enscript-function-name">clear_sys_error</span>()	errno=0
#<span class="enscript-reference">endif</span>

#<span class="enscript-reference">if</span> <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">WINDOWS</span>) &amp;&amp; !<span class="enscript-reference">defined</span>(<span class="enscript-variable-name">__CYGWIN32__</span>)  &amp;&amp; !<span class="enscript-reference">defined</span>(<span class="enscript-variable-name">_UWIN</span>)

#<span class="enscript-reference">define</span> <span class="enscript-function-name">get_last_socket_error</span>()	WSAGetLastError()
#<span class="enscript-reference">define</span> <span class="enscript-function-name">clear_socket_error</span>()	WSASetLastError(0)
#<span class="enscript-reference">define</span> <span class="enscript-function-name">readsocket</span>(s,b,n)	recv((s),(b),(n),0)
#<span class="enscript-reference">define</span> <span class="enscript-function-name">writesocket</span>(s,b,n)	send((s),(b),(n),0)
#<span class="enscript-reference">define</span> <span class="enscript-variable-name">EADDRINUSE</span>		WSAEADDRINUSE
#<span class="enscript-reference">elif</span> <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">MAC_OS_pre_X</span>)
#<span class="enscript-reference">define</span> <span class="enscript-function-name">get_last_socket_error</span>()	errno
#<span class="enscript-reference">define</span> <span class="enscript-function-name">clear_socket_error</span>()	errno=0
#<span class="enscript-reference">define</span> <span class="enscript-function-name">closesocket</span>(s)		MacSocket_close(s)
#<span class="enscript-reference">define</span> <span class="enscript-function-name">readsocket</span>(s,b,n)	MacSocket_recv((s),(b),(n),true)
#<span class="enscript-reference">define</span> <span class="enscript-function-name">writesocket</span>(s,b,n)	MacSocket_send((s),(b),(n))
#<span class="enscript-reference">elif</span> <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">VMS</span>)
#<span class="enscript-reference">define</span> <span class="enscript-function-name">get_last_socket_error</span>() errno
#<span class="enscript-reference">define</span> <span class="enscript-function-name">clear_socket_error</span>()    errno=0
#<span class="enscript-reference">define</span> <span class="enscript-function-name">ioctlsocket</span>(a,b,c)      ioctl(a,b,c)
#<span class="enscript-reference">define</span> <span class="enscript-function-name">closesocket</span>(s)          close(s)
#<span class="enscript-reference">define</span> <span class="enscript-function-name">readsocket</span>(s,b,n)       recv((s),(b),(n),0)
#<span class="enscript-reference">define</span> <span class="enscript-function-name">writesocket</span>(s,b,n)      send((s),(b),(n),0)
#<span class="enscript-reference">else</span>
#<span class="enscript-reference">define</span> <span class="enscript-function-name">get_last_socket_error</span>()	errno
#<span class="enscript-reference">define</span> <span class="enscript-function-name">clear_socket_error</span>()	errno=0
#<span class="enscript-reference">define</span> <span class="enscript-function-name">ioctlsocket</span>(a,b,c)	ioctl(a,b,c)
#<span class="enscript-reference">define</span> <span class="enscript-function-name">closesocket</span>(s)		close(s)
#<span class="enscript-reference">define</span> <span class="enscript-function-name">readsocket</span>(s,b,n)	read((s),(b),(n))
#<span class="enscript-reference">define</span> <span class="enscript-function-name">writesocket</span>(s,b,n)	write((s),(b),(n))
#<span class="enscript-reference">endif</span>

#<span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">WIN16</span>
#  <span class="enscript-reference">define</span> <span class="enscript-variable-name">NO_FP_API</span>
#  <span class="enscript-reference">define</span> <span class="enscript-variable-name">MS_CALLBACK</span>	_far _loadds
#  <span class="enscript-reference">define</span> <span class="enscript-variable-name">MS_FAR</span>	_far
#<span class="enscript-reference">else</span>
#  <span class="enscript-reference">define</span> <span class="enscript-variable-name">MS_CALLBACK</span>
#  <span class="enscript-reference">define</span> <span class="enscript-variable-name">MS_FAR</span>
#<span class="enscript-reference">endif</span>

#<span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">NO_STDIO</span>
#  <span class="enscript-reference">define</span> <span class="enscript-variable-name">NO_FP_API</span>
#<span class="enscript-reference">endif</span>

#<span class="enscript-reference">if</span> (<span class="enscript-reference">defined</span>(<span class="enscript-variable-name">WINDOWS</span>) || <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">MSDOS</span>)) &amp;&amp; !<span class="enscript-reference">defined</span>(<span class="enscript-variable-name">__CYGWIN32__</span>) &amp;&amp; !<span class="enscript-reference">defined</span>(<span class="enscript-variable-name">_UWIN</span>)

#  <span class="enscript-reference">ifndef</span> <span class="enscript-variable-name">S_IFDIR</span>
#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">S_IFDIR</span>	_S_IFDIR
#  <span class="enscript-reference">endif</span>

#  <span class="enscript-reference">ifndef</span> <span class="enscript-variable-name">S_IFMT</span>
#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">S_IFMT</span>	_S_IFMT
#  <span class="enscript-reference">endif</span>

#  <span class="enscript-reference">if</span> !<span class="enscript-reference">defined</span>(<span class="enscript-variable-name">WINNT</span>)
#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">NO_SYSLOG</span>
#  <span class="enscript-reference">endif</span>
#  <span class="enscript-reference">define</span> <span class="enscript-variable-name">NO_DIRENT</span>

#  <span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">WINDOWS</span>
#    <span class="enscript-reference">include</span> <span class="enscript-string">&lt;windows.h&gt;</span>
#    <span class="enscript-reference">include</span> <span class="enscript-string">&lt;stddef.h&gt;</span>
#    <span class="enscript-reference">include</span> <span class="enscript-string">&lt;errno.h&gt;</span>
#    <span class="enscript-reference">include</span> <span class="enscript-string">&lt;string.h&gt;</span>
#    <span class="enscript-reference">include</span> <span class="enscript-string">&lt;malloc.h&gt;</span>
#  <span class="enscript-reference">endif</span>
#  <span class="enscript-reference">include</span> <span class="enscript-string">&lt;io.h&gt;</span>
#  <span class="enscript-reference">include</span> <span class="enscript-string">&lt;fcntl.h&gt;</span>

#  <span class="enscript-reference">define</span> <span class="enscript-variable-name">ssize_t</span> long

#  <span class="enscript-reference">if</span> <span class="enscript-variable-name">defined</span> (<span class="enscript-variable-name">__BORLANDC__</span>)
#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">_setmode</span> setmode
#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">_O_TEXT</span> O_TEXT
#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">_O_BINARY</span> O_BINARY
#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">_int64</span> __int64
#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">_kbhit</span> kbhit
#  <span class="enscript-reference">endif</span>

#  <span class="enscript-reference">if</span> <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">WIN16</span>) &amp;&amp; <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">SSLEAY</span>) &amp;&amp; <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">_WINEXITNOPERSIST</span>)
#    <span class="enscript-reference">define</span> <span class="enscript-function-name">EXIT</span>(n) _wsetexit(_WINEXITNOPERSIST)
#    <span class="enscript-reference">define</span> <span class="enscript-function-name">OPENSSL_EXIT</span>(n) do { if (n == 0) EXIT(n); return(n); } while(0)
#  <span class="enscript-reference">else</span>
#    <span class="enscript-reference">define</span> <span class="enscript-function-name">EXIT</span>(n) return(n)
#  <span class="enscript-reference">endif</span>
#  <span class="enscript-reference">define</span> <span class="enscript-variable-name">LIST_SEPARATOR_CHAR</span> <span class="enscript-string">';'</span>
#  <span class="enscript-reference">ifndef</span> <span class="enscript-variable-name">X_OK</span>
#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">X_OK</span>	0
#  <span class="enscript-reference">endif</span>
#  <span class="enscript-reference">ifndef</span> <span class="enscript-variable-name">W_OK</span>
#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">W_OK</span>	2
#  <span class="enscript-reference">endif</span>
#  <span class="enscript-reference">ifndef</span> <span class="enscript-variable-name">R_OK</span>
#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">R_OK</span>	4
#  <span class="enscript-reference">endif</span>
#  <span class="enscript-reference">define</span> <span class="enscript-variable-name">OPENSSL_CONF</span>	<span class="enscript-string">&quot;openssl.cnf&quot;</span>
#  <span class="enscript-reference">define</span> <span class="enscript-variable-name">SSLEAY_CONF</span>	OPENSSL_CONF
#  <span class="enscript-reference">define</span> <span class="enscript-variable-name">NUL_DEV</span>	<span class="enscript-string">&quot;nul&quot;</span>
#  <span class="enscript-reference">define</span> <span class="enscript-variable-name">RFILE</span>		<span class="enscript-string">&quot;.rnd&quot;</span>
#  <span class="enscript-reference">define</span> <span class="enscript-variable-name">DEFAULT_HOME</span>  <span class="enscript-string">&quot;C:&quot;</span>

#<span class="enscript-reference">else</span> <span class="enscript-comment">/* The non-microsoft world world */</span>

#  <span class="enscript-reference">if</span> <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">__VMS</span>) &amp;&amp; !<span class="enscript-reference">defined</span>(<span class="enscript-variable-name">VMS</span>)
#  <span class="enscript-reference">define</span> <span class="enscript-variable-name">VMS</span> 1
#  <span class="enscript-reference">endif</span>

#  <span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">VMS</span>
  <span class="enscript-comment">/* some programs don't include stdlib, so exit() and others give implicit 
     function warnings */</span>
#    <span class="enscript-reference">include</span> <span class="enscript-string">&lt;stdlib.h&gt;</span>
#    <span class="enscript-reference">if</span> <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">__DECC</span>)
#      <span class="enscript-reference">include</span> <span class="enscript-string">&lt;unistd.h&gt;</span>
#    <span class="enscript-reference">else</span>
#      <span class="enscript-reference">include</span> <span class="enscript-string">&lt;unixlib.h&gt;</span>
#    <span class="enscript-reference">endif</span>
#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">OPENSSL_CONF</span>	<span class="enscript-string">&quot;openssl.cnf&quot;</span>
#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">SSLEAY_CONF</span>		OPENSSL_CONF
#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">RFILE</span>		<span class="enscript-string">&quot;.rnd&quot;</span>
#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">LIST_SEPARATOR_CHAR</span> <span class="enscript-string">','</span>
#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">NUL_DEV</span>		<span class="enscript-string">&quot;NLA0:&quot;</span>
  <span class="enscript-comment">/* We need to do this since VMS has the following coding on status codes:

     Bits 0-2: status type: 0 = warning, 1 = success, 2 = error, 3 = info ...
               The important thing to know is that odd numbers are considered
	       good, while even ones are considered errors.
     Bits 3-15: actual status number
     Bits 16-27: facility number.  0 is considered &quot;unknown&quot;
     Bits 28-31: control bits.  If bit 28 is set, the shell won't try to
                 output the message (which, for random codes, just looks ugly)

     So, what we do here is to change 0 to 1 to get the default success status,
     and everything else is shifted up to fit into the status number field, and
     the status is tagged as an error, which I believe is what is wanted here.
     -- Richard Levitte
  */</span>
#    <span class="enscript-reference">define</span> <span class="enscript-function-name">EXIT</span>(n)		do { int __VMS_EXIT = n; \
                                     <span class="enscript-keyword">if</span> (__VMS_EXIT == 0) \
				       __VMS_EXIT = 1; \
				     <span class="enscript-keyword">else</span> \
				       __VMS_EXIT = (n &lt;&lt; 3) | 2; \
                                     __VMS_EXIT |= 0x10000000; \
				     exit(__VMS_EXIT); } <span class="enscript-keyword">while</span>(0)
#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">NO_SYS_PARAM_H</span>
#  <span class="enscript-reference">else</span>
     <span class="enscript-comment">/* !defined VMS */</span>
#    <span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">MPE</span>
#      <span class="enscript-reference">define</span> <span class="enscript-variable-name">NO_SYS_PARAM_H</span>
#    <span class="enscript-reference">endif</span>
#    <span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">OPENSSL_UNISTD</span>
#      <span class="enscript-reference">include</span> <span class="enscript-variable-name">OPENSSL_UNISTD</span>
#    <span class="enscript-reference">else</span>
#      <span class="enscript-reference">include</span> <span class="enscript-string">&lt;unistd.h&gt;</span>
#    <span class="enscript-reference">endif</span>
#    <span class="enscript-reference">ifndef</span> <span class="enscript-variable-name">NO_SYS_TYPES_H</span>
#      <span class="enscript-reference">include</span> <span class="enscript-string">&lt;sys/types.h&gt;</span>
#    <span class="enscript-reference">endif</span>
#    <span class="enscript-reference">if</span> <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">NeXT</span>) || <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">NEWS4</span>)
#      <span class="enscript-reference">define</span> <span class="enscript-variable-name">pid_t</span> int <span class="enscript-comment">/* pid_t is missing on NEXTSTEP/OPENSTEP
                         * (unless when compiling with -D_POSIX_SOURCE,
                         * which doesn't work for us) */</span>
#      <span class="enscript-reference">define</span> <span class="enscript-variable-name">ssize_t</span> int <span class="enscript-comment">/* ditto */</span>
#    <span class="enscript-reference">endif</span>
#    <span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">NEWS4</span> <span class="enscript-comment">/* setvbuf is missing on mips-sony-bsd */</span>
#      <span class="enscript-reference">define</span> <span class="enscript-function-name">setvbuf</span>(a, b, c, d) setbuffer((a), (b), (d))
       <span class="enscript-type">typedef</span> <span class="enscript-type">unsigned</span> <span class="enscript-type">long</span> clock_t;
#    <span class="enscript-reference">endif</span>

#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">OPENSSL_CONF</span>	<span class="enscript-string">&quot;openssl.cnf&quot;</span>
#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">SSLEAY_CONF</span>		OPENSSL_CONF
#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">RFILE</span>		<span class="enscript-string">&quot;.rnd&quot;</span>
#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">LIST_SEPARATOR_CHAR</span> <span class="enscript-string">':'</span>
#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">NUL_DEV</span>		<span class="enscript-string">&quot;/dev/null&quot;</span>
#    <span class="enscript-reference">define</span> <span class="enscript-function-name">EXIT</span>(n)		exit(n)
#  <span class="enscript-reference">endif</span>

#  <span class="enscript-reference">define</span> <span class="enscript-function-name">SSLeay_getpid</span>()	getpid()

#<span class="enscript-reference">endif</span>


<span class="enscript-comment">/*************/</span>

#<span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">USE_SOCKETS</span>
#  <span class="enscript-reference">if</span> <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">WINDOWS</span>) || <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">MSDOS</span>)
      <span class="enscript-comment">/* windows world */</span>

#    <span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">NO_SOCK</span>
#      <span class="enscript-reference">define</span> <span class="enscript-function-name">SSLeay_Write</span>(a,b,c)	(-1)
#      <span class="enscript-reference">define</span> <span class="enscript-function-name">SSLeay_Read</span>(a,b,c)	(-1)
#      <span class="enscript-reference">define</span> <span class="enscript-function-name">SHUTDOWN</span>(fd)		close(fd)
#      <span class="enscript-reference">define</span> <span class="enscript-function-name">SHUTDOWN2</span>(fd)		close(fd)
#    <span class="enscript-reference">else</span>
#      <span class="enscript-reference">include</span> <span class="enscript-string">&lt;winsock.h&gt;</span>
<span class="enscript-type">extern</span> HINSTANCE _hInstance;
#      <span class="enscript-reference">define</span> <span class="enscript-function-name">SSLeay_Write</span>(a,b,c)	send((a),(b),(c),0)
#      <span class="enscript-reference">define</span> <span class="enscript-function-name">SSLeay_Read</span>(a,b,c)	recv((a),(b),(c),0)
#      <span class="enscript-reference">define</span> <span class="enscript-function-name">SHUTDOWN</span>(fd)		{ shutdown((fd),0); closesocket(fd); }
#      <span class="enscript-reference">define</span> <span class="enscript-function-name">SHUTDOWN2</span>(fd)		{ shutdown((fd),2); closesocket(fd); }
#    <span class="enscript-reference">endif</span>

#  <span class="enscript-reference">elif</span> <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">MAC_OS_pre_X</span>)

#    <span class="enscript-reference">include</span> <span class="enscript-string">&quot;MacSocket.h&quot;</span>
#    <span class="enscript-reference">define</span> <span class="enscript-function-name">SSLeay_Write</span>(a,b,c)		MacSocket_send((a),(b),(c))
#    <span class="enscript-reference">define</span> <span class="enscript-function-name">SSLeay_Read</span>(a,b,c)		MacSocket_recv((a),(b),(c),true)
#    <span class="enscript-reference">define</span> <span class="enscript-function-name">SHUTDOWN</span>(fd)		MacSocket_close(fd)
#    <span class="enscript-reference">define</span> <span class="enscript-function-name">SHUTDOWN2</span>(fd)		MacSocket_close(fd)

#  <span class="enscript-reference">else</span>

#    <span class="enscript-reference">ifndef</span> <span class="enscript-variable-name">NO_SYS_PARAM_H</span>
#      <span class="enscript-reference">include</span> <span class="enscript-string">&lt;sys/param.h&gt;</span>
#    <span class="enscript-reference">endif</span>
#    <span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">VXWORKS</span>
#      <span class="enscript-reference">include</span> <span class="enscript-string">&lt;time.h&gt;</span> 
#    <span class="enscript-reference">elif</span> !<span class="enscript-reference">defined</span>(<span class="enscript-variable-name">MPE</span>)
#      <span class="enscript-reference">include</span> <span class="enscript-string">&lt;sys/time.h&gt;</span> <span class="enscript-comment">/* Needed under linux for FD_XXX */</span>
#    <span class="enscript-reference">endif</span>

#    <span class="enscript-reference">include</span> <span class="enscript-string">&lt;netdb.h&gt;</span>
#    <span class="enscript-reference">if</span> <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">VMS</span>) &amp;&amp; !<span class="enscript-reference">defined</span>(<span class="enscript-variable-name">__DECC</span>)
#      <span class="enscript-reference">include</span> <span class="enscript-string">&lt;socket.h&gt;</span>
#      <span class="enscript-reference">include</span> <span class="enscript-string">&lt;in.h&gt;</span>
#      <span class="enscript-reference">include</span> <span class="enscript-string">&lt;inet.h&gt;</span>
#    <span class="enscript-reference">else</span>
#      <span class="enscript-reference">include</span> <span class="enscript-string">&lt;sys/socket.h&gt;</span>
#      <span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">FILIO_H</span>
#        <span class="enscript-reference">include</span> <span class="enscript-string">&lt;sys/filio.h&gt;</span> <span class="enscript-comment">/* Added for FIONBIO under unixware */</span>
#      <span class="enscript-reference">endif</span>
#      <span class="enscript-reference">include</span> <span class="enscript-string">&lt;netinet/in.h&gt;</span>
#      <span class="enscript-reference">include</span> <span class="enscript-string">&lt;arpa/inet.h&gt;</span>
#    <span class="enscript-reference">endif</span>

#    <span class="enscript-reference">if</span> <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">NeXT</span>) || <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">_NEXT_SOURCE</span>)
#      <span class="enscript-reference">include</span> <span class="enscript-string">&lt;sys/fcntl.h&gt;</span>
#      <span class="enscript-reference">include</span> <span class="enscript-string">&lt;sys/types.h&gt;</span>
#    <span class="enscript-reference">endif</span>

#    <span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">AIX</span>
#      <span class="enscript-reference">include</span> <span class="enscript-string">&lt;sys/select.h&gt;</span>
#    <span class="enscript-reference">endif</span>

#    <span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">__QNX__</span>
#      <span class="enscript-reference">include</span> <span class="enscript-string">&lt;sys/select.h&gt;</span>
#    <span class="enscript-reference">endif</span>

#    <span class="enscript-reference">if</span> <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">sun</span>)
#      <span class="enscript-reference">include</span> <span class="enscript-string">&lt;sys/filio.h&gt;</span>
#    <span class="enscript-reference">else</span>
#      <span class="enscript-reference">ifndef</span> <span class="enscript-variable-name">VMS</span>
#        <span class="enscript-reference">include</span> <span class="enscript-string">&lt;sys/ioctl.h&gt;</span>
#      <span class="enscript-reference">else</span>
	 <span class="enscript-comment">/* ioctl is only in VMS &gt; 7.0 and when socketshr is not used */</span>
#        <span class="enscript-reference">if</span> !<span class="enscript-reference">defined</span>(<span class="enscript-variable-name">TCPIP_TYPE_SOCKETSHR</span>) &amp;&amp; <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">__VMS_VER</span>) &amp;&amp; (<span class="enscript-variable-name">__VMS_VER</span> &gt; 70000000)
#          <span class="enscript-reference">include</span> <span class="enscript-string">&lt;sys/ioctl.h&gt;</span>
#        <span class="enscript-reference">endif</span>
#      <span class="enscript-reference">endif</span>
#    <span class="enscript-reference">endif</span>

#    <span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">VMS</span>
#      <span class="enscript-reference">include</span> <span class="enscript-string">&lt;unixio.h&gt;</span>
#      <span class="enscript-reference">if</span> <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">TCPIP_TYPE_SOCKETSHR</span>)
#        <span class="enscript-reference">include</span> <span class="enscript-string">&lt;socketshr.h&gt;</span>
#      <span class="enscript-reference">endif</span>
#    <span class="enscript-reference">endif</span>

#    <span class="enscript-reference">define</span> <span class="enscript-function-name">SSLeay_Read</span>(a,b,c)     read((a),(b),(c))
#    <span class="enscript-reference">define</span> <span class="enscript-function-name">SSLeay_Write</span>(a,b,c)    write((a),(b),(c))
#    <span class="enscript-reference">define</span> <span class="enscript-function-name">SHUTDOWN</span>(fd)    { shutdown((fd),0); closesocket((fd)); }
#    <span class="enscript-reference">define</span> <span class="enscript-function-name">SHUTDOWN2</span>(fd)   { shutdown((fd),2); closesocket((fd)); }
#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">INVALID_SOCKET</span>	(-1)
#  <span class="enscript-reference">endif</span>
#<span class="enscript-reference">endif</span>

#<span class="enscript-reference">if</span> <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">__ultrix</span>)
#  <span class="enscript-reference">ifndef</span> <span class="enscript-variable-name">ssize_t</span>
#    <span class="enscript-reference">define</span> <span class="enscript-variable-name">ssize_t</span> int 
#  <span class="enscript-reference">endif</span>
#<span class="enscript-reference">endif</span>

#<span class="enscript-reference">if</span> <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">sun</span>) &amp;&amp; !<span class="enscript-reference">defined</span>(<span class="enscript-variable-name">__svr4__</span>) &amp;&amp; !<span class="enscript-reference">defined</span>(<span class="enscript-variable-name">__SVR4</span>)
  <span class="enscript-comment">/* include headers first, so our defines don't break it */</span>
#<span class="enscript-reference">include</span> <span class="enscript-string">&lt;stdlib.h&gt;</span>
#<span class="enscript-reference">include</span> <span class="enscript-string">&lt;string.h&gt;</span>
  <span class="enscript-comment">/* bcopy can handle overlapping moves according to SunOS 4.1.4 manpage */</span>
# <span class="enscript-reference">define</span> <span class="enscript-function-name">memmove</span>(s1,s2,n) bcopy((s2),(s1),(n))
# <span class="enscript-reference">define</span> <span class="enscript-function-name">strtoul</span>(s,e,b) ((unsigned long int)strtol((s),(e),(b)))
<span class="enscript-type">extern</span> <span class="enscript-type">char</span> *sys_errlist[]; <span class="enscript-type">extern</span> <span class="enscript-type">int</span> sys_nerr;
# <span class="enscript-reference">define</span> <span class="enscript-function-name">strerror</span>(errnum) \
	(((errnum)&lt;0 || (errnum)&gt;=sys_nerr) ? NULL : sys_errlist[errnum])
#<span class="enscript-reference">endif</span>

#<span class="enscript-reference">ifndef</span> <span class="enscript-variable-name">OPENSSL_EXIT</span>
# <span class="enscript-reference">if</span> <span class="enscript-reference">defined</span>(<span class="enscript-variable-name">MONOLITH</span>) &amp;&amp; !<span class="enscript-reference">defined</span>(<span class="enscript-variable-name">OPENSSL_C</span>)
#  <span class="enscript-reference">define</span> <span class="enscript-function-name">OPENSSL_EXIT</span>(n) return(n)
# <span class="enscript-reference">else</span>
#  <span class="enscript-reference">define</span> <span class="enscript-function-name">OPENSSL_EXIT</span>(n) do { EXIT(n); return(n); } while(0)
# <span class="enscript-reference">endif</span>
#<span class="enscript-reference">endif</span>

<span class="enscript-comment">/***********************************************/</span>

<span class="enscript-comment">/* do we need to do this for getenv.
 * Just define getenv for use under windows */</span>

#<span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">WIN16</span>
<span class="enscript-comment">/* How to do this needs to be thought out a bit more.... */</span>
<span class="enscript-comment">/*char *GETENV(char *);
#define Getenv	GETENV*/</span>
#<span class="enscript-reference">define</span> <span class="enscript-variable-name">Getenv</span>	getenv
#<span class="enscript-reference">else</span>
#<span class="enscript-reference">define</span> <span class="enscript-variable-name">Getenv</span> getenv
#<span class="enscript-reference">endif</span>

#<span class="enscript-reference">define</span> <span class="enscript-variable-name">DG_GCC_BUG</span>	<span class="enscript-comment">/* gcc &lt; 2.6.3 on DGUX */</span>

#<span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">sgi</span>
#<span class="enscript-reference">define</span> <span class="enscript-variable-name">IRIX_CC_BUG</span>	<span class="enscript-comment">/* all version of IRIX I've tested (4.* 5.*) */</span>
#<span class="enscript-reference">endif</span>
#<span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">SNI</span>
#<span class="enscript-reference">define</span> <span class="enscript-variable-name">IRIX_CC_BUG</span>	<span class="enscript-comment">/* CDS++ up to V2.0Bsomething suffered from the same bug.*/</span>
#<span class="enscript-reference">endif</span>

#<span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">NO_MD2</span>
#<span class="enscript-reference">define</span> <span class="enscript-variable-name">MD2_Init</span> MD2Init
#<span class="enscript-reference">define</span> <span class="enscript-variable-name">MD2_Update</span> MD2Update
#<span class="enscript-reference">define</span> <span class="enscript-variable-name">MD2_Final</span> MD2Final
#<span class="enscript-reference">define</span> <span class="enscript-variable-name">MD2_DIGEST_LENGTH</span> 16
#<span class="enscript-reference">endif</span>
#<span class="enscript-reference">ifdef</span> <span class="enscript-variable-name">NO_MD5</span>
#<span class="enscript-reference">define</span> <span class="enscript-variable-name">MD5_Init</span> MD5Init 
#<span class="enscript-reference">define</span> <span class="enscript-variable-name">MD5_Update</span> MD5Update
#<span class="enscript-reference">define</span> <span class="enscript-variable-name">MD5_Final</span> MD5Final
#<span class="enscript-reference">define</span> <span class="enscript-variable-name">MD5_DIGEST_LENGTH</span> 16
#<span class="enscript-reference">endif</span>

#<span class="enscript-reference">ifdef</span>  <span class="enscript-variable-name">__cplusplus</span>
}
#<span class="enscript-reference">endif</span>

#<span class="enscript-reference">endif</span>

</pre>
<hr />
</body></html>