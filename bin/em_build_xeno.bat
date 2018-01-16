emcc -std=c++11 -I"../Xeno/src" -I"../flappy/src/level" -I"../Dependencies/Freeimage/include" "../Xeno/src/graphics/buffers/vertexbuffer.cpp" "../Xeno/src/graphics/buffers/indexbuffer.cpp" "../Xeno/src/graphics/buffers/vertexarray.cpp" "../Xeno/src/graphics/label.cpp" "../Xeno/src/graphics/font.cpp" "../Xeno/src/graphics/font_manager.cpp" "../Xeno/src/graphics/shader.cpp" "../Xeno/src/graphics/texture.cpp" "../Xeno/src/graphics/window.cpp" "../Xeno/src/maths/mat4.cpp" "../Xeno/src/maths/vec2.cpp" "../Xeno/src/maths/vec3.cpp" "../Xeno/src/maths/vec4.cpp" "../flappy/src/flappy.cpp" "../Xeno/src/audio/audio.cpp" "../Xeno/src/audio/audio_manager.cpp" freetype.bc freeimage.bc -s USE_GLFW=3 -s FULL_ES3=1 -DXENO_PLATFORM_WEB=1 -s ASSERTIONS=1 --memory-init-file 0 --post-js AudioManager.js -g4 -O3 -o Web\xeno.html