# GGEngine #
A simple OpenGL game engine.
* Microsoft Visual Community 2017
 * SDK Version: 10.0.15063.0


## Resources ##
#### 1. thebennybox ####
* [[github](https://github.com/BennyQBD)]
* [[opengl series](https://www.youtube.com/watch?v=ss3AnSxJ2X8&list=PLEETnX-uPtBXP_B2yupUKlflXBznWIlL5)]

#### 2. TheCherno ####
* [[Sparky Engine github](https://github.com/TheCherno/Sparky)]
* [[Sparky Engine series](https://www.youtube.com/watch?v=vWU8EltWTfM&list=PLlrATfBNZ98fqE45g3jZA_hLGUrD4bo6_)]
* [[c++ series](https://www.youtube.com/watch?v=18c3MTX0PK0&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb)]
* [[new openGL series](https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2)]

#### 3. Joey de Vries ####
* [[opengl github](https://github.com/JoeyDeVries/LearnOpenGL)]
* [[opengl tutorial](https://learnopengl.com/)]  [[learnopengl pdf](https://learnopengl.com/book/learnopengl_book.pdf)]
 * \*pdf is the more recent one


## Books ##
1. **Game Engine Architecture** by Jason Gregory
2. **Effective C++** by Scott Meyers
3. **Code Complete** by Steve McConnell


## Libraries used ##
1. [(Assimp) Open Asset Import Library](http://www.assimp.org/)
2. [(GLEW) The OpenGL Extension Wrangler Library](http://glew.sourceforge.net/)
3. [(GLFW) OpenGL Framework](http://www.glfw.org/)
4. [(SOIL2) Simple OpenGL Image Library 2](https://bitbucket.org/SpartanJ/soil2) based from [SOIL](http://www.lonesock.net/soil.html)


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
   * shared shaders / materials
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
 * debug draws
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
* \*dirty flags
* renderer
 * base renderer
   * mesh renderer
   * model load
   * material
   * texture
 * shader
   * automated uniforms
   * system uniforms
* components
 * camera

\* Needs polish but will do for now.