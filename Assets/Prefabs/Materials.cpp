#include "Materials.h"

static Material CreateMaterial(const std::string& path, Vec2 tiling = { 1.0f, 1.0f }) {
    Material mat;
    mat.ambient = { 0.2f, 0.2f, 0.25f, 1.0f };
    mat.diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
    mat.specular = { 0.1f, 0.1f, 0.1f, 1.0f };
    mat.loadTexture(path);
    mat.tiling = tiling;
    return mat;
}

Material Assets::Grass1() { return CreateMaterial("Assets/Textures/Grass/Grass_02.png", { 1000.0f, 1000.0f }); }
Material Assets::Grass12() { return CreateMaterial("Assets/Textures/Grass/Grass_12.png", { 1000.0f, 1000.0f }); }

Material Assets::Brick01() { return CreateMaterial("Assets/Textures/Bricks/Bricks_01.png", { 3.0f, 3.0f }); }
Material Assets::Brick05() { return CreateMaterial("Assets/Textures/Bricks/Bricks_05.png", { 3.0f, 3.0f }); }
Material Assets::Brick20() { return CreateMaterial("Assets/Textures/Bricks/Bricks_20.png", { 3.0f, 3.0f }); }

Material Assets::Wood01() { return CreateMaterial("Assets/Textures/Wood/Wood_01.png", { 1.0f, 1.0f }); }
Material Assets::Wood04() { return CreateMaterial("Assets/Textures/Wood/Wood_04.png", { 1.0f, 1.0f }); }

Material Assets::Tile01() { return CreateMaterial("Assets/Textures/Tile/Tile_01.png", { 5.0f, 5.0f }); }
Material Assets::Tile10() { return CreateMaterial("Assets/Textures/Tile/Tile_10.png", { 5.0f, 5.0f }); }

Material Assets::Roof01() { return CreateMaterial("Assets/Textures/Roofs/Roofs_01.png", { 4.0f, 4.0f }); }