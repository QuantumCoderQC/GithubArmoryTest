/*
 * Copyright (C)2005-2019 Haxe Foundation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

// We need this class so that calls to the empty standard implementations
// don't get optimized away.

@:coreApi
extern class EReg {
	public function new( r : String, opt : String ):Void;
	public function match( s : String ) : Bool;
	public function matched( n : Int ) : String;
	public function matchedLeft() : String;
	public function matchedRight() : String;
	public function matchedPos() : { pos : Int, len : Int };
	public function matchSub( s : String, pos : Int, len : Int = -1):Bool;
	public function split( s : String ) : Array<String>;
	public function replace( s : String, by : String ) : String;
	public function map( s : String, f : EReg -> String ) : String;
	public static function escape( s : String ) : String;
}