var app = null;
var appInitialised = false;

var onSubmit = function(e) {
    e.preventDefault();

    if(app !== null && appInitialised === true) {
        var output = app.generate(parseInt(e.target[0].value));
        document.getElementById("output").innerHTML = output;
    } else {
        console.log("Waiting for APPCpp to be initialised");
    }

    return false;
};

var script = document.createElement('script');

if (Util.canIUseWebAssembly() === true) {
    script.setAttribute('src', 'main.wasm.js');
} else {
    script.setAttribute('src', 'main.asm.js');
}

script.onload = function () {
    app = new APPCpp({
        print: function (e) {
            //std::cout redirects to here
            console.log(e);
        },
        onRuntimeInitialized: function (e) {
            appInitialised = true;
        }
    });
};

document.body.appendChild(script);