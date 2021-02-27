function en(c){var x='charCodeAt',b,e={},f=c.split(""),d=[],a=f[0],g=256;for(b=1;b<f.length;b++)c=f[b],null!=e[a+c]?a+=c:(d.push(1<a.length?e[a]:a[x](0)),e[a+c]=g,g++,a=c);d.push(1<a.length?e[a]:a[x](0));for(b=0;b<d.length;b++)d[b]=String.fromCharCode(d[b]);return d.join("")}
function de(b){var a,e={},d=b.split(""),c=f=d[0],g=[c],h=o=256;for(b=1;b<d.length;b++)a=d[b].charCodeAt(0),a=h>a?d[b]:e[a]?e[a]:f+c,g.push(a),c=a.charAt(0),e[o]=f+c,o++,f=a;return g.join("")}

// get code in hex form
code = process.argv[2];

// convert to ascii
/*
const convert = (from, to) => str => Buffer.from(str, from).toString(to)
const hexToAscii = convert('hex', 'ascii')
const asciiToHex = convert('ascii', 'hex')
*/

function hexToAscii(hex) {
    var hex = hex.toString();//force conversion
    var str = '';
    for (var i = 0; i < hex.length; i += 2)
        str += String.fromCharCode(parseInt(hex.substr(i, 2), 16));
    return str;
}

function asciiToHex(str) {
    var hex = '';
    for(var i=0;i<str.length;i++) {
        hex += ''+str.charCodeAt(i).toString(16);
    }
    return hex;
}

code = hexToAscii(code)

_src = code // test input

// encode lzw
code = en(code)

if (code != hexToAscii(asciiToHex(code))) {console.log(hexToAscii(asciiToHex(code)));error("WTF test 0 failed")}

// test decoding
if (de(code) != _src) error("test 1 failed")

// encode to hex
test_ascii = code
code = asciiToHex(code)
test_hex = code

// format to c string
code = "\\x"+code.match(/.{2}/g).join("\\x")

_tcode = code // test input
// escape 0x00 so c++ does not have a problem with it
code = code.replace(/\\x5c/g,"\\x5c\\x5c")   // ("\\","\\\\")
code = code.replace(/\\x00/g,"\\x2f\\x5c\\x30") // ("\x00","/\\0")

// test //
tcode =  code.replace(/\\x2f\\x5c\\x30/g,"\\x00") // ("\x00","/\\0")
tcode = tcode.replace(/\\x5c\\x5c/g,"\\x5c")   // ("\\","\\\\")
if (tcode != _tcode) error("test 2 failed")
tcode = tcode.replace(/\\x/g,"")
if (test_hex != tcode) error("test 3 faild")
tcode = hexToAscii(tcode)
if (test_ascii != tcode) error("test 4 failed")
p1 = tcode = de(tcode)
if (tcode != _src) {console.log(p1);error("test 5 failed\n")} // I know that error is not defined... but it shows my message in the console ;)


// output code
console.log(code)