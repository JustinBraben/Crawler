#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

constexpr float width = 1536.f;

constexpr float height = 1024.f;

constexpr auto assetsLoadPath = "../../../../assets";

constexpr float textureTileSizeX = 32.f;
constexpr float textureTileSizeY = 32.f;

constexpr float gameTileSizeX = 128.f;
constexpr float gameTileSizeY = 128.f;

constexpr float scaleX = gameTileSizeX / textureTileSizeX;
constexpr float scaleY = gameTileSizeY / textureTileSizeY;

constexpr float playerSpawnX = width / 2.0f;

constexpr float playerSpawnY = height / 2.0f;

constexpr float playerMaxVelocityY = 2.f;

constexpr float playerMinVelocityY = -2.f;

constexpr float playerMaxVelocityX = 2.f;

constexpr float playerMinVelocityX = -2.f;

#endif // !CONSTANTS_HPP