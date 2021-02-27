function de(b){
    var a,e={},d=b.split(""),c=f=d[0],g=[c],h=o=256;
    for(b=1;b<d.length;b++)
        a=d[b].charCodeAt(0),a=h>a?d[b]:e[a]?e[a]:f+c,g.push(a),c=a.charAt(0),e[o]=f+c,o++,f=a;
    return g.join("")
}

function loadLzwContent(url,cb){
    fetch(url)
        .then(res=>res.text())
        .then(data=>{
            y=new Uint8Array(data)
            o=""
            for (i=0;i<y.length;i++) {
                o += String.fromCharCode(y[i])
            }
            cb(de(o.replace("/\\0","\x00").replace("\\\\","\\")))
        }
    )
}