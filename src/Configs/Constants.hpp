#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

constexpr float width = 1536.f;

constexpr float height = 1024.f;

constexpr auto assetsLoadPath = "../../../../assets";
constexpr auto savesPath = "../../../../data/saves";

constexpr float textureTileSizeX = 32.f;
constexpr float textureTileSizeY = 32.f;

constexpr float gameTileSizeX = 128.f;
constexpr float gameTileSizeY = 128.f;

constexpr float scaleX = gameTileSizeX / textureTileSizeX;
constexpr float scaleY = gameTileSizeY / textureTileSizeY;

constexpr float playerSpawnX = width / 2.0f;

constexpr float playerSpawnY = height / 2.0f;

constexpr float playerAccelerationX = 0.1f;

constexpr float playerAccelerationY = 0.1f;

constexpr float playerMaxVelocityY = 3.f;

constexpr float playerMinVelocityY = -3.f;

constexpr float playerMaxVelocityX = 3.f;

constexpr float playerMinVelocityX = -3.f;

#endif // !CONSTANTS_HPP