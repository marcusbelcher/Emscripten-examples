var Util = Util || {};
(function (Util) {
    Util.canIUseWebAssembly = function () {
        return typeof WebAssembly === 'object' ? true : false;
    };
    Util.isHTTPS = function () {
        return (location.protocol === 'https:') ? true : false;
    };
    Util.isImageDataEqual = function (lhs, rhs) {
        if (lhs.data.length !== rhs.data.length) {
            return false;
        }

        for (let i = 0; i < lhs.data.length; ++i) {
            if (lhs.data[i] !== rhs.data[i]) {
                return false;
            }
        }

        return true;
    };
    Util.canIUseGetUserMedia = function () {
        if (navigator && navigator.mediaDevices && navigator.mediaDevices.getUserMedia) {
            return true;
        }

        return false;
    };
    //https://stackoverflow.com/questions/45189257/how-to-test-the-availability-of-asm-js-in-a-web-browser
    Util.canIUseASM = function () {
        try {
            (function MyAsmModule() { "use asm"; return {} })();
            return true;
        }
        catch (err) {
            return false;
        }
    }
})(Util);