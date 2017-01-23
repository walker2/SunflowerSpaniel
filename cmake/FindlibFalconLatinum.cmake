set(FIND_FALCONLATINUM_PATHS ${SunflowerSpaniel_SOURCE_DIR}/include/Falcon)

find_path(FALCONLATINUM_INCLUDE_DIR
        States/StateManager.h
        2D/Sprite.h
        GLSL/ShaderProgram.h
        Errors/Errors.h
        2D/Vertex.h
        InputOutput/IOManager.h
        2D/picoPNG.h
        2D/GLTexture.h
        2D/ImageLoader/ImageLoader.h
        ResourceManager/ResourceManager.h
        ResourceManager/TextureCache.h
        Window/Window.h
        Init/Falcon.h
        2D/Camera/Camera2D.h
        2D/SpriteBatch/SpriteBatch.h
        InputOutput/InputManager.h
        Timing/Timing.h
        Object/Projectile.h
        2D/SpriteFont/SpriteFont.h
        Audio/AudioEngine.h
        2D/Particles/ParticleSystem.h
        2D/Particles/ParticleBatch.h
        2D/DebugRenderer/DebugRenderer.h
        2D/TileSheet.h
        2D/Lights/BasicLight.h
        GUI/GUI.h
        GameIntefaces/IGameScreen.h
        GameIntefaces/IMainGame.h
        GameIntefaces/ScreenList.h
        PATH_SUFFIXES
        include PATHS
        ${FIND_FALCONLATINUM_PATHS})

find_library(FALCONLATINUM_LIBRARY
        NAMES FalconLatinum
        PATH_SUFFIXES lib
        PATHS ${FIND_FALCONLATINUM_PATHS})