function en(c){var x='charCodeAt',b,e={},f=c.split(""),d=[],a=f[0],g=256;for(b=1;b<f.length;b++)c=f[b],null!=e[a+c]?a+=c:(d.push(1<a.length?e[a]:a[x](0)),e[a+c]=g,g++,a=c);d.push(1<a.length?e[a]:a[x](0));for(b=0;b<d.length;b++)d[b]=String.fromCharCode(d[b]);return d.join("")}

// get code in hex form
code = process.argv[2];

// convert to ascii
const convert = (from, to) => str => Buffer.from(str, from).toString(to)
const hexToAscii = convert('hex', 'ascii')
const asciiToHex = convert('ascii', 'hex')
code = hexToAscii(code)

// encode lzw and encode to hex
code = en(code)
code = asciiToHex(code)

// format to c string
code = "\\x"+code.match(/.{2}/g).join("\\x")

console.log(code)