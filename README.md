# GGEngine #
A simple OpenGL game engine.
* Microsoft Visual Community 2017
 * SDK Version: 10.0.15063.0


## References / Resources ##
#### 1. OpenGL ####
* API docs - http://docs.gl/

#### 2. TheCherno ####
* [[Sparky Engine github](https://github.com/TheCherno/Sparky)]
* [[Sparky Engine series](https://www.youtube.com/watch?v=vWU8EltWTfM&list=PLlrATfBNZ98fqE45g3jZA_hLGUrD4bo6_)]
* [[c++ series](https://www.youtube.com/watch?v=18c3MTX0PK0&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb)]
* [[new openGL series](https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2)]

#### 3. thebennybox ####
* [[github](https://github.com/BennyQBD)]
* [[opengl series](https://www.youtube.com/watch?v=ss3AnSxJ2X8&list=PLEETnX-uPtBXP_B2yupUKlflXBznWIlL5)]

#### 4. Joey de Vries ####
* [[opengl github](https://github.com/JoeyDeVries/LearnOpenGL)]
* [[opengl tutorial](https://learnopengl.com/)]  [[learnopengl pdf](https://learnopengl.com/book/learnopengl_book.pdf)]
 * \*pdf is the more recent one

#### 5. Jason Turner ####
* [[c++ series](https://www.youtube.com/channel/UCxHAlbZQNFU2LgEtiqd2Maw)]

#### 6. Fonts ####
* [[Google Fonts](https://fonts.google.com/)]


## Books ##
1. **Game Engine Architecture** by Jason Gregory
2. **Effective C++** by Scott Meyers
3. **Code Complete** by Steve McConnell


## Libraries used ##
1. [(GLEW) The OpenGL Extension Wrangler Library](http://glew.sourceforge.net/)
2. [(GLFW) OpenGL Framework](http://www.glfw.org/)
3. [(SOIL2) Simple OpenGL Image Library 2](https://bitbucket.org/SpartanJ/soil2) based from [SOIL](http://www.lonesock.net/soil.html)
4. [(Assimp) Open Asset Import Library](http://www.assimp.org/)
5. [FreeType](https://www.freetype.org/index.html)
6. [ImGui](https://github.com/ocornut/imgui)


## Tools used ##
#### 1. Microsoft Visual Community 2017 ####
* https://www.visualstudio.com/vs/community/

#### 2. NShader ####
* glsl syntax highlight package for visual studio
* https://github.com/samizzo/nshader

#### 3. sublime-shaders ####
* a Sublime Text 2 & 3 syntax highlighting package for HLSL, OpenGL's GLSL, and Cg, based on ShaderLanguages.
* https://github.com/euler0/sublime-glsl


## TODO ##
* high prio
 * renderer
   * frame buffers
     * render buffers
     * depth/color textures
   * light
     * directional light
     * point light
     * spotlight
* renderer
 * base renderer
   * mesh
   * transform
 * shader
   * reload
   * post process
   * hdr
   * pbr
   * skybox
   * cubemaps
 * categorized draw *
   * per vertex array id
   * per shader / material
* core
 * scene graph
   * bsp
   * octrees (3d)
   * quad trees (2d)
 * primitive objects
* debug
 * text ui
* physics
 * collisions
 * numerical integrations
   * euler
   * verlet
* audio
* resource management
 * delete cache on 0 reference
 * async loading
 * memory allocator
* production
 * asset zipping
* etc
 * guids

## DONE ##
* <span style="color:red">\*\*</span>dirty flags
* components
 * camera
* debug
 * <span style="color:red">\*\*</span>debug draws (draw line)
* renderer
 * shared shaders / materials
 * base renderer
   * mesh renderer
   * model load
   * material
   * texture
 * shader
   * automated uniforms
   * system uniforms

<span style="color:red">\*\*</span> Needs polish but will do for now.