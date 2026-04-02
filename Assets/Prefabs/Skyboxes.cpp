#include "Skyboxes.h"

static Skybox* CreateVzSkybox(const std::string& folder, const std::string& prefix) {
    Skybox* skybox = new Skybox();
    skybox->Load({
        "Assets/Skyboxes/" + folder + "/vz_" + prefix + "_right.png", // +X
        "Assets/Skyboxes/" + folder + "/vz_" + prefix + "_left.png",  // -X
        "Assets/Skyboxes/" + folder + "/vz_" + prefix + "_up.png",    // +Y
        "Assets/Skyboxes/" + folder + "/vz_" + prefix + "_down.png",  // -Y
        "Assets/Skyboxes/" + folder + "/vz_" + prefix + "_front.png", // +Z
        "Assets/Skyboxes/" + folder + "/vz_" + prefix + "_back.png"   // -Z
    });
    return skybox;
}

Skybox* Assets::Apocalypse()      { return CreateVzSkybox("Apocalypse", "apocalypse"); }
Skybox* Assets::ApocalypseLand()  { return CreateVzSkybox("Apocalypse Land", "apocalypse_land"); }
Skybox* Assets::ApocalypseOcean() { return CreateVzSkybox("Apocalypse Ocean", "apocalypse_ocean"); }
Skybox* Assets::Classic()         { return CreateVzSkybox("Classic", "classic"); }
Skybox* Assets::ClassicLand()     { return CreateVzSkybox("Classic Land", "classic_land"); }
Skybox* Assets::Clear()           { return CreateVzSkybox("Clear", "clear"); }
Skybox* Assets::ClearOcean()      { return CreateVzSkybox("Clear Ocean", "clear_ocean"); }
Skybox* Assets::Dawn()            { return CreateVzSkybox("Dawn", "dawn"); }
Skybox* Assets::Dusk()            { return CreateVzSkybox("Dusk", "dusk"); }
Skybox* Assets::DuskLand()        { return CreateVzSkybox("Dusk Land", "dusk_land"); }
Skybox* Assets::DuskOcean()       { return CreateVzSkybox("Dusk Ocean", "dusk_ocean"); }
Skybox* Assets::EmptySpace()      { return CreateVzSkybox("Empty Space", "empty_space"); }
Skybox* Assets::Gray()            { return CreateVzSkybox("Gray", "gray"); }
Skybox* Assets::Moody()           { return CreateVzSkybox("Moody", "moody"); }
Skybox* Assets::Netherworld()     { return CreateVzSkybox("Netherworld", "netherworld"); }
Skybox* Assets::Sinister()        { return CreateVzSkybox("Sinister", "sinister"); }
Skybox* Assets::SinisterLand()    { return CreateVzSkybox("Sinister Land", "sinister_land"); }
Skybox* Assets::SinisterOcean()   { return CreateVzSkybox("Sinister Ocean", "sinister_ocean"); }

Skybox* Assets::Space1() {
    Skybox* skybox = new Skybox();
    skybox->Load({
        "Assets/Skyboxes/Space1/px.png",
        "Assets/Skyboxes/Space1/nx.png",
        "Assets/Skyboxes/Space1/py.png",
        "Assets/Skyboxes/Space1/ny.png",
        "Assets/Skyboxes/Space1/pz.png",
        "Assets/Skyboxes/Space1/nz.png"
    });
    return skybox;
}

Skybox* Assets::Sunshine() { return CreateVzSkybox("Sunshine", "sunshine"); }
Skybox* Assets::Techno()   { return CreateVzSkybox("Techno", "techno"); }