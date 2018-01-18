var script = document.createElement('script');

if (Util.canIUseWebAssembly() === true) {
    script.setAttribute('src', 'main.wasm.js');
} else {
    script.setAttribute('src', 'main.asm.js');
}

script.onload = function () {
    var app = new APPCpp({
        print: function (e) {
            //std::cout redirects to here
            console.log(e);
        },
        onRuntimeInitialized: function (e) {
            // Post this event you can use your transpiled library
            var h1 = document.createElement('h1');
            if (typeof app.printString === 'function') {
                //USE_EMBIND was used within CPP
                h1.innerHTML = app.getString();
                app.setString(h1.innerHTML + " Meow.");
                app.printString();
            } else {
                h1.innerHTML = app.ccall("getString", 'string', [], []);
                app.ccall("setString", 'void', ['string'], [h1.innerHTML + ' Meow']);
                app.ccall("printString", 'void', [], []);
            }
            document.body.appendChild(h1);
        }
    });
};

document.body.appendChild(script);