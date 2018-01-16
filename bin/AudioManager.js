function _AudioManagerAdd(name, filename) {
	Module.AudioManagerAdd(Pointer_stringify(name), Pointer_stringify(filename));
}

function _AudioManagerPlay(name) {
	Module.AudioManagerPlay(Pointer_stringify(name));
}

function _AudioManagerPause(name) {
	Module.AudioManagerPause(Pointer_stringify(name));
}

function _AudioManagerStop(name) {
	Module.AudioManagerStop(Pointer_stringify(name));
}

function _AudioManagerLoop(name) {
	Module.AudioManagerLoop(Pointer_stringify(name));
}

function _AudioManagerSetGain(name, gain) {
	Module.AudioManagerSetGain(Pointer_stringify(name), gain);
}